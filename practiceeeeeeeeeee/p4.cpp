#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void timer_func(int value);

int squr_loc[10][2] = { 0, };
int size[10] = { 0, };
int color[10][3] = { 0, };
int size_ch[10] = { 0, };
int rev = 0;
int num = 0;
int trigger[10] = { 0, };

void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example4");
	glutMouseFunc(mouse);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer_func, 1);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	int count = 0;

	while (count < 10 && trigger[count] == 1)
	{
		glColor4ub(color[count][0], color[count][1], color[count][2], 200);
		glRecti(squr_loc[count][0] - size[count], squr_loc[count][1] - size[count], squr_loc[count][0] + size[count], squr_loc[count][1] + size[count]);
		count++;
	}

	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		trigger[num] = 1;
		if (num == 10)
		{
			num = 0;
			squr_loc[num][0] = x;
			squr_loc[num][1] = y;
			size[num] = rand() % 50 + 30;
		}
		else
		{
			squr_loc[num][0] = x;
			squr_loc[num][1] = y;
			size[num] = rand() % 50 + 30;
		}
		++num;
	}
	glutPostRedisplay();
}

void timer_func(int value)
{
	int timer = 0;
	while (timer < 10)
	{
		color[timer][0] = rand() % 250 + 5;
		color[timer][1] = rand() % 250 + 5;
		color[timer][2] = rand() % 250 + 5;

		switch (size_ch[timer])
		{
		case 0:
			size[timer] += 20;
			++size_ch[timer];
			rev = 0;
			break;
		case 1:
			if (rev == 1)
			{
				size[timer] -= 20;
				--size_ch[timer];
			}
			else
			{
				size[timer] += 20;
				++size_ch[timer];
			}
			break;
		case 2:
			if (rev == 1)
			{
				size[timer] -= 20;
				--size_ch[timer];
			}
			else
			{
				size[timer] += 20;
				++size_ch[timer];
			}
			break;
		case 3:
			if (rev == 1)
			{
				size[timer] -= 20;
				--size_ch[timer];
			}
			else
			{
				size[timer] += 20;
				++size_ch[timer];
			}
			break;
		case 4:
			if (rev == 1)
			{
				size[timer] -= 20;
				--size_ch[timer];
			}
			else
			{
				size[timer] += 20;
				++size_ch[timer];
			}
			break;
		case 5:
			size[timer] -= 20;
			--size_ch[timer];
			rev = 1;
			break;
		}
		++timer;
	}
	glutPostRedisplay();
	glutTimerFunc(100, timer_func, 1);
}