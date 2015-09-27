
#include "ShapeGroup.h"
#include <thread>

void shapeGroup::RefreshBuffer()
{
	std::thread GetTotalDataThread(&shapeGroup::GetTotalData,this);
	GetTotalDataThread.detach();

	glGenVertexArrays(1, &SG_VAO);
	glBindVertexArray(SG_VAO);

	glGenBuffers(1, &SG_Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, SG_Buffer);
	glBufferData(GL_ARRAY_BUFFER, SG_ShapeData.size() * 20 * sizeof(GLfloat), TmpTotalData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT,
		GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(SG_ShapeData.size() * 12 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	free(TmpTotalData);
}

void shapeGroup::GetTotalData()
{
	ShapeList::iterator	SG_ShapeData_Iterator;

	const int	VAOSize = SG_ShapeData.size() * 12;
	const int	ItemSize = SG_ShapeData.size() * 20;

	TmpTotalData = (GLfloat*)malloc(sizeof(GLfloat) * ItemSize);

	int LoopShapeNumber = 0;

	//start to loop
	for (SG_ShapeData_Iterator = SG_ShapeData.begin(); SG_ShapeData_Iterator != SG_ShapeData.end(); SG_ShapeData_Iterator++)
	{
		//VAO
		TmpTotalData[LoopShapeNumber * 12 + 0] = SG_ShapeData_Iterator->Shape->VAO_Data[0] + SG_ShapeData_Iterator->Location[0];
		TmpTotalData[LoopShapeNumber * 12 + 1] = SG_ShapeData_Iterator->Shape->VAO_Data[1] + SG_ShapeData_Iterator->Location[1];
		TmpTotalData[LoopShapeNumber * 12 + 2] = SG_ShapeData_Iterator->Shape->VAO_Data[2] + SG_ShapeData_Iterator->Location[2];

		TmpTotalData[LoopShapeNumber * 12 + 3] = SG_ShapeData_Iterator->Shape->VAO_Data[3] + SG_ShapeData_Iterator->Location[0];
		TmpTotalData[LoopShapeNumber * 12 + 4] = SG_ShapeData_Iterator->Shape->VAO_Data[4] + SG_ShapeData_Iterator->Location[1];
		TmpTotalData[LoopShapeNumber * 12 + 5] = SG_ShapeData_Iterator->Shape->VAO_Data[5] + SG_ShapeData_Iterator->Location[2];

		TmpTotalData[LoopShapeNumber * 12 + 6] = SG_ShapeData_Iterator->Shape->VAO_Data[6] + SG_ShapeData_Iterator->Location[0];
		TmpTotalData[LoopShapeNumber * 12 + 7] = SG_ShapeData_Iterator->Shape->VAO_Data[7] + SG_ShapeData_Iterator->Location[1];
		TmpTotalData[LoopShapeNumber * 12 + 8] = SG_ShapeData_Iterator->Shape->VAO_Data[8] + SG_ShapeData_Iterator->Location[2];

		TmpTotalData[LoopShapeNumber * 12 + 9] = SG_ShapeData_Iterator->Shape->VAO_Data[9] + SG_ShapeData_Iterator->Location[0];
		TmpTotalData[LoopShapeNumber * 12 + 10] = SG_ShapeData_Iterator->Shape->VAO_Data[10] + SG_ShapeData_Iterator->Location[1];
		TmpTotalData[LoopShapeNumber * 12 + 11] = SG_ShapeData_Iterator->Shape->VAO_Data[11] + SG_ShapeData_Iterator->Location[2];
		//TexturePos
		for (int i = 0; i < 8; i++)
		{
			TmpTotalData[VAOSize + LoopShapeNumber * 8 + i] = SG_ShapeData_Iterator->Shape->TexturePos_Data[i];
		}
		LoopShapeNumber++;
	}
	HasChange = false;
}