#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

/*끼이ㅏ럼ㄴ이럼;ㅣ나얼
하기 싫지만 해야 한다 과제니까 겜수 과제 하나 잊어버려서 화가 난다 그래서 한다고 시바
히든 문제라 추가된게 매우 까다로운거 같다 귀찮은게 잔뜩
시계나 반시계 방향 회전은 함수로 땜빵하고 p는 무슨 소린지 모르겠다
내일 물어봐야지
*/

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void timer_func(int value);
void rand_dir_init(int x, int y);
void turn_clockwise(int squr_num);
void go_right(int squr_num);
void go_left(int squr_num);
void go_down(int squr_num);
void go_up(int squr_num,int normal);
void go_right_back(int squr_num, int normal);


int squr_loc[10][2] = { 0, };//사각형 중앙 좌표
int size_x[10] = { 0, };//크기 x쪽으로
int size_y[10] = { 0, };//크기 y쪽으로
int color[10][3] = { 0, };//색깔
int size_ch[10] = { 0, };//크기 상태 변환
int rand_dir_x[10] = { 0, };//x좌표 이동
int rand_dir_y[10] = { 0, };//y좌표 이동
int speed_mul[10] = { 1, 1,1,1,1,1,1,1,1,1 };//속도 배수
int rev = 0;//크기 줄어드는거 체크
int num = 0;//사각형 카운트
int trigger[10] = { 0, };//토리가



void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example4");
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer_func, 1);
	//glutTimerFunc(100, turn_clockwise, 2);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//바탕색 파랑파랑
	glClear(GL_COLOR_BUFFER_BIT);//뭐였지 이거
	int count = 0;

	while (count < 9 && trigger[count] == 1)//색깔 바꾸는 부분과 사각형 그리기 부분
	{
		glColor4ub(color[count][0], color[count][1], color[count][2], 200);//색깔 그리긴데 내가 봤던 거랑 좀 다르게 나온다. 안 예쁨
		glRecti(squr_loc[count][0] - size_x[count], squr_loc[count][1] - size_y[count], squr_loc[count][0] + size_x[count], squr_loc[count][1] + size_y[count]);//사각형이다
		count++;
	}

	glFlush();//출력!
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);//윈도우 API처럼 좌표 바꾸기 (0,0)이 맨 왼쪽 위임
}

void keyboard(unsigned char key, int x, int y)//키보드 입력받음
{
	int check = 0;//검사검사
	switch (key)//입력받은 키
	{
	case '+'://q의 경우 증가
		while (trigger[check] == 1)
		{
			if (speed_mul[check] < 10)
			{
				++speed_mul[check];
			}
			++check;
		}
		break;
	case '-'://s의 경우 감소
		while (trigger[check] == 1)
		{
			if (speed_mul[check] > 0)
			{
				--speed_mul[check];
			}
			++check;
		}
		break;
	case 's':
		while (trigger[check] == 1)
		{
			if (speed_mul[check] > 0)
			{
				speed_mul[check] = 0;
			}
			++check;
			break;
		}
	case '0':
		turn_clockwise(0);
		rand_dir_init(rand_dir_x[0], rand_dir_y[0]);
		break;
	case '1':
		turn_clockwise(1);
		rand_dir_init(rand_dir_x[1], rand_dir_y[1]);
		break;
	case '2':
		turn_clockwise(2);
		rand_dir_init(rand_dir_x[2], rand_dir_y[2]);
		break;
	case '3':
		turn_clockwise(3);
		rand_dir_init(rand_dir_x[3], rand_dir_y[3]);
		break;
	case '4':
		turn_clockwise(4);
		rand_dir_init(rand_dir_x[4], rand_dir_y[4]);
		break;
	case '5':
		turn_clockwise(5);
		rand_dir_init(rand_dir_x[5], rand_dir_y[5]);
		break;
	case '6':
		turn_clockwise(6);
		rand_dir_init(rand_dir_x[6], rand_dir_y[6]);
		break;
	case '7':
		turn_clockwise(7);
		rand_dir_init(rand_dir_x[7], rand_dir_y[7]);
		break;
	case '8':
		turn_clockwise(8);
		rand_dir_init(rand_dir_x[8], rand_dir_y[8]);
		break;
	case '9':
		turn_clockwise(9);
		rand_dir_init(rand_dir_x[9], rand_dir_y[9]);
		break;
	}
	glutPostRedisplay();//??다시 그리기??
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//왼쪽 마우스 버튼 눌림
	{
		trigger[num] = 1;//버튼 눌린거 체크 안 그럼 0으로 초기화 한 자리에서 그려짐
		if (num == 10)//10까지
		{
			num = 0;
			squr_loc[num][0] = x;//x좌표
			squr_loc[num][1] = y;//y좌표
			size_x[num] += (rand() % 20) + 5;
			size_y[num] += (rand() % 10) + 5;
			rand_dir_init(rand_dir_x[num], rand_dir_y[num]);
		}
		else
		{
			squr_loc[num][0] = x;
			squr_loc[num][1] = y;
			size_x[num] += (rand() % 20) + 5;
			size_y[num] += (rand() % 10) + 5;
			rand_dir_init(rand_dir_x[num], rand_dir_y[num]);
		}
		++num;
	}
	glutPostRedisplay();//??다시 그리기??
}

