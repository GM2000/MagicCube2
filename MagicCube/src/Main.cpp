#include "MagicCube.h"
#include "Block.h"

//ShapeGroup test
shapeGroup stone;

//Render
void Render();

//FPS
double	LastRenderTime = glfwGetTime();
double	FPS;
int		RenderTime = 0;

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
	GLfloat vaod[12] = {	-1.0,-1.0, 0.0,
							1.0,-1.0, 0.0,
							1.0, 1.0, 0.0,
							-1.0, 1.0, 0.0 };

	GLfloat texpd[8] = { 0.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,1.0f / 32.0f,0.0f / 32.0f,0.0f / 32.0f,0.0f / 32.0f };

	shape SH(vaod, texpd);
	//stone.AddShape(&SH, (const char*)1,0,0,-1);

	for (int i = -340; i < 340; i++)
	{
		for (int j = -340; j < 340; j++)
		{
			stone.AddShape(SH, (const char*)(((i + 128) * 256 + j + 128)), i*2, j*2, -15);
		}
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

	//glEnable(GL_DEPTH_TEST);

	stone.init();
	//maim loop
	while (!glfwWindowShouldClose(Window))
	{
		//FPS
		RenderTime++;

		//refresh screen
		glfwSwapBuffers(Window);

		//draw screen
		Render();

		//pass the message
		glfwPollEvents();

		//FPS
		double FinishTime = glfwGetTime();
		if (FinishTime - LastRenderTime > 0.25)
		{
			FPS = (double)RenderTime / (FinishTime - LastRenderTime);
			std::cout << FPS << std::endl;
			RenderTime = 0;
			LastRenderTime = FinishTime;
		}
	}
	//exit
	glfwTerminate();

	return 0;
}