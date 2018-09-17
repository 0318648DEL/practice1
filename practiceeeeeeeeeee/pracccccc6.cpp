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
void turn_clockwise(int squr_num);
void go_right(int squr_num);
void go_left(int squr_num);
void go_down(int squr_num);
void go_up(int squr_num,int normal);
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
	glutPostRedisplay();//??�ٽ� �׸���??
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
		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
	}
}

void go_right_back(int squr_num, int normal)
{
	if (squr_loc[squr_num][0] <= normal)
	{
		rand_dir_x[squr_num] = 10;
		rand_dir_y[squr_num] = 0;
		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
	}
}

void go_left(int squr_num)
{
	if (squr_loc[squr_num][0] >= 0)
	{
		rand_dir_x[squr_num] = -10;
		rand_dir_y[squr_num] = 0;
		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
	}
}

void go_up(int squr_num, int normal)
{
	if (squr_loc[squr_num][1] >= normal)
	{
		rand_dir_x[squr_num] = 0;
		rand_dir_y[squr_num] = -10;
		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
	}
}

void go_down(int squr_num)
{
	if (squr_loc[squr_num][1] <= 600)
	{
		rand_dir_x[squr_num] = 0;
		rand_dir_y[squr_num] = 10;
		glutTimerFunc(100, timer_func, 1);//Ÿ�̸� ȣ�� �ٽ�
	}
}

void timer_func(int value)//Ÿ�̸� ȣ��
{
	int timer = 0;//1~10���� ���� �� ���� �ɰ� ������ ����
	while (timer < 9)//10���� ����
	{
		if (squr_loc[timer][0] <= 0 || squr_loc[timer][1] <= 0 || squr_loc[timer][0] >= 800 || squr_loc[timer][1] >= 600)//x��ǥ�� 0�� 800, y��ǥ�� 0�� 600���� �� �߿� �ϳ��� �ɸ��� �ٷ� �Ʒ���
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