#include "pch.h"
#include <gl/freeglut.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example3");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	srand((unsigned int)time(NULL));
	int draw = rand() % 4;
	int rev = 0;
	for (int curr_y = 200; curr_y >= -200; curr_y -= 200)
	{
		for (int curr_x = -300; curr_x <= 300; curr_x += 200)
		{
			switch (draw)
			{
			case 0:
				glBegin(GL_LINES);
				glVertex2i(curr_x - 30, curr_y);
				glVertex2i(curr_x + 30, curr_y);
				glEnd();
				rev = 0;
				draw++;
				//Sleep(3000);
				break;
			case 1:
				glBegin(GL_TRIANGLES);
				glVertex2i(curr_x - 30, curr_y - 30);
				glVertex2i(curr_x + 30, curr_y - 30);
				glVertex2i(curr_x, curr_y + 30);
				glEnd();
				if (rev == 1)
				{
					draw--;
				}
				else
				{
					draw++;
				}
				//Sleep(3000);
				//draw++;
				break;
			case 2:
				glBegin(GL_POLYGON);
				glVertex2i(curr_x - 30, curr_y - 30);
				glVertex2i(curr_x + 30, curr_y - 30);
				glVertex2i(curr_x + 30, curr_y + 30);
				glVertex2i(curr_x - 30, curr_y + 30);
				glEnd();
				if (rev == 1)
				{
					draw--;
				}
				else
				{
					draw++;
				}
				//Sleep(3000);
				//draw++;
				break;
			case 3:
				glBegin(GL_POLYGON);
				glVertex2i(curr_x - 20, curr_y - 30);
				glVertex2i(curr_x + 20, curr_y - 30);
				glVertex2i(curr_x + 45, curr_y);
				glVertex2i(curr_x, curr_y + 30);
				glVertex2i(curr_x - 45, curr_y);
				glEnd();
				rev = 1;
				draw--;
				//draw++;
				break;
			}
		}
	}
	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(-400, 400, -300, 300, -1, 1);
}