#pragma once
#include "MagicCube.h"
#include "ShapeGroup.h"

#define BLOCK_VAO_UP	0
#define BLOCK_VAO_DOWN	1
#define BLOCK_VAO_LEFT	2
#define BLOCK_VAO_RIGHT	3
#define BLOCK_VAO_FRONT	4
#define BLOCK_VAO_BACK	5
#define BLOCK_VAO_OTHER	6

/*Block*/
class block
{
private:
	//save Block Vao
	ShapeGroup* RenderData;
	//Block basic data
public:
	//init Block
	block(int i)
	{
		ShapeGroup hehe(i);
	}
	void AddShape(int X1,int X2,int Y1,int Y2,int Z1,int Z2)
	{
		
	}
	ShapeGroup GetBlockRenderData()
	{

	}
};