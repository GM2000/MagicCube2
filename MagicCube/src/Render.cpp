
#include "MagicCube.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Location.h"
#include "ShapeGroup.h"

extern shapeGroup stone;

bool ScreenInit = false;

GLuint ScreenVao;
GLuint Buffers;

GLfloat XM=0;
GLfloat YM=0;
GLfloat ZM=0;

GLfloat X;
GLfloat Y;
GLfloat Z;

GLfloat rot;

//try to use Mob System
loc teste;

void RenderGame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Z = -2;

	teste.MoveTo(XM, YM, ZM);

	X += XM;
	Y += YM;
	Z += ZM;

	//rot = 180.0f;
	//rot = 0.0f;
	//rot += 0.05f;

	glm::mat4 Translate = glm::translate(glm::mat4(), glm::vec3(teste.GetX(), teste.GetY(), teste.GetZ()));
	glm::mat4 Rotate = glm::rotate_slow(glm::mat4(), rot, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)WindowsWidth / (GLfloat)WindowsHeight, 0.1f, 500.0f);

	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_FRUSTUM], 1, GL_TRUE, glm::value_ptr(Projection));
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_ROTATE], 1, GL_TRUE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_TRANSLATE], 1, GL_TRUE, glm::value_ptr(Translate));

	stone.RenderShapeGroup();
}

void Render()
{
	//Render
	RenderGame();
}