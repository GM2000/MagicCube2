
#include "MagicCube.h"

void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action==GLFW_PRESS)
		std::cout << key << std::endl;
}