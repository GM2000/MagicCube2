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

	GLfloat*			TotalData;

	ShapeList			SG_ShapeData;

	int					SG_ShapeNumber;

	bool				HasChange;

public:
	int	 ShapeNumber()
	{
		return SG_ShapeData.size();
	}
	void AddShape(shape* Shape,const char* ShapeName)
	{
		HasChange = true;
		//make a TMP shape
		_shape SG_Shape(ShapeName, Shape);
		//add data
		SG_ShapeData.push_back(SG_Shape);
	}
	void RemoveShape(const char* ShapeName)
	{
		HasChange = true;
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
		if (HasChange)
		{
			HasChange = false;

			ShapeList::iterator	SG_ShapeData_Iterator;

			const int	VAOSize = SG_ShapeData.size() * 12;
			const int	ItemSize = SG_ShapeData.size() * 20;

			GLfloat** TmpTotalData;

			TmpTotalData = (GLfloat**)malloc(sizeof(GLfloat) * ItemSize);

			int LoopShapeNumber = 0;

			//start to loop
			for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end(); SG_ShapeData_Iterator++)
			{
				//VAO
				for (int i = 0; i < 12; i++)
				{
					TmpTotalData[LoopShapeNumber * 12 + i] = &SG_ShapeData_Iterator->Shape->VAO_Data[i];
				}
				//TexturePos
				for (int i = 0; i < 8; i++)
				{
					TmpTotalData[VAOSize + LoopShapeNumber * 8 + i] = &SG_ShapeData_Iterator->Shape->TexturePos_Data[i];
				}

				LoopShapeNumber++;
			}
			TotalData = *TmpTotalData;
		}
		return TotalData;
	}
};