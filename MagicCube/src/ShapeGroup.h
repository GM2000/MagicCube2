#pragma once
#include "MagicCube.h"

//ShapeGroup
class ShapeGroup
{
private:
	//save size and data
	class _Array
	{
	public:
		GLfloat *SG_Data;

		int		SG_DataSize;

		//set the size and clear data
		void inline SetSize(int Size)
		{
			if (Size == 0)
			{
				SG_Data = NULL;
				SG_DataSize = 0;
			}
			else
			{
				SG_Data = new GLfloat[Size];
				SG_DataSize = Size;
			}
		}
		//make the size bigger
		void inline ExpandSize(unsigned int Size)
		{
			GLfloat *SG_Tmp = SG_Data;

			//resize
			SG_Data = new GLfloat[SG_DataSize + Size];
			//copy data
			memcpy(SG_Data, SG_Tmp, SG_DataSize * sizeof(GLfloat));
			//save size
			SG_DataSize += Size;

			//delete TMP data
			delete(SG_Tmp);
		}
		//make the size smaller
		void inline NarrowSize(unsigned int Size)
		{
			GLfloat *SG_Tmp = SG_Data;

			//resize
			SG_Data = new GLfloat[SG_DataSize - Size];
			//copy data
			memcpy(SG_Data, SG_Tmp, (SG_DataSize - Size) * sizeof(GLfloat));
			//save size
			SG_DataSize -= Size;

			//delete TMP data
			delete(SG_Tmp);
		}
	};
	struct _Shape
	{
		char*	SG_ShapeName;
	};
	_Shape*	SG_Shape;

	_Array	SG_VaoData;
	_Array	SG_TextureData;

	int		SG_Size;
public:
	//unload ShaoeGroup
	~ShapeGroup()
	{
		delete(SG_VaoData.SG_Data);
		delete(SG_TextureData.SG_Data);
	}
	//load ShapeGroup
	ShapeGroup(unsigned int Type)
	{
		SG_VaoData.SetSize(1);
		SG_TextureData.SetSize(1);
		SG_TextureData.SG_Data[0] = 213.0;

		SG_TextureData.ExpandSize(1);
		SG_TextureData.SG_Data[1] = 13.0;
		SG_TextureData.NarrowSize(1);
	}
	//set SG data
	int AddShape(GLfloat VBOData[12], GLfloat TexturePosition[8],const char* ShapeName)
	{
		SG_Size++;

		for (int i = 0; i < 12; i++)
		{
			SG_TextureData.SG_Data[2 + 0] = VBOData[0];
			SG_TextureData.SG_Data[2 + 1] = VBOData[1];
		}
		for (int i = 0; i < 8; i++)
		{
			SG_TextureData.SG_Data[3 + 0] = TexturePosition[0];
			SG_TextureData.SG_Data[3 + 1] = TexturePosition[1];
			SG_TextureData.SG_Data[3 + 2] = TexturePosition[2];
		}
	}
};