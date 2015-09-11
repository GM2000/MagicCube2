
#define NORMAL_3D_SHADER_FRUSTUM   0
#define NORMAL_3D_SHADER_ROTATE    1
#define NORMAL_3D_SHADER_TRANSLATE 2

#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <iostream>

//temp data when load PNG
typedef struct 
{
	//save PNG's size
	int width, height;
	//depth
	int bit_depth;
	//such as alpha
	int flag;

	//save the pixel
	GLubyte *rgba;
} pic_data;

//it will be needed when load shader 
typedef struct 
{
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

//glfw windows
extern		GLFWwindow	*window;
//all of the shader are save in *shader
extern		GLuint		*shader;
//Sader Uniform Location
extern		GLuint		ShaderUniformLocation[3];

//change ASCII to Unicode
wchar_t*	A2U(const char* in);

//init the program
GLuint		init		(int argc, char **argv);
//load PNG
GLuint		LoadPNG		(char *filepath, pic_data *out);
//load a shader
GLuint		LoadShaders	(ShaderInfo*);

//render game
void RenderGame();

