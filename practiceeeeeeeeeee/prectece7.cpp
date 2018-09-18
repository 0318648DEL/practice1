#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/*�ϴ� ���� ������ 1�� �̻��̴ϱ� ���� ���� �����ϴ°� �迭�� ����� ġ�µ�
���� �׸��°� ��� �ؾ��ϳ� ���� ������ �̻��� �Ǹ� ���������� �ٽ� ���� ���������ٰ�?
�� �̰� ������ ��� �Ǵ� ����
���콺 ��Ŭ��->Ŭ���ѵ� ��ǥ ����->������ �þ->�þ�鼭 ���� ���� ����->Ư�� ������ üũ->�������������� �� ����� ����
������ � �� ������ �ڳ�.
�� ó���� ��[10�� ����]
�� ���� �������̶� ���� ������� ������ �ٽ� �������� 0���� �ʱ�ȭ�϶� ��䰡
�׸��� ��� �̷��� ���ϰ� �׳� �������鼭 ������µ� ������ �ٸ�
�׷� �׳� �� ����[10��]�ϰ� �ݺ��ϴ� ���̶� ���������� ���̶� �����س��� �ڴ�
�׷� ó���� ����� �� �ݺ������� ������ ������ �����ϴ� ���� �ϳ���*/

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void timer_func(int value);

int yeah_circle[10][2] = { 0, };
int radius[10] = { 0, };
int trigger[10] = { 0, };
int which_circ[10] = { 0, };
int color[10][3] = { 0, };
double angle[10] = { 0, };
int num = 0;


void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example7");
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
	while (count < 10 && trigger[count] == 1)
	{
		glBegin(GL_POINTS);
		glColor3ub(color[count][0], color[count][1], color[count][2]);
		for (angle[count] = 0.0f; angle[count] < 360.0f; angle[count] += 5.0f)
		{
			glVertex2f(yeah_circle[count][0]+(cos(angle[count])*radius[count]), yeah_circle[count][1]+(sin(angle[count])*radius[count]));
		}
		glEnd();
		++count;
	}
	glFlush();
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);//������ APIó�� ��ǥ �ٲٱ� (0,0)�� �� ���� ����
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		trigger[num] = 1;
		if (num == 10)
		{
			num = 0;
			yeah_circle[num][0] = x;
			yeah_circle[num][1] = y;
			radius[num] = 0;
			which_circ[num] = rand() % 2;
			if (which_circ[num] == 1)
			{
				color[num][0] = 0;
				color[num][1] = 0;
				color[num][2] = 255;
			}
			else
			{
				color[num][0] = 255;
				color[num][1] = 0;
				color[num][2] = 0;
			}
		}
		else
		{
			yeah_circle[num][0] = x;
			yeah_circle[num][1] = y;
			radius[num] = 0;
			which_circ[num] = rand() % 2;
			if (which_circ[num] == 1)
			{
				color[num][0] = 0;
				color[num][1] = 0;
				color[num][2] = 255;
			}
			else
			{
				color[num][0] = 255;
				color[num][1] = 0;
				color[num][2] = 0;
			}
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
			if (which_circ[check] == 1 && ((yeah_circle[check][0] + radius[check] <= 800 || yeah_circle[check][0] - radius[check] >= 0) || (yeah_circle[check][1] + radius[check] <= 600 || yeah_circle[check][1] + radius[check] >= 0)))
			{
				radius[check] += 10;
			}
			else if (which_circ[check] == 0)
			{
				radius[check] += 10;
				radius[check] = radius[check] % 200;
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, timer_func, 1);
}//Ÿ�̸� ȣ��