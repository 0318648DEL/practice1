#include "pch.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example2");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	int color1 = 0;
	int color2 = 0;
	int color3 = 0;
	int num = 0;
	float roll = 0;
	float out = 0;
	num = (rand() % 10)+5;
	roll = 800 / num;
	out = 600 / num;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	color1 = rand() % 3;
	color2 = rand() % 3;
	color3 = rand() % 3;
	for (int y = 0; y < num; ++y)
	{
		for (int x = 0; x < num; ++x)
		{
			glColor3f(0.03f*x*color1, 0.03f*x*color2, 0.03f*x*y/**color3*/);
			glRectf(-400 + x*roll, -300 + y * out, -400 + (x + 1) * roll, -300 + (y + 1) * out);
			//glRectf(-1.0f+0.05f*x, -1.0f+0.4f*y, -1.0f+0.05f*(x + 1), -1.0f+0.2f*(y + 1));
			color3++;
		}
	}
	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1, 1);
}