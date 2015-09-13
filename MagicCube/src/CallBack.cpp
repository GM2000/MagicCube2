
#include "MagicCube.h"

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
			ZM = 0.01;
			break;
		case GLFW_KEY_S:
			ZM = -0.01;
			break;
		case GLFW_KEY_A:
			XM = 0.01;
			break;
		case GLFW_KEY_D:
			XM = -0.01;
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

	glViewport(0.0, 0.0, width, height);
}