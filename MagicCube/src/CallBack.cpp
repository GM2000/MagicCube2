
#include "MagicCube.h"
#include "ShapeGroup.h"

extern bool ScreenInit;

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
	if ((height == 0) || (width == 0))
	{
		//pause
	}
	else 
	{
		//change windows size
		WindowsHeight = height;
		WindowsWidth = width;

		//set viewport
		glViewport(0, 0, width, height);
	}
}