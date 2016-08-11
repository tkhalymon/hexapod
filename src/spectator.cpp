#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>

#include "spectator.hpp"

Spectator::Spectator()
{
	position = Vertex(0, 0, 50);
	direction = 0;
	for (int i = 0; i < 255; ++i)
	{
		keys[i] = false;
	}
	// eye = position;
	eye = Vertex (cos(direction) * -200, sin(direction) * -200, 300);
}

Spectator::~Spectator()
{

}

void Spectator::advance()
{
	// const double PI = acos(-1);
	double boost = 0.2;
	if (keys[static_cast<int>('w')])
	{
		speed += Vertex (cos(direction) * boost, sin(direction) * boost, 0);
	}
	if (keys[static_cast<int>('s')])
	{
		speed -= Vertex (cos(direction) * boost, sin(direction) * boost, 0);
	}
	if (keys[static_cast<int>('a')])
	{
		// speed += Vertex (cos(direction + PI / 2) * boost, sin(direction + PI / 2) * boost, 0);
		direction += 0.05;
	}
	if (keys[static_cast<int>('d')])
	{
		direction -= 0.05;
		// speed -= Vertex (cos(direction + PI / 2) * boost, sin(direction + PI / 2) * boost, 0);
	}
	speed /= 1.01;

	Vertex expected = (Vertex (position.x() - cos(direction) *  200, position.y() - sin(direction) * 200, position.z() - 50 + 300));
	eye.x() -= (eye.x() - expected.x()) * 0.1;
	eye.y() -= (eye.y() - expected.y()) * 0.1;
	eye.z() -= (eye.z() - expected.z()) * 0.1;
	if (keys[static_cast<int>(' ')])
	{
		speed = Vertex(0, 0, 0);
	}
	position += speed;
	if (position.x() < -950 && speed.x() < 0)
	{
		speed.x() *= -0.9;
	}
	if (position.y() < -950 && speed.y() < 0)
	{
		speed.y() *= -0.9;
	}
	if (position.x() > 950 && speed.x() > 0)
	{
		speed.x() *= -0.9;
	}
	if (position.y() > 950 && speed.y() > 0)
	{
		speed.y() *= -0.9;
	}
	if (position.z() < -400)
	{
		position.z() = -400;
	}
	if (position.z() > 400)
	{
		position.z() = 400;
	}
	glLoadIdentity();
	gluLookAt(eye.x(), eye.y(), eye.z(), position.x(), position.y(), 50, 0, 0, 1);
}

void Spectator::render()
{
	glPushMatrix();
	glColor3d(1, 1, 1);
	glTranslated(position.x(), position.y(), 50);
	glRotated(direction / acos(-1) * 180 - 90, 0, 0, 1);

		GLUquadric* quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_LINE);
		gluSphere(quad, 50, 5, 5);

	glPopMatrix();
}

void Spectator::keyPressed(const unsigned char& key)
{
	keys[key] = true;
}

void Spectator::keyRelease(const unsigned char& key)
{
	keys[key] = false;
}

void Spectator::startPos(int y)
{
	moveYpos = y;
}

void Spectator::moveY(int y)
{
	position.z() -= (moveYpos - y) * 0.1;
}
