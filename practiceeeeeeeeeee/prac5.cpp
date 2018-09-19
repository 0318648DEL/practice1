#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>

/*20180915 오늘의 목표
5번 조지기 제에발 뒤로 미루지 말자 좀
할거 많으니까 존나 힘든건 내 몸 뿐이잖아
이 시팔롬아 이거 쓸 시간에 빨리 순서 구성이나 해라*/

/*와! 충돌체크! 와! 뒹기기!
속도랑 방향이 완전 무작위라는데 음 이거 어떻게 하지
속도값과 방향값을 사각형 하나하나마다 다 적용되야 하므로
일단 각각 일차원 배열 10개를 만들어 준다
음
아 근데 그러면 잠깐만
방향값이 아니라 사각형을 그리는 좌표가 바뀌어야 하는데
좌표의 변동값이라고 해야겠다 그걸 x와 y로 나누어서 하나씩 일차원 배열 10만큼의 크기
이렇게 되면 속도 빨라지는건 음 요 변동값에다가 곱하면 되나
어차피 속도 변동이 일괄적으로 적용되야 하니까 그러면 이게 더 편할지도
만들어야 할꺼 x좌표 변동값[10],y좌표 변동값[10], 속도 배수[10]
야호! 그럼 이걸 어떻게 써먹어야 할까
아 귀찮지만 과제니까 조지면 안된다 그러므로 해야함
기본적인 구조는 완전 동일, 하지만 추가할게 생겨서 고려할게 몇 개 생겨남. 썅
일정한 시간마다 타이머가 호출, 그리고 시간마다 색깔과 크기만 바뀌는게 아니라 움직이기까지함
그럼 타이머 쪽에다가 색깔과 크기, 이동 방향과 속도를 전부 때려박아야함
색깔과 크기는 이미 있으니, 필요한건 이동 방향과 속도와 !충돌체크! 개 중요함 이거 안 하면 조짐
음 순서를 어떻게 두지, 일단 우선적으로 충돌체크부터 해야 하겠지
그러면 그 다음에 이동 방향을 결정해야 겠지, 그래야 튕겨나갈꺼 아니냐
고 다음에 속도랑 색깔이랑 크기 막 하면 되겠지
아 크기 정사각형 싫다, 이것도 짬나면 바꿔보자
아 맞다 키보드 입력도 받아야 한다*/

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void timer_func(int value);
void rand_dir_init(int x, int y);

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
int change = 0;



void main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example5");
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, timer_func, 1);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//바탕색 파랑파랑
	glClear(GL_COLOR_BUFFER_BIT);//뭐였지 이거
	int count = 0;

	while (count < 10 && trigger[count] == 1)//색깔 바꾸는 부분과 사각형 그리기 부분
	{
		if (change == 1)
		{
			glColor4ub(color[count][0], color[count][1], color[count][2], 200);//색깔 그리긴데 내가 봤던 거랑 좀 다르게 나온다. 안 예쁨
			glBegin(GL_TRIANGLES);
			glVertex2i(squr_loc[count][0] - size_x[count], squr_loc[count][1] + size_y[count]);
			glVertex2i(squr_loc[count][0], squr_loc[count][1] - size_y[count]);
			glVertex2i(squr_loc[count][0] + size_x[count], squr_loc[count][1] + size_y[count]);
			glEnd();
		}
		else
		{
			glColor4ub(color[count][0], color[count][1], color[count][2], 200);//색깔 그리긴데 내가 봤던 거랑 좀 다르게 나온다. 안 예쁨
			glRecti(squr_loc[count][0] - size_x[count], squr_loc[count][1] - size_y[count], squr_loc[count][0] + size_x[count], squr_loc[count][1] + size_y[count]);//사각형이다
		}
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
	case 'q'://q의 경우 증가
		while (trigger[check]==1)
		{
			if (speed_mul[check] < 10)
			{
				++speed_mul[check];
			}
			++check;
		}
		break;
	case 's'://s의 경우 감소
		while (trigger[check] == 1)
		{
			if (speed_mul[check] > 0)
			{
				--speed_mul[check];
			}
			++check;
		}
		break;
	case 't':
		if (change == 0)
		{
			change = 1;
		}
		else
		{
			change = 0;
		}
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

void timer_func(int value)//타이머 호출
{
	int timer = 0;//1~10까지 변수 안 만들어도 될거 같은데 만듦
	while (timer < 10)//10까지 돈다
	{
		if (squr_loc[timer][0] <= 0 || squr_loc[timer][1] <= 0 || squr_loc[timer][0] >= 800 || squr_loc[timer][1] >= 600)//x좌표는 0과 800, y좌표는 0과 600까지 이 중에 하나라도 걸리면 바로 아래로
		{//이게 아마 튕기는 부분으로 만들었을껄 좌표 체크랑 튕기는거
			if (squr_loc[timer][0] <= 0)
			{
				rand_dir_x[timer] = (rand() % 10) + 5;
			}
			else if (squr_loc[timer][0]>=800)
			{
				rand_dir_x[timer] = -(rand() % 10) - 5;
			}

			if (squr_loc[timer][1] <=0)
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