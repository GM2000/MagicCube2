#pragma once
#include "MagicCube.h"
#include <list>
#include <vector>

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
			Shape		= (shape*)malloc(sizeof(shape));
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
	//save data
	GLfloat*		TotalData;
	ShapeList		SG_ShapeData;
	int				SG_ShapeNumber;
	bool			HasChange;

	GLfloat *GetTotalData();

	void	RefreshBuffer();
public:
	void inline AddShape(shape Shape, const char* ShapeName, float X, float Y, float Z)
	{
		HasChange = true;
		//make a TMP shape
		_shape SG_Shape(ShapeName, Shape, X, Y, Z);
		//add data
		SG_ShapeData.push_back(SG_Shape);
	}
	void inline AddShapes(shape* Shape, const char* ShapeName, float X, float Y, float Z, int ShapeNumber)
	{
		HasChange = true;

		for (int i = 0; i < ShapeNumber; i++)
		{
			//make a TMP shape
			_shape SG_Shape(ShapeName, Shape[i], X, Y, Z);
			//add data
			SG_ShapeData.push_back(SG_Shape);
		}
	}
	void inline RemoveShapes(const char* ShapeName)
	{
		HasChange = true;
		//use iterator to get the data
		ShapeList::iterator	SG_ShapeData_Iterator;

		for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end();)
		{
			if (SG_ShapeData_Iterator->ShapeName == ShapeName)
			{
				//delete iterator
				SG_ShapeData.erase(SG_ShapeData_Iterator++);
			}
			else 
			{
				SG_ShapeData_Iterator++;
			}
		}
	}

	void RenderShapeGroup()
	{
		if (HasChange)
		{
			//refresh Buffer Data
			RefreshBuffer();
		}
		glBindVertexArray(SG_VAO);
		glDrawArrays(GL_QUADS, 0, SG_ShapeData.size() * 4);
	}
};