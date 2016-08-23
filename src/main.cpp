#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "spectator.hpp"
#include "hexapod.hpp"

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void idle();
void mouseMove(int x, int y);
void mousePressed(int button, int state, int x, int y);
void mousePressedMove(int x, int y);

std::shared_ptr<Spectator> spectator;
std::shared_ptr<Field> field;
std::shared_ptr<Hexapod> hexapod;
Vertex mousePos;
bool mouseRotating = false;
bool mouseMoving = false;
bool paused = false;

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(w, h);
	glutCreateWindow("Hexapod 0.0");
	// glClearColor(0, 0, 0, 0);
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, static_cast<double>(static_cast<double>(w) / static_cast<double>(h)), 10.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mousePressedMove);

	field = std::make_shared<Field>(20, 10, 1, true);
	spectator = std::make_shared<Spectator>(field);
	hexapod = std::make_shared<Hexapod>();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutFullScreen();
	glutMainLoop();
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	field->render();
	hexapod->render();
	// spectator->look();
	hexapod->look();
	// spectator->render();
	glutSwapBuffers();
}

void timer(int)
{
	if (!paused)
	{
		hexapod->advance();
	}
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
	if (key == ' ')
	{
		paused = !paused;
	}
	spectator->keyPressed(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	spectator->keyRelease(key);
}

void idle()
{
	// spectator->rotate(Vertex((mousePos.x() - 1000) / 100, (mousePos.y() - 500) / 100, 0));
}

void mouseMove(int x, int y)
{
	mousePos = Vertex(x, y, 0);
}

void mousePressed(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseRotating = !mouseRotating;
	}
	if (button == GLUT_MIDDLE_BUTTON)
	{
		mouseMoving = !mouseMoving;
	}
	mousePos = Vertex (x, y, 0);
	if (state == GLUT_DOWN)
	{
		if (button == 3)
		{
			spectator->zoom(-1);
		}
		if (button == 4)
		{
			spectator->zoom(1);
		}
	}
}

void mousePressedMove(int x, int y)
{
	if (mouseRotating)
	{
		spectator->rotate(Vertex (x, y, 0) - mousePos);
	}
	if (mouseMoving)
	{
		spectator->move(Vertex (x, y, 0) - mousePos);
	}
	mousePos = Vertex (x, y, 0);
}
