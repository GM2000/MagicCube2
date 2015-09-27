
#include "MagicCube.h"
#include "ShapeGroup.h"

//test ShapeGroup
GLfloat vaod[12] = { -1.0,-1.0, 0.0,
1.0,-1.0, 0.0,
1.0, 1.0, 0.0,
-1.0, 1.0, 0.0 };

GLfloat texpd[8] = { 0.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,0.0f / 32.0f,0.0f / 32.0f,0.0f / 32.0f };

shape SH3(vaod, texpd);

extern shapeGroup stone;

extern bool ScreenInit;

int NowAddShapeNumber = 0;

//test move
extern GLfloat XM;
extern GLfloat YM;
extern GLfloat ZM;

//KeyBoard CallBack
void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			ZM = 0.01f;
			break;
		case GLFW_KEY_S:
			ZM = -0.01f;
			break;
		case GLFW_KEY_A:
			XM = 0.01f;
			break;
		case GLFW_KEY_D:
			XM = -0.01f;
			break;
		case GLFW_KEY_1:
			NowAddShapeNumber++;
			stone.AddShape(SH3, (const char*)(NowAddShapeNumber), 0, NowAddShapeNumber * 2 - 10, -10);
			//ScreenInit = false;
			break;
		case GLFW_KEY_2:
			stone.RemoveShapes((const char*)NowAddShapeNumber);
			ScreenInit = false;
			NowAddShapeNumber--;
			break;
		default:
			break;
		}
	}else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			ZM = 0;
			break;
		case GLFW_KEY_S:
			ZM = 0;
			break;
		case GLFW_KEY_A:
			XM = 0;
			break;
		case GLFW_KEY_D:
			XM = 0;
			break;
		default:
			break;
		}
	}
}

//WindowsResize callback
void WindowsSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowsHeight = height;
	WindowsWidth = width;

	glViewport(0, 0, width, height);
}