#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/*일단 원의 갯수가 1개 이상이니까 원의 원점 저장하는건 배열로 만든다 치는데
어음 그리는걸 어떻게 해야하나 일정 반지름 이상이 되면 시작점에서 다시 원이 퍼져나간다고?
음 이거 순서가 어떻게 되는 거지
마우스 좌클릭->클릭한데 좌표 저장->반지름 늘어남->늘어나면서 점도 같이 찍음->특정 반지름 체크->시작점에서부터 또 점찍기 시작
변수를 몇개 더 만들어야 겠네.
맨 처음의 원[10개 정도]
음 일정 반지름이라 함은 어느정도 넘으면 다시 반지름을 0으로 초기화하란 얘긴가
그리고 몇개는 이런거 안하고 그냥 퍼져가면서 사라지는데 색깔이 다름
그럼 그냥 원 변수[10개]하고 반복하는 원이랑 퍼져나가는 원이랑 구별해놔야 겠다
그럼 처음에 찍었을 때 반복원인지 퍼지는 원인지 구별하는 변수 하나더*/

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
}//타이머 호출