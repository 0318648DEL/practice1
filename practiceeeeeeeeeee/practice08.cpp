#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

/*음 일단 원의 중심이 되는 점은 무조건 두개다
맨 처음에 반시계 방향으로 그려지는 놈이랑 시계 방향으로 다시 돌아가는 놈이랑
다 돌았을때 방향 조절하도록 검사하는 변수 하나 더
음 끝?*/

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void timer_func(int value);

int yes_circle[10][4] = { 0, };
double radius[10] = { 0, };
int which_dir[10] = { 0, };
int trigger[10] = { 0, };
double angle[10] = { 0, };
double radius_inc[10] = { 0, };
int num = 0;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example8");
	glutMouseFunc(mouse);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer_func, 1);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	int count = 0;
	double radius_dep = 0;
	int pass = 0;
	while (count < 10 && trigger[count] == 1)
	{
		pass = 0;
		glColor3ub(0, 255, 0);
		glBegin(GL_POINTS);
		while (pass!=1)
		{
			if (which_dir[count] == 1)
			{
				while (radius_dep >= radius[count])
				{
					glVertex2f(yes_circle[count][2] - (cos(angle[count])*radius_dep), yes_circle[count][3] - sin(angle[count])*radius_dep);
					angle[count] -= 1.0f;
					radius_dep -= radius_inc[count]/100;
				}
				if (radius_dep <= radius[count])
				{
					pass = 1;
				}
			}
			else if (which_dir[count] == 0)
			{
				while (radius_dep <= radius[count])
				{
					glVertex2f(yes_circle[count][0] + (cos(angle[count])*radius_dep), yes_circle[count][1] + sin(angle[count])*radius_dep);
					angle[count] += 1.0f;
					radius_dep += radius_inc[count] / 100;
				}
				if (radius_dep >= radius[count] && radius[count] < 100)
				{
					pass = 1;
				}
			}
		}
		glEnd();
		radius_dep = 0;
		++count;
	}
	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);//윈도우 API처럼 좌표 바꾸기 (0,0)이 맨 왼쪽 위임
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		trigger[num] = 1;
		if (num == 10)
		{
			num = 0;
			yes_circle[num][0] = x;
			yes_circle[num][1] = y;
			yes_circle[num][2] = x + 100;
			yes_circle[num][3] = y;
			radius[num] = 0;
			angle[num] = 0;
			which_dir[num] = 0;
			radius_inc[num] = 0.5;
		}
		else
		{
			yes_circle[num][0] = x;
			yes_circle[num][1] = y;
			yes_circle[num][2] = x + 100;
			yes_circle[num][3] = y;
			radius[num] = 0;
			angle[num] = 0;
			which_dir[num] = 0;
			radius_inc[num] = 0.5;
		}
		++num;
	}
}

void timer_func(int value)
{
	for (int check = 0; check < 10; ++check)
	{
		if (trigger[check] == 1)
		{
			if (which_dir[check] == 1)
			{
				radius[check] -= radius_inc[check]/100;
				radius_inc[check] -= 0.5;
				//angle[check] -= 5.0f;
			}
			else
			{
				if (radius[check] >= 100)
				{
					which_dir[check] = 1;
					//angle[check] = 180.0f;
				}
				else
				{
					radius[check] += radius_inc[check]/100;
					radius_inc[check] += 0.5;
					//angle[check] += 5.0f;
				}
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, timer_func, 1);
}