void rand_dir_init(int x, int y)
{
	x = (-20 + ((rand() % 10) + 5));
	y = (-20 + ((rand() % 10) + 5));
}

void turn_clockwise(int squr_num)
{
	int normal_pos_x = squr_loc[squr_num][0];
	int normal_pos_y = squr_loc[squr_num][1];

	go_right(squr_num);
	go_down(squr_num);
	go_left(squr_num);
	go_up(squr_num, normal_pos_y);
	go_right_back(squr_num, normal_pos_x);
}

void go_right(int squr_num)
{
	while (squr_loc[squr_num][0] <= 800)
	{
		rand_dir_x[squr_num] = 10;
		rand_dir_y[squr_num] = 0;
		glutPostRedisplay();
		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
	}
}

void go_right_back(int squr_num, int normal)
{
	if (squr_loc[squr_num][0] <= normal)
	{
		rand_dir_x[squr_num] = 10;
		rand_dir_y[squr_num] = 0;
		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
	}
}

void go_left(int squr_num)
{
	if (squr_loc[squr_num][0] >= 0)
	{
		rand_dir_x[squr_num] = -10;
		rand_dir_y[squr_num] = 0;
		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
	}
}

void go_up(int squr_num, int normal)
{
	if (squr_loc[squr_num][1] >= normal)
	{
		rand_dir_x[squr_num] = 0;
		rand_dir_y[squr_num] = -10;
		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
	}
}

void go_down(int squr_num)
{
	if (squr_loc[squr_num][1] <= 600)
	{
		rand_dir_x[squr_num] = 0;
		rand_dir_y[squr_num] = 10;
		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
	}
}

void timer_func(int value)//타이머 호출
{
	int timer = 0;//1~10까지 변수 안 만들어도 될거 같은데 만듦
	while (timer < 9)//10까지 돈다
	{
		if (squr_loc[timer][0] <= 0 || squr_loc[timer][1] <= 0 || squr_loc[timer][0] >= 800 || squr_loc[timer][1] >= 600)//x좌표는 0과 800, y좌표는 0과 600까지 이 중에 하나라도 걸리면 바로 아래로
		{//이게 아마 튕기는 부분으로 만들었을껄 좌표 체크랑 튕기는거
			if (squr_loc[timer][0] <= 0)
			{
				rand_dir_x[timer] = (rand() % 10) + 5;
			}
			else if (squr_loc[timer][0] >= 800)
			{
				rand_dir_x[timer] = -(rand() % 10) - 5;
			}

			if (squr_loc[timer][1] <= 0)
			{
				rand_dir_y[timer] = (rand() % 10) + 5;
			}
			else if (squr_loc[timer][1] >= 600)
			{
				rand_dir_y[timer] = -(rand() % 10) - 5;
			}
		}
		color[timer][0] = rand() % 250 + 5;//야호
		color[timer][1] = rand() % 250 + 5;//색깔
		color[timer][2] = rand() % 250 + 5;//변환

		squr_loc[timer][0] += (rand_dir_x[timer] * speed_mul[timer]);
		squr_loc[timer][1] += (rand_dir_y[timer] * speed_mul[timer]);

		switch (size_ch[timer])//사이즈 바꾸기 이것도 굳이 변수 만든거 같다
		{
		case 0://초기 상태
			size_x[timer] += 5;
			size_y[timer] += 5;
			++size_ch[timer];
			rev = 0;
			break;
		case 1://1단계
			if (rev == 1)
			{
				size_x[timer] -= 5;
				size_y[timer] -= 5;
				--size_ch[timer];
			}
			else
			{
				size_x[timer] += 5;
				size_y[timer] += 5;
				++size_ch[timer];
			}
			break;
		case 2://2단계
			if (rev == 1)
			{
				size_x[timer] -= 5;
				size_y[timer] -= 5;
				--size_ch[timer];
			}
			else
			{
				size_x[timer] += 5;
				size_y[timer] += 5;
				++size_ch[timer];
			}
			break;
		case 3://3단계
			if (rev == 1)
			{
				size_x[timer] -= 5;
				size_y[timer] -= 5;
				--size_ch[timer];
			}
			else
			{
				size_x[timer] += 5;
				size_y[timer] += 5;
				++size_ch[timer];
			}
			break;
		case 4://4단계
			if (rev == 1)
			{
				size_x[timer] -= 5;
				size_y[timer] -= 5;
				--size_ch[timer];
			}
			else
			{
				size_x[timer] += 5;
				size_y[timer] += 5;
				++size_ch[timer];
			}
			break;
		case 5://5단계
			size_x[timer] -= 5;
			size_y[timer] -= 5;
			--size_ch[timer];
			rev = 1;//다시 뒤로 간다
			break;
		}
		++timer;
	}
	glutPostRedisplay();//다시 그리기
	glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
}