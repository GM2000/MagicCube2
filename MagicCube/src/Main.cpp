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
	ShapeGroup stone(1);
	GLfloat iii[8] = { 1.0,2.0,9.9,12.3,12.2,871.1,283.1,92873.1 };
	GLfloat ii1i[12] = { 1.1230,3212.0312,9.229,312.332,1322.2,83271.1,2383.1,973.1 };

	stone.AddShape(iii, ii1i, "123");

	stone.init();

	for (int i = 0; i < stone.SG_TextureData.SG_DataSize; i++)
	{
		std::cout << stone.SG_TextureData.SG_Data[i] << std::endl;
	}
	stone.AddShape(iii, iii, "111");

	for (int i = 0; i < stone.SG_TextureData.SG_DataSize; i++)
	{
		std::cout << stone.SG_TextureData.SG_Data[i] << std::endl;
	}
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