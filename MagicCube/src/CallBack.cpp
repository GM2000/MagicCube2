
#include "MagicCube.h"

void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			break;
		default:
			break;
		}
	}
}

void WindowsSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowsHeight = height;
	WindowsWidth = width;

	glViewport(0.0, 0.0, width, height);
}