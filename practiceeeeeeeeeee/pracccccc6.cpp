#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

/*���̤������̷�;�ӳ���
�ϱ� ������ �ؾ� �Ѵ� �����ϱ� �׼� ���� �ϳ� �ؾ������ ȭ�� ���� �׷��� �Ѵٰ� �ù�
���� ������ �߰��Ȱ� �ſ� ��ٷο�� ���� �������� �ܶ�
�ð質 �ݽð� ���� ȸ���� �Լ��� �����ϰ� p�� ���� �Ҹ��� �𸣰ڴ�
���� ���������
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


int squr_loc[10][2] = { 0, };//�簢�� �߾� ��ǥ
int size_x[10] = { 0, };//ũ�� x������
int size_y[10] = { 0, };//ũ�� y������
int color[10][3] = { 0, };//����
int size_ch[10] = { 0, };//ũ�� ���� ��ȯ
int rand_dir_x[10] = { 0, };//x��ǥ �̵�
int rand_dir_y[10] = { 0, };//y��ǥ �̵�
int speed_mul[10] = { 1, 1,1,1,1,1,1,1,1,1 };//�ӵ� ���
int rev = 0;//ũ�� �پ��°� üũ
int num = 0;//�簢�� ī��Ʈ
int trigger[10] = { 0, };//�丮��
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
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//������ �Ķ��Ķ�
	glClear(GL_COLOR_BUFFER_BIT);//������ �̰�
	int count = 0;

	while (count < 9 && trigger[count] == 1)//���� �ٲٴ� �κа� �簢�� �׸��� �κ�
	{
		glColor4ub(color[count][0], color[count][1], color[count][2], 200);//���� �׸��䵥 ���� �ô� �Ŷ� �� �ٸ��� ���´�. �� ����
		glRecti(squr_loc[count][0] - size_x[count], squr_loc[count][1] - size_y[count], squr_loc[count][0] + size_x[count], squr_loc[count][1] + size_y[count]);//�簢���̴�
		count++;
	}

	glFlush();//���!
}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);//������ APIó�� ��ǥ �ٲٱ� (0,0)�� �� ���� ����
}

void keyboard(unsigned char key, int x, int y)//Ű���� �Է¹���
{
	int check = 0;//�˻�˻�
	int all = 0;
	switch (key)//�Է¹��� Ű
	{
	case '+'://q�� ��� ����
		while (trigger[check] == 1)
		{
			if (speed_mul[check] < 10)
			{
				++speed_mul[check];
			}
			++check;
		}
		break;
	case '-'://s�� ��� ����
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
	glutPostRedisplay();//??�ٽ� �׸���??
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)//���� ���콺 ��ư ����
	{
		trigger[num] = 1;//��ư ������ üũ �� �׷� 0���� �ʱ�ȭ �� �ڸ����� �׷���
		if (num == 10)//10����
		{
			num = 0;
			squr_loc[num][0] = x;//x��ǥ
			squr_loc[num][1] = y;//y��ǥ
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
	glutPostRedisplay();//??�ٽ� �׸���??
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
//		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
//	}
//}
//
//void go_left(int squr_num)
//{
//	if (squr_loc[squr_num][0] >= 0)
//	{
//		rand_dir_x[squr_num] = -10;
//		rand_dir_y[squr_num] = 0;
//		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
//	}
//}
//
//void go_up(int squr_num, int normal)
//{
//	if (squr_loc[squr_num][1] >= normal)
//	{
//		rand_dir_x[squr_num] = 0;
//		rand_dir_y[squr_num] = -10;
//		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
//	}
//}
//
//void go_down(int squr_num)
//{
//	if (squr_loc[squr_num][1] <= 600)
//	{
//		rand_dir_x[squr_num] = 0;
//		rand_dir_y[squr_num] = 10;
//		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
//	}
//}

void timer_func(int value)//Ÿ�̸� ȣ��
{
	int timer = 0;//1~10���� ���� �� ���� �ɰ� ������ ����
	while (timer < 9)//10���� ����
	{
		if ((squr_loc[timer][0] <= 0 || squr_loc[timer][1] <= 0 || squr_loc[timer][0] >= 800 || squr_loc[timer][1] >= 600) && turn_clockwise[timer + 1] == 0)//x��ǥ�� 0�� 800, y��ǥ�� 0�� 600���� �� �߿� �ϳ��� �ɸ��� �ٷ� �Ʒ���
		{//�̰� �Ƹ� ƨ��� �κ����� ��������� ��ǥ üũ�� ƨ��°�
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
		color[timer][0] = rand() % 250 + 5;//��ȣ
		color[timer][1] = rand() % 250 + 5;//����
		color[timer][2] = rand() % 250 + 5;//��ȯ

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

		switch (size_ch[timer])//������ �ٲٱ� �̰͵� ���� ���� ����� ����
		{
		case 0://�ʱ� ����
			size_x[timer] += 5;
			size_y[timer] += 5;
			++size_ch[timer];
			rev = 0;
			break;
		case 1://1�ܰ�
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
		case 2://2�ܰ�
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
		case 3://3�ܰ�
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
		case 4://4�ܰ�
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
		case 5://5�ܰ�
			size_x[timer] -= 5;
			size_y[timer] -= 5;
			--size_ch[timer];
			rev = 1;//�ٽ� �ڷ� ����
			break;
		}
		++timer;
	}
	glutPostRedisplay();//�ٽ� �׸���
	glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
}