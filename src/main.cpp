#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "spectator.hpp"

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mousePressed(int button, int state, int x, int y);
void mousePressedMove(int x, int y);

std::shared_ptr<Spectator> spectator;
std::shared_ptr<Field> field;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	int w = glutGet(GLUT_SCREEN_WIDTH) * 0.8;
	int h = glutGet(GLUT_SCREEN_HEIGHT) * 0.8;
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
	glutMouseFunc(mousePressed);
	glutMotionFunc(mousePressedMove);

	field = std::make_shared<Field>(20, 10, 1, true);
	spectator = std::make_shared<Spectator>(field);

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	field->render();
	spectator->render();
	glutSwapBuffers();
}

void timer(int)
{
	spectator->advance();
	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}
	spectator->keyPressed(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	spectator->keyRelease(key);
}

void mousePressed(int button, int state, int x, int y)
{

}

void mousePressedMove(int x, int y)
{
	
}
