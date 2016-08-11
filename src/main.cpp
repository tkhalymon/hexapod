#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "spectator.hpp"

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

Spectator spectator;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	int w = glutGet(GLUT_SCREEN_WIDTH) / 2;
	int h = glutGet(GLUT_SCREEN_HEIGHT) / 2;
	glutInitWindowSize(w, h);
	glutCreateWindow("Spectator 0.1");
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, (double)((double)w / (double)h), 1.0, 1000000.0);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	gluLookAt(-1500, 0, 300, 100, 100, 0, 0, 0, 1);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMainLoop();
	return 0;
}

void drawGrid()
{
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for (int i = -1000; i <= 1000; i += 50)
	{
		glVertex3d(-1000, i, 0);
		glVertex3d(1000, i, 0);

		glVertex3d(i, -1000, 0);
		glVertex3d(i, 1000, 0);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	spectator.render();
	glutSwapBuffers();
}

void timer(int)
{
	spectator.advance();
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}
	spectator.keyPressed(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	spectator.keyRelease(key);
}
