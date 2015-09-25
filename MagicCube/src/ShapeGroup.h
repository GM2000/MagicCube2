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
		_shape(const char* InitShapeName, shape* InitShape)
		{
			ShapeName	 = InitShapeName;
			Shape		 = InitShape;
		}
		shape*		Shape;
		const char*	ShapeName;
	};
	typedef std::list<_shape> ShapeList;

	ShapeList			SG_ShapeData;

	int					SG_ShapeNumber;

public:
	void AddShape(shape* Shape,const char* ShapeName)
	{
		//make a TMP shape
		_shape SG_Shape(ShapeName, Shape);
		//add data
		SG_ShapeData.push_back(SG_Shape);
	}
	void RemoveShape(const char* ShapeName)
	{
		//use iterator to get the data
		ShapeList::iterator	SG_ShapeData_Iterator;

		for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end();)
		{
			if (SG_ShapeData_Iterator->ShapeName == ShapeName)
			{
				//delete iterator
				SG_ShapeData.erase(SG_ShapeData_Iterator);
				//break the loop and it will save the memoty and it can be safty
				break;
			}
			else 
			{
				SG_ShapeData_Iterator++;
			}
		}
	}
	GLfloat* GetTotalData()
	{
		ShapeList::iterator	SG_ShapeData_Iterator;

		//Tmp Vector data
		std::vector<GLfloat*>	TexturePos;
		std::vector<GLfloat*>	VAOData;

		unsigned int	ItemSize = 0;;

		for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end(); SG_ShapeData_Iterator++)
		{
			VAOData		.push_back(SG_ShapeData_Iterator->Shape->VAO_Data);
			TexturePos	.push_back(SG_ShapeData_Iterator->Shape->TexturePos_Data);

			ItemSize += 20;
		}
		VAOData.insert(VAOData.begin(), TexturePos.begin(), TexturePos.end());

		GLfloat*	TotalData = (GLfloat*)malloc(sizeof(GLfloat) * ItemSize);

		for (int i = 0; i < ItemSize; i++)
		{
			TotalData[i] = *VAOData[i];
		}
		
		return TotalData;
	}
};