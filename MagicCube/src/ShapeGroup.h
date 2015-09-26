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
		_shape(const char* InitShapeName, shape* InitShape,float X,float Y,float Z)
		{
			//save the shape data
			ShapeName	 = InitShapeName;
			Shape		 = InitShape;

			Location[0] = X;
			Location[1] = Y;
			Location[2] = Z;
		}
		float			Location[3];
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
	void AddShape(shape* Shape,const char* ShapeName, float X, float Y, float Z)
	{
		HasChange = true;
		//make a TMP shape
		_shape SG_Shape(ShapeName, Shape,X,Y,Z);
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
				return;
			}
			else 
			{
				SG_ShapeData_Iterator++;
			}
		}
		std::cout << "[Warning]Could Not Find The Shape" << std::endl;
	}
	GLfloat* GetTotalData()
	{
		if (HasChange)
		{
			HasChange = false;

			ShapeList::iterator	SG_ShapeData_Iterator;

			const int	VAOSize = SG_ShapeData.size() * 12;
			const int	ItemSize = SG_ShapeData.size() * 20;

			GLfloat* TmpTotalData;

			TmpTotalData = (GLfloat*)malloc(sizeof(GLfloat) * ItemSize);

			int LoopShapeNumber = 0;

			//start to loop
			for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end(); SG_ShapeData_Iterator++)
			{
				//VAO
				TmpTotalData[LoopShapeNumber * 12 + 0 ] = SG_ShapeData_Iterator->Shape->VAO_Data[0 ] + SG_ShapeData_Iterator->Location[0];
				TmpTotalData[LoopShapeNumber * 12 + 1 ] = SG_ShapeData_Iterator->Shape->VAO_Data[1 ] + SG_ShapeData_Iterator->Location[1];
				TmpTotalData[LoopShapeNumber * 12 + 2 ] = SG_ShapeData_Iterator->Shape->VAO_Data[2 ] + SG_ShapeData_Iterator->Location[2];

				TmpTotalData[LoopShapeNumber * 12 + 3 ] = SG_ShapeData_Iterator->Shape->VAO_Data[3 ] + SG_ShapeData_Iterator->Location[0];
				TmpTotalData[LoopShapeNumber * 12 + 4 ] = SG_ShapeData_Iterator->Shape->VAO_Data[4 ] + SG_ShapeData_Iterator->Location[1];
				TmpTotalData[LoopShapeNumber * 12 + 5 ] = SG_ShapeData_Iterator->Shape->VAO_Data[5 ] + SG_ShapeData_Iterator->Location[2];

				TmpTotalData[LoopShapeNumber * 12 + 6 ] = SG_ShapeData_Iterator->Shape->VAO_Data[6 ] + SG_ShapeData_Iterator->Location[0];
				TmpTotalData[LoopShapeNumber * 12 + 7 ] = SG_ShapeData_Iterator->Shape->VAO_Data[7 ] + SG_ShapeData_Iterator->Location[1];
				TmpTotalData[LoopShapeNumber * 12 + 8 ] = SG_ShapeData_Iterator->Shape->VAO_Data[8 ] + SG_ShapeData_Iterator->Location[2];

				TmpTotalData[LoopShapeNumber * 12 + 9 ] = SG_ShapeData_Iterator->Shape->VAO_Data[9 ] + SG_ShapeData_Iterator->Location[0];
				TmpTotalData[LoopShapeNumber * 12 + 10] = SG_ShapeData_Iterator->Shape->VAO_Data[10] + SG_ShapeData_Iterator->Location[1];
				TmpTotalData[LoopShapeNumber * 12 + 11] = SG_ShapeData_Iterator->Shape->VAO_Data[11] + SG_ShapeData_Iterator->Location[2];
				//TexturePos
				for (int i = 0; i < 8; i++)
				{
					TmpTotalData[VAOSize + LoopShapeNumber * 8 + i] = SG_ShapeData_Iterator->Shape->TexturePos_Data[i];
				}
				LoopShapeNumber++;
			}
			TotalData = TmpTotalData;
		}
		return TotalData;
	}
};