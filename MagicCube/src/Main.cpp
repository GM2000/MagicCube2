#include "MagicCube.h"
#include "Block.h"

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
	GLfloat i2[10]={ 1.0,0.0,0.0,2.0,0.0,3.0,4.0,5.0,6.0 };

	shape SH(i2, i2);

	shapeGroup stone;

	stone.AddShape(&SH, "ABC");
	stone.AddShape(&SH, "ABC");
	//stone.RemoveShape("ABC");
	stone.GetTotalData();

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
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, test->width, test->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, test->rgba);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//delete pic_data
	free(test);
	
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