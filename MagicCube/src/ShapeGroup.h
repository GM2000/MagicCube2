#pragma once
#include "MagicCube.h"

#define SG_MAX_ARRAY 1000000

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
	GLfloat	*SG_TmpVaoData		= new GLfloat	[SG_MAX_ARRAY * 3];
	GLfloat	*SG_TmpTextureData	= new GLfloat	[SG_MAX_ARRAY * 2];

	char**	SG_ShapeName		= new char*		[SG_MAX_ARRAY	 ];

	int		SG_ShapeNumber;

	bool	HasInit;
public:
	//array
	_Array	SG_VaoData;
	_Array	SG_TextureData;

	//unload ShaoeGroup
	~ShapeGroup()
	{
		//delete
		delete(SG_VaoData.SG_Data);
		delete(SG_TextureData.SG_Data);
	}
	//load ShapeGroup
	ShapeGroup(unsigned int Type)
	{
		SG_ShapeNumber	= 0;
		HasInit			= false;
	}
	//init
	void inline init()
	{
		//malloc
		SG_VaoData		.SetSize(SG_ShapeNumber * 12);
		SG_TextureData	.SetSize(SG_ShapeNumber * 8);

		//copy memory
		memcpy(SG_VaoData.SG_Data		, SG_TmpVaoData		, SG_VaoData	.SG_DataSize * sizeof(GLfloat));
		memcpy(SG_TextureData.SG_Data	, SG_TmpTextureData	, SG_TextureData.SG_DataSize * sizeof(GLfloat));

		//delete
		delete(SG_TmpVaoData	);
		delete(SG_TmpTextureData);

		HasInit = true;
	}
	//set SG data
	void inline AddShape(GLfloat VAOData[12], GLfloat TexturePosition[8],const char* ShapeName)
	{
		if (HasInit)
		{
			//expand memory
			SG_VaoData		.ExpandSize(SG_ShapeNumber * 12);
			SG_TextureData	.ExpandSize(SG_ShapeNumber * 8 );

			//copy memory
			memcpy(&SG_VaoData		.SG_Data[SG_ShapeNumber * 12], VAOData			, 12	* sizeof(GLfloat));
			memcpy(&SG_TextureData	.SG_Data[SG_ShapeNumber * 8	], TexturePosition	, 8		* sizeof(GLfloat));

			//set shapename
			SG_ShapeName[SG_ShapeNumber] = (char*)ShapeName;

			//add shape number
			SG_ShapeNumber++;

			std::cout << "Load Shape after init Call:"<<SG_ShapeName[SG_ShapeNumber - 1] << std::endl;
		}
		else 
		{
			//copy memory
			memcpy(&SG_TmpVaoData		[SG_ShapeNumber * 12]	, VAOData			, 12	* sizeof(GLfloat));
			memcpy(&SG_TmpTextureData	[SG_ShapeNumber * 8	]	, TexturePosition	, 8		* sizeof(GLfloat));

			//set shapename
			SG_ShapeName[SG_ShapeNumber] = (char*)ShapeName;

			//add shape number
			SG_ShapeNumber ++;

			std::cout << "Load Shape before init Call:" << SG_ShapeName[SG_ShapeNumber - 1] << std::endl;
		}
	}
};