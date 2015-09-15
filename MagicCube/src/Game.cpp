
#include "MagicCube.h"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void RenderGame()
{
	int size = 1;

	if (!ScreenInit) 
	{

		GLfloat *quad_data = new GLfloat[20 * size];

		/*
		GLfloat quad_data2[20]=
		{
			-1.0f,-1.0f,-2.0f,
			1.0f,-1.0f,-2.0f,
			1.0f,1.0f,-2.0f,
			-1.0f,1.0f,-2.0f,
			0.0,1.0,
			1.0,1.0,
			1.0,0.0,
			0.0,0.0
		};
		*/

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
			quad_data[i * 8 + 0 + size * 12] = 0.0f;
			quad_data[i * 8 + 1 + size * 12] = 1.0f;
			quad_data[i * 8 + 2 + size * 12] = 1.0f;
			quad_data[i * 8 + 3 + size * 12] = 1.0f;
			quad_data[i * 8 + 4 + size * 12] = 1.0f;
			quad_data[i * 8 + 5 + size * 12] = 0.0f;
			quad_data[i * 8 + 6 + size * 12] = 0.0f;
			quad_data[i * 8 + 7 + size * 12] = 0.0f;
		}

		glGenVertexArrays(1, &ScreenVao);
		glBindVertexArray(ScreenVao);

		glGenBuffers(1, &Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers);
		glBufferData(GL_ARRAY_BUFFER, 20 * size * sizeof(GLfloat), quad_data, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT,
			GL_FALSE, 0, (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(size * 12 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		ScreenInit = true;

		glm::mat4 Projection = glm::perspective(45.0f, (GLfloat)WindowsWidth / (GLfloat)WindowsHeight, 0.1f, 500.0f);
		glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_FRUSTUM], 1, GL_TRUE, glm::value_ptr(Projection));
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	Z = -6;

	X += XM;
	Y += YM;
	Z += ZM;

	//rot = 180.0f;
	//rot = 0.0f;
	rot += 0.05f;

	glm::mat4 Translate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, Z));
	glm::mat4 Rotate = glm::rotate_slow(glm::mat4(), rot,glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_ROTATE], 1, GL_TRUE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_TRANSLATE], 1, GL_TRUE, glm::value_ptr(Translate));
	
	glBindVertexArray(ScreenVao);
	for (int i = 0; i < 1;i++)
		glDrawArrays(GL_TRIANGLE_FAN, 0, size*4);
}