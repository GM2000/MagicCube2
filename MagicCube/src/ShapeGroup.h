#pragma once
#include "MagicCube.h"

//ShapeGroup
class ShapeGroup
{
private:
	//save size and data
	struct _Array
	{
		GLfloat *SG_Data;

		int		SG_DataSize;

		void inline Reset(int Size)
		{
			if (Size == 0)
			{
				SG_Data		= NULL;
				SG_DataSize = 0;
			}
			else
			{
				SG_Data		= new GLfloat[Size];
				SG_DataSize = Size;
			}
		}
	};

	_Array	SG_VaoData;
	_Array	SG_TextureData;

	bool SG_Lock;
public:
	//unload ShaoeGroup
	~ShapeGroup()
	{
		delete(SG_VaoData.SG_Data);
		delete(SG_TextureData.SG_Data);
	}
	//load ShapeGroup
	ShapeGroup(int i)
	{
		SG_VaoData.Reset(0);
		SG_TextureData.Reset(0);

		SG_Lock = false;
	}
	//Lock SG
	void Lock()
	{
		SG_Lock = true;
	}
	//set SG data
	int AddShape(GLfloat VBOData[12], GLfloat TexturePosition[8])
	{
		if (!SG_Lock)
		{
			_Array	TMPData;

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
	}
};