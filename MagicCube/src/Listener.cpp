
#include "MagicCube.h"

void KeyBoardListener(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action==GLFW_PRESS)
		std::cout << key << std::endl;
}