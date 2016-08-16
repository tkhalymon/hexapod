#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "spectator.hpp"
#include "hexapod.hpp"

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mousePressed(int button, int state, int x, int y);
void mousePressedMove(int x, int y);

Spectator spectator;
Hexapod hexapod;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	int w = glutGet(GLUT_SCREEN_WIDTH) * 0.8;
	int h = glutGet(GLUT_SCREEN_HEIGHT) * 0.8;
	glutInitWindowSize(w, h);
	glutCreateWindow("Spectator 0.1");
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, static_cast<double>(static_cast<double>(w) / static_cast<double>(h)), 10.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mousePressedMove);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	
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
	for (int i = -1000; i <= 1000; i += 50)
	{
		glVertex3d(-1000, i, 0);
		glVertex3d(-1000, i, 200);

		glVertex3d(1000, i, 0);
		glVertex3d(1000, i, 200);

		glVertex3d(i, -1000, 0);
		glVertex3d(i, -1000, 200);

		glVertex3d(i, 1000, 0);
		glVertex3d(i, 1000, 200);
	}
	for (int i = 0; i <= 200; i += 50)
	{
		glVertex3d(-1000, 1000, i);
		glVertex3d(1000, 1000, i);

		glVertex3d(1000, 1000, i);
		glVertex3d(1000, -1000, i);

		glVertex3d(1000, -1000, i);
		glVertex3d(-1000, -1000, i);

		glVertex3d(-1000, -1000, i);
		glVertex3d(-1000, 1000, i);

	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawGrid();
	hexapod.render();
	spectator.render();
	glutSwapBuffers();
}

void timer(int)
{
	spectator.advance();
	hexapod.advance();
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

void mousePressed(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		// spectator.startPos(y);
	}
}

void mousePressedMove(int x, int y)
{
	// spectator.moveY(y);
}
