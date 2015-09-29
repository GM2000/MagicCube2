#pragma once
#include "MagicCube.h"
#include <list>
#include <vector>

#define SG_NOTASK			0
#define SG_NEEDREFRESH		1

class shape
{
public:
	GLfloat		VAO_Data		[12];
	GLfloat		TexturePos_Data	[8 ];

	shape(GLfloat* VAOData,GLfloat* TexturePosData)
	{
		//copy the data to make sure the size is 20
		memcpy(VAO_Data			, VAOData		, 12 * sizeof(GLfloat));
		memcpy(TexturePos_Data	, TexturePosData, 8  * sizeof(GLfloat));
	}
};

//ShapeGroup
class shapeGroup
{
private:
	//save size and data
	class _shape
	{
	public:
		_shape(const char* InitShapeName, shape InitShape,float X,float Y,float Z)
		{
			//save the shape data
			Shape = (shape*)malloc(sizeof(shape));

			*Shape		= InitShape;
			ShapeName	= InitShapeName;

			Location[0] = X;
			Location[1] = Y;
			Location[2] = Z;
		}
		shape*		Shape;

		float		Location[3];
		const char*	ShapeName;
	};
	typedef std::list<_shape> ShapeList;

	//for opengl
	GLuint			SG_VAO;
	GLuint			SG_Buffer;
	bool			SG_InitGL;
	//save data
	GLfloat*		SG_TotalData;
	ShapeList		SG_ShapeData;

	int				SG_ShapeNumber;
	int				SG_Size;

	//refresh shapegroup
	bool			SG_NeedRefreshBuffer;
	bool			SG_Task;
	bool			SG_IsRefreshingData;

	void			RefreshBuffer();
	void			RefteshTotalData();

	void			RefreshData()
	{
		SG_IsRefreshingData = true;

		std::thread GetTotalDataThread(&shapeGroup::RefteshTotalData, this);
		GetTotalDataThread.detach();
	}
public:
	shapeGroup()
	{
		SG_NeedRefreshBuffer	= false;
		SG_IsRefreshingData		= false;
		SG_InitGL				= false;

		SG_Task					= SG_NOTASK;
	}
	void inline init()
	{
		glGenVertexArrays(1, &SG_VAO);
		glBindVertexArray(SG_VAO);

		glGenBuffers(1, &SG_Buffer);

		SG_InitGL = true;
	}
	//only can add one shape
	void inline AddShape(shape Shape, const char* ShapeName, float X, float Y, float Z)
	{
		SG_Task = SG_NEEDREFRESH;
		//only can add one shape
		//make a TMP shape
		_shape SG_Shape(ShapeName, Shape, X, Y, Z);
		//add data
		SG_ShapeData.push_back(SG_Shape);
	}
	//can add more than one shape
	void inline AddShapes(shape* Shape, const char* ShapeName, float X, float Y, float Z, int ShapeNumber)
	{
		SG_Task = SG_NEEDREFRESH;
		//loop to add more than one shape
		for (int i = 0; i < ShapeNumber; i++)
		{
			//make a TMP shape
			_shape SG_Shape(ShapeName, Shape[i], X, Y, Z);
			//add data
			SG_ShapeData.push_back(SG_Shape);
		}
	}
	//can remove the shape that have the same name
	void inline RemoveShapes(const char* ShapeName)
	{
		//use iterator to get the data
		ShapeList::iterator	SG_ShapeData_Iterator;

		for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end();)
		{
			if (SG_ShapeData_Iterator->ShapeName == ShapeName)
			{
				//delete iterator
				SG_ShapeData_Iterator = SG_ShapeData.erase(SG_ShapeData_Iterator);
			}
			else 
			{
				SG_ShapeData_Iterator++;
			}
		}
	}
	//render the shapegroup and auto refresh
	void RenderShapeGroup()
	{
		if (SG_InitGL)
		{
			if (SG_Task == SG_NEEDREFRESH)
			{
				if (SG_NeedRefreshBuffer)
				{
					RefreshBuffer();
				}
				else if(!SG_IsRefreshingData)
				{
					RefreshData();
				}
			}
			glBindVertexArray(SG_VAO);
			glDrawArrays(GL_QUADS, 0, SG_ShapeData.size() * 4);
		}
	}
};