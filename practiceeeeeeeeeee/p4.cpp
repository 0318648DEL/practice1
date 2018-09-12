#include "pch.h"
#include <gl/freeglut.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

GLvoid drawScene(GLvoid);
GLvoid reshape(int w, int h);
void mouse(int button, int state, int x, int y);

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example4");
	glutDisplayFunc(drawScene);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

GLvoid drawScene()
{

}

GLvoid reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glOrtho(0, 800, 600, 0, -1, 1);
}

void mouse(int button, int state, int x, int y)
{

}