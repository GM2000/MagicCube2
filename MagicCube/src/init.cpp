#include "MagicCube.h"

void KeyBoardListener(GLFWwindow* window, int key, int scancode, int action, int mods);

//load all shader
void LoadShaders()
{
	//load 2D shader
	shader = new GLuint[1];

	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "Normail3D.vert" },
		{ GL_FRAGMENT_SHADER, "Normail3D.frag" },
		{ GL_NONE, NULL } };

	shader[0] = LoadShaders(shaders);

	ShaderUniformLocation[NORMAL_3D_SHADER_FRUSTUM] = glGetUniformLocation(shader[0], "Frustum");
	ShaderUniformLocation[NORMAL_3D_SHADER_TRANSLATE] = glGetUniformLocation(shader[0], "Translate");
	ShaderUniformLocation[NORMAL_3D_SHADER_ROTATE]=glGetUniformLocation(shader[0], "Rotate");
}

GLuint init(int argc, char **argv)
{
	setlocale(LC_ALL, "chs");

	//init glfw
	if (!glfwInit())
		return false;

	//create windows
	window = glfwCreateWindow(640, 480, argv[0], NULL, NULL);
	if (!window)//is create windows?
	{
		//exit
		glfwTerminate();
		return false;
	}
	
	//set opengl version
	glfwMakeContextCurrent(window);

	//init glew
	int glewInitIsOk = glewInit();
	//is of?
	if (glewInitIsOk != GLEW_OK)
		return glewInitIsOk;//exit
	
	//load all shaders
	LoadShaders();


	glfwSetKeyCallback(window, KeyBoardListener);

	return true;
}