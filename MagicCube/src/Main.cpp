#include "MagicCube.h"
#include "Location.h"

GLFWwindow	*Window;

GLuint		*shader;
GLuint		ShaderUniformLocation[3];

int WindowsHeight;
int WindowsWidth;

int main(int argc,char **argv)
{
	int initState = Init(argc, argv);

	if (!initState)
		return initState;

	pic_data *test = new pic_data[1];

	LoadPNG("pngtest.png", test);

	GLuint TextureID;

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, test->width, test->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, test->rgba);

	free(test);

	loc teste;
	teste.X = -0.1f;
	teste.Y = -0.1f;

	teste.GetChunkX();
	
	
	glUseProgram(shader[0]);

	while (!glfwWindowShouldClose(Window))
	{
		glfwSwapBuffers(Window);

		RenderGame();

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}