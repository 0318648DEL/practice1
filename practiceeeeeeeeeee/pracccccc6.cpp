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
void go_right(int squr_num);
void go_left(int squr_num);
void go_down(int squr_num);
void go_up(int squr_num, int normal);
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
int turn_clockwise[10] = { 0, };
int turned[10] = { 0, };
int normal_loc_x[10] = { 0, };
int normal_loc_y[10] = { 0, };


void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example6");
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
	int all = 0;
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
		while (trigger[check] == 1&&check<9)
		{
			if (speed_mul[check] >= 0)
			{
				speed_mul[check] = 0;
			}
			++check;
		}
		break;
	case 'p':
		while (trigger[check] == 1 && check < 9)
		{
			rand_dir_x[check] = (rand() % 30) - 15;
			rand_dir_y[check] = (rand() % 30) - 15;
			++check;
		}
		break;
	case '0':
		turn_clockwise[0] = 1;
		all = 0;
		while (all < 9)
		{
			turn_clockwise[all + 1] = 1;
			normal_loc_x[all] = squr_loc[all][0];
			normal_loc_y[all] = squr_loc[all][1];
			go_right(all);
			++all;
		}
		break;
	case '1':
		turn_clockwise[1] = 1;
		normal_loc_x[0] = squr_loc[0][0];
		normal_loc_y[0] = squr_loc[0][1];
		go_right(0);
		break;
	case '2':
		turn_clockwise[2] = 1;
		normal_loc_x[1] = squr_loc[1][0];
		normal_loc_y[1] = squr_loc[1][1];
		go_right(1);
		break;
	case '3':
		turn_clockwise[3] = 1;
		normal_loc_x[2] = squr_loc[2][0];
		normal_loc_y[2] = squr_loc[2][1];
		go_right(2);
		break;
	case '4':
		turn_clockwise[4] = 1;
		normal_loc_x[3] = squr_loc[3][0];
		normal_loc_y[3] = squr_loc[3][1];
		go_right(3);
		break;
	case '5':
		turn_clockwise[5] = 1;
		normal_loc_x[4] = squr_loc[4][0];
		normal_loc_y[4] = squr_loc[4][1];
		go_right(4);
		break;
	case '6':
		turn_clockwise[6] = 1;
		normal_loc_x[5] = squr_loc[5][0];
		normal_loc_y[5] = squr_loc[5][1];
		go_right(5);
		break;
	case '7':
		turn_clockwise[7] = 1;
		normal_loc_x[6] = squr_loc[6][0];
		normal_loc_y[6] = squr_loc[6][1];
		go_right(6);
		break;
	case '8':
		turn_clockwise[8] = 1;
		normal_loc_x[7] = squr_loc[7][0];
		normal_loc_y[7] = squr_loc[7][1];
		go_right(7);
		break;
	case '9':
		turn_clockwise[9] = 1;
		normal_loc_x[8] = squr_loc[8][0];
		normal_loc_y[8] = squr_loc[8][1];
		go_right(8);
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
			rand_dir_x[num] = (rand() % 30) - 15;
			rand_dir_y[num] = (rand() % 30) - 15;
		}
		else
		{
			squr_loc[num][0] = x;
			squr_loc[num][1] = y;
			size_x[num] += (rand() % 20) + 5;
			size_y[num] += (rand() % 10) + 5;
			rand_dir_x[num] = (rand() % 30) - 15;
			rand_dir_y[num] = (rand() % 30) - 15;
		}
		++num;
	}
	glutPostRedisplay();//??다시 그리기??
}

//void rand_dir_init(int x, int y)
//{
//	x = (-20 + ((rand() % 10) + 5));
//	y = (-20 + ((rand() % 10) + 5));
//}

void go_right(int squr_num)
{

	rand_dir_x[squr_num] = 10;
	rand_dir_y[squr_num] = 0;

}

//void go_right_back(int squr_num, int normal)
//{
//	if (squr_loc[squr_num][0] <= normal)
//	{
//		rand_dir_x[squr_num] = 10;
//		rand_dir_y[squr_num] = 0;
//		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
//	}
//}
//
//void go_left(int squr_num)
//{
//	if (squr_loc[squr_num][0] >= 0)
//	{
//		rand_dir_x[squr_num] = -10;
//		rand_dir_y[squr_num] = 0;
//		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
//	}
//}
//
//void go_up(int squr_num, int normal)
//{
//	if (squr_loc[squr_num][1] >= normal)
//	{
//		rand_dir_x[squr_num] = 0;
//		rand_dir_y[squr_num] = -10;
//		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
//	}
//}
//
//void go_down(int squr_num)
//{
//	if (squr_loc[squr_num][1] <= 600)
//	{
//		rand_dir_x[squr_num] = 0;
//		rand_dir_y[squr_num] = 10;
//		glutTimerFunc(100, timer_func, 1);//타이머 호출 다시
//	}
//}

void timer_func(int value)//타이머 호출
{
	int timer = 0;//1~10까지 변수 안 만들어도 될거 같은데 만듦
	while (timer < 9)//10까지 돈다
	{
		if ((squr_loc[timer][0] <= 0 || squr_loc[timer][1] <= 0 || squr_loc[timer][0] >= 800 || squr_loc[timer][1] >= 600) && turn_clockwise[timer + 1] == 0)//x좌표는 0과 800, y좌표는 0과 600까지 이 중에 하나라도 걸리면 바로 아래로
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

		if (turn_clockwise[timer + 1] == 1)
		{
			if (squr_loc[timer][0] >= 800 && squr_loc[timer][1] <= 600)
			{
				rand_dir_x[timer] = 0;
				rand_dir_y[timer] = 10;
			}
			else if (squr_loc[timer][1] >= 600 && squr_loc[timer][0] >= 0)
			{
				rand_dir_x[timer] = -10;
				rand_dir_y[timer] = 0;
			}
			else if (squr_loc[timer][0] <= 0 && squr_loc[timer][1] >= normal_loc_y[timer])
			{
				rand_dir_x[timer] = 0;
				rand_dir_y[timer] = -10;
				turned[timer] = 1;
			}
			else if (squr_loc[timer][1] <= normal_loc_y[timer] && squr_loc[timer][0] <= normal_loc_x[timer])
			{
				rand_dir_x[timer] = 10;
				rand_dir_y[timer] = 0;
			}
			else if (turned[timer] == 1)
			{
				rand_dir_x[timer] = (rand() % 30) - 15;
				rand_dir_y[timer] = (rand() % 30) - 15;
				turn_clockwise[timer + 1] = 0;
				turned[timer] = 0;
			}
		}

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