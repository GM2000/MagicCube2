#pragma once
#include "MagicCube.h"

#define BLOCK_VAO_UP	0
#define BLOCK_VAO_DOWN	1
#define BLOCK_VAO_LEFT	2
#define BLOCK_VAO_RIGHT	3
#define BLOCK_VAO_FRONT	4
#define BLOCK_VAO_BACK	5
#define BLOCK_VAO_OTHER	6

class blockRenderDate
{
private:
	//save a block vao Data(only one,a block need seven vao data
	struct _oneBlockVaoData
	{

	};
	struct _oneBlockTexturePositionData
	{

	};

	GLfloat RenderData[7];

public:
};

class block
{
private:
	//save Block Vao
	GLfloat* RenderData[7];
public:
	//init Block
	block(blockRenderDate* VAO)
	{
		RenderData[BLOCK_VAO_UP	] = VAOUp;
		RenderData[BLOCK_VAO_DOWN	] = VAODown;
		RenderData[BLOCK_VAO_LEFT	] = VAOLeft;
		RenderData[BLOCK_VAO_RIGHT	] = VAORight;
		RenderData[BLOCK_VAO_FRONT	] = VAOFront;
		RenderData[BLOCK_VAO_BACK	] = VAOBack;
		RenderData[BLOCK_VAO_OTHER	] = VAOOther;
	}

	GLfloat* GetVAO(int Front)
	{
		return RenderData[Front];
	}

	GLfloat GetVAOSize(int Front)
	{
		return sizeof(RenderData[Front]);
	}
};