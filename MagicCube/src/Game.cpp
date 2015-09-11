
#include "MagicCube.h"
#include <vmath.h>

bool ScreenInit = false;

GLuint ScreenVao;
GLuint Buffers;

GLfloat X;
GLfloat Y;
GLfloat Z;

GLfloat rot;

void RenderGame()
{
	if (!ScreenInit)
	{
		static const GLfloat quad_data[] =
		{
			-0.9f,-0.9f,-2.0f,
			0.9f,-0.9f,-2.0f,
			0.9f,0.9f,-2.0f,
			-0.9f,0.9f,-2.0f,
			1.0,1.0,
			0.0,1.0,
			0.0,0.0,
			1.0,0.0
		};

		glGenVertexArrays(1, &ScreenVao);
		glBindVertexArray(ScreenVao);

		glGenBuffers(1, &Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT,
			GL_FALSE, 0, (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		ScreenInit = true;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	X += 0.001;
	Y += 0.001;
	Z += 0.01;

	rot += 1.0f;

	vmath::Tmat4<GLfloat> PlayerFrustum(vmath::frustum(1.0, -1.0, -1.0, 1.0, 0.1, 500));
	vmath::Tmat4<GLfloat> PlayerRotate(vmath::rotate<GLfloat>(rot,0.0f,0.0f,1.0f));
	vmath::Tmat4<GLfloat> PlayerTranslate(vmath::translate<GLfloat>(X,Y,Z));

	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_FRUSTUM], 1, GL_TRUE, PlayerFrustum);
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_ROTATE], 1, GL_FALSE, PlayerRotate);
	glUniformMatrix4fv(ShaderUniformLocation[NORMAL_3D_SHADER_TRANSLATE], 1, GL_TRUE, PlayerTranslate);

	glBindVertexArray(ScreenVao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}