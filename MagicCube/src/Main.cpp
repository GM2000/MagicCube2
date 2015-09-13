#include "MagicCube.h"
#include "Location.h"

//windows
GLFWwindow	*Window;

//shaders
GLuint		*shader;
GLuint		ShaderUniformLocation[3];

//windows size
int WindowsHeight;
int WindowsWidth;

//main
int main(int argc,char **argv)
{
	//init the program
	int initState = Init(argc, argv);

	//is OK?
	if (!initState)
		return initState;

	//load a PNG
	pic_data *test = new pic_data[1];
	LoadPNG("pngtest.png", test);

	//gen a texture
	GLuint TextureID;

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, test->width, test->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, test->rgba);
	
	//delete pic_data
	free(test);

	//try to use Mob System
	loc teste;

	//try GetChunk and GetBlock(get int Position)
	teste.GetChunkX();
	
	//use shader
	glUseProgram(shader[0]);

	//maim loop
	while (!glfwWindowShouldClose(Window))
	{
		//refresh screen
		glfwSwapBuffers(Window);

		//draw screen
		RenderGame();

		//pass the message
		glfwPollEvents();
	}
	//exit
	glfwTerminate();

	return 0;
}