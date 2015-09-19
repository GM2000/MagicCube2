
#include "MagicCube.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Location.h"

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
	int size = 1;

	if (!ScreenInit) 
	{
		GLfloat quad_data[20];

			quad_data[0] = -1.0f;
			quad_data[1] = -1.0f;
			quad_data[2] = 0.0f;
			quad_data[3] = 1.0f;
			quad_data[4] = -1.0f;
			quad_data[5] = 0.0f;
			quad_data[6] = 1.0f;
			quad_data[7] = 1.0f;
			quad_data[8] = 0.0f;
			quad_data[9] = -1.0f;
			quad_data[10] = 1.0f;
			quad_data[11] = 0.0f;

			quad_data[12] = 0.0f / 32.0f;//X
			quad_data[13] = 1.0f / 32.0f;//Y+1
			quad_data[14] = 1.0f / 32.0f;//X+1
			quad_data[15] = 1.0f / 32.0f;//Y+1
			quad_data[16] = 1.0f / 32.0f;//X+1
			quad_data[17] = 0.0f / 32.0f;//Y
			quad_data[18] = 0.0f / 32.0f;//X
			quad_data[19] = 0.0f / 32.0f;//Y


		/*
		GLfloat *quad_data = new GLfloat[20 * size];	

		for (int i = 0; i < size; i++)
		{
			quad_data[i * 12 + 0] = -1.0f;
			quad_data[i * 12 + 1] = -1.0f;
			quad_data[i * 12 + 2] =  0.0f;
			quad_data[i * 12 + 3] =  1.0f;
			quad_data[i * 12 + 4] = -1.0f;
			quad_data[i * 12 + 5] =  0.0f;
			quad_data[i * 12 + 6] =  1.0f;
			quad_data[i * 12 + 7] =  1.0f;
			quad_data[i * 12 + 8] =  0.0f;
			quad_data[i * 12 + 9] = -1.0f;
			quad_data[i * 12 + 10] =  1.0f;
			quad_data[i * 12 + 11] =  0.0f;
		}
		for (int i = 0; i < size; i++)
		{
			
			quad_data[i * 8 + 0 + size * 12] = 0.0f / 32.0f;//X
			quad_data[i * 8 + 1 + size * 12] = 1.0f / 32.0f;//Y+1
			quad_data[i * 8 + 2 + size * 12] = 1.0f / 32.0f;//X+1
			quad_data[i * 8 + 3 + size * 12] = 1.0f / 32.0f;//Y+1
			quad_data[i * 8 + 4 + size * 12] = 1.0f / 32.0f;//X+1
			quad_data[i * 8 + 5 + size * 12] = 0.0f / 32.0f;//Y
			quad_data[i * 8 + 6 + size * 12] = 0.0f / 32.0f;//X
			quad_data[i * 8 + 7 + size * 12] = 0.0f / 32.0f;//Y
			
		}
		*/
		glGenVertexArrays(1, &ScreenVao);
		glBindVertexArray(ScreenVao);

		glGenBuffers(1, &Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers);
		glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT,
			GL_FALSE, 0, (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(size * 12 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		ScreenInit = true;
	}
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
	glm::mat4 Rotate = glm::rotate_slow(glm::mat4(), rot,glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)WindowsWidth / (GLfloat)WindowsHeight, 0.1f, 500.0f);

	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_FRUSTUM], 1, GL_TRUE, glm::value_ptr(Projection));
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_ROTATE], 1, GL_TRUE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_TRANSLATE], 1, GL_TRUE, glm::value_ptr(Translate));
	
	glBindVertexArray(ScreenVao);
	for (int i = 0; i < 1;i++)
		glDrawArrays(GL_TRIANGLE_FAN, 0, size*4);
}