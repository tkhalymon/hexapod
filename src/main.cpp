#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <math.h>
#include "spectator.hpp"
#include "hexapod.hpp"

void display();
void timer(int);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void keyboardSpecial(int key, int x, int y);
void keyboardSpecialUp(int key, int x, int y);
void idle();
void mouseMove(int x, int y);
void mousePressed(int button, int state, int x, int y);
void mousePressedMove(int x, int y);

std::shared_ptr<Spectator> spectator;
std::shared_ptr<Field> field;
std::shared_ptr<Hexapod> hexapod;

std::vector<unsigned char> pressedKeys;

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
	glClearColor(0.7, 0.7, 0.7, 0);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60, static_cast<double>(static_cast<double>(w) / static_cast<double>(h)), 10.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);

	glutDisplayFunc(display);
	glutTimerFunc(20, timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecial);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mousePressed);
	glutMotionFunc(mousePressedMove);

	field = std::make_shared<Field>(5, 5, 1, false);
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
	spectator->look();
	// hexapod->look();
	glutSwapBuffers();
}

int rotationDir;

void timer(int)
{
	for (std::vector<unsigned char>::iterator i = pressedKeys.begin(); i != pressedKeys.end(); ++i)
	{
		switch (*i)
		{
		case 'w': spectator->forward(); break;
		case 's': spectator->backward(); break;
		case 'a': spectator->left(); break;
		case 'd': spectator->right(); break;
		case '4': hexapod->rotatePaw(4, 0, 1 * rotationDir); break;
		case 'r': hexapod->rotatePaw(4, 1, 1 * rotationDir); break;
		case 'f': hexapod->rotatePaw(4, 2, 1 * rotationDir); break;
		case '5': hexapod->rotatePaw(2, 0, 1 * rotationDir); break;
		case 't': hexapod->rotatePaw(2, 1, 1 * rotationDir); break;
		case 'g': hexapod->rotatePaw(2, 2, 1 * rotationDir); break;
		case '6': hexapod->rotatePaw(0, 0, 1 * rotationDir); break;
		case 'y': hexapod->rotatePaw(0, 1, 1 * rotationDir); break;
		case 'h': hexapod->rotatePaw(0, 2, 1 * rotationDir); break;

		case '7': hexapod->rotatePaw(1, 0, -1 * rotationDir); break;
		case 'u': hexapod->rotatePaw(1, 1, 1 * rotationDir); break;
		case 'j': hexapod->rotatePaw(1, 2, 1 * rotationDir); break;
		case '8': hexapod->rotatePaw(3, 0, -1 * rotationDir); break;
		case 'i': hexapod->rotatePaw(3, 1, 1 * rotationDir); break;
		case 'k': hexapod->rotatePaw(3, 2, 1 * rotationDir); break;
		case '9': hexapod->rotatePaw(5, 0, -1 * rotationDir); break;
		case 'o': hexapod->rotatePaw(5, 1, 1 * rotationDir); break;
		case 'l': hexapod->rotatePaw(5, 2, 1 * rotationDir); break;
		
		case '0': for (int j=0;j<6;j++)hexapod->rotatePaw(j, 0, -1 * rotationDir); break;
		case 'p': for (int j=0;j<6;j++)hexapod->rotatePaw(j, 1, 1 * rotationDir); break;
		case ';': for (int j=0;j<6;j++)hexapod->rotatePaw(j, 2, 1 * rotationDir); break;
		}
	}
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
	rotationDir = glutGetModifiers() == 4 ? 1 : -1;
	if (key == 27)
	{
		exit(0);
	}
	if (key == ' ')
	{
		paused = !paused;
	}
	pressedKeys.push_back(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	rotationDir = glutGetModifiers() == 4 ? 1 : -1;
	for (std::vector<unsigned char>::iterator i = pressedKeys.begin(); i != pressedKeys.end(); ++i)
	{
		if (*i == key)
		{
			pressedKeys.erase(i);
			break;
		}
	}
}

void keyboardSpecial(int key, int x, int y)
{
	
}

void keyboardSpecialUp(int key, int x, int y)
{

}

void idle()
{
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
