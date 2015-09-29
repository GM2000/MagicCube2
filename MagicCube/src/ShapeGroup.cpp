
#include "ShapeGroup.h"

void shapeGroup::RefreshBuffer()
{
	glBindVertexArray(SG_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, SG_Buffer);

	glBufferData(GL_ARRAY_BUFFER, SG_Size * 20 * sizeof(GLfloat), SG_TotalData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT,
		GL_FALSE, 0, (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(SG_Size * 12 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	free(SG_TotalData);

	SG_Task = SG_NOTASK;

	SG_NeedRefreshBuffer = false;
}

void shapeGroup::RefteshTotalData()
{
	ShapeList TMPShapeList = SG_ShapeData;

	ShapeList::iterator	SG_ShapeData_Iterator = TMPShapeList.begin();

	SG_Size = TMPShapeList.size();

	const int	VAOSize = SG_Size * 12;
	const int	ItemSize = SG_Size * 20;

	GLfloat*	SG_TmpTotalData = (GLfloat*)malloc(sizeof(GLfloat) * ItemSize);


	if (SG_TmpTotalData == nullptr)
	{
		std::cout << "[Warning]Can't malloc(" << sizeof(GLfloat) * ItemSize << ")" << std::endl;

		return;
	}

	//start to copy
	for (int LoopShapeNumber = 0; LoopShapeNumber < SG_Size; LoopShapeNumber++)
	{
		//VAO
		SG_TmpTotalData[LoopShapeNumber * 12 + 0] = SG_ShapeData_Iterator->Shape->VAO_Data[0] + SG_ShapeData_Iterator->Location[0];
		SG_TmpTotalData[LoopShapeNumber * 12 + 1] = SG_ShapeData_Iterator->Shape->VAO_Data[1] + SG_ShapeData_Iterator->Location[1];
		SG_TmpTotalData[LoopShapeNumber * 12 + 2] = SG_ShapeData_Iterator->Shape->VAO_Data[2] + SG_ShapeData_Iterator->Location[2];

		SG_TmpTotalData[LoopShapeNumber * 12 + 3] = SG_ShapeData_Iterator->Shape->VAO_Data[3] + SG_ShapeData_Iterator->Location[0];
		SG_TmpTotalData[LoopShapeNumber * 12 + 4] = SG_ShapeData_Iterator->Shape->VAO_Data[4] + SG_ShapeData_Iterator->Location[1];
		SG_TmpTotalData[LoopShapeNumber * 12 + 5] = SG_ShapeData_Iterator->Shape->VAO_Data[5] + SG_ShapeData_Iterator->Location[2];

		SG_TmpTotalData[LoopShapeNumber * 12 + 6] = SG_ShapeData_Iterator->Shape->VAO_Data[6] + SG_ShapeData_Iterator->Location[0];
		SG_TmpTotalData[LoopShapeNumber * 12 + 7] = SG_ShapeData_Iterator->Shape->VAO_Data[7] + SG_ShapeData_Iterator->Location[1];
		SG_TmpTotalData[LoopShapeNumber * 12 + 8] = SG_ShapeData_Iterator->Shape->VAO_Data[8] + SG_ShapeData_Iterator->Location[2];

		SG_TmpTotalData[LoopShapeNumber * 12 + 9] = SG_ShapeData_Iterator->Shape->VAO_Data[9] + SG_ShapeData_Iterator->Location[0];
		SG_TmpTotalData[LoopShapeNumber * 12 + 10] = SG_ShapeData_Iterator->Shape->VAO_Data[10] + SG_ShapeData_Iterator->Location[1];
		SG_TmpTotalData[LoopShapeNumber * 12 + 11] = SG_ShapeData_Iterator->Shape->VAO_Data[11] + SG_ShapeData_Iterator->Location[2];
		//TexturePos
		for (int i = 0; i < 8; i++)
		{
			SG_TmpTotalData[VAOSize + LoopShapeNumber * 8 + i] = SG_ShapeData_Iterator->Shape->TexturePos_Data[i];
		}
		SG_ShapeData_Iterator++;
	}
	SG_TotalData = SG_TmpTotalData;

	SG_NeedRefreshBuffer = true;
	SG_IsRefreshingData = false;
}