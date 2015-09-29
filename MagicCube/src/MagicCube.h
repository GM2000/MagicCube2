#pragma once

//Uniform Location
#define NORMAL_3D_SHADER_FRUSTUM	0
#define NORMAL_3D_SHADER_ROTATE		1
#define NORMAL_3D_SHADER_TRANSLATE	2
//Block VAO's front
#define BLOCK_VAO_UP	0
#define BLOCK_VAO_DOWN	1
#define BLOCK_VAO_LEFT	2
#define BLOCK_VAO_RIGHT	3
#define BLOCK_VAO_FRONT	4
#define BLOCK_VAO_BACK	5
#define BLOCK_VAO_OTHER	6

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include<stdlib.h>
	#include<crtdbg.h>
#endif

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <string.h>
#include <thread>

#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

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
} shaderInfo;

//glfw windows
extern		GLFWwindow	*Window;
//all of the shader are save in *shader
extern		GLuint		*shader;
//Sader Uniform Location
extern		GLuint		ShaderUniformLocation[3];

//change ASCII to Unicode
wchar_t*	A2U(const char* in);

//init the program
GLuint		Init		(int argc, char **argv);
//load PNG
GLuint		LoadPNG		(char *filepath, pic_data *out);
//load a shader
GLuint		LoadShaders	(shaderInfo*);

//Windows Size
extern	int WindowsHeight;
extern	int WindowsWidth;

