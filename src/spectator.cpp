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
}

Spectator::~Spectator()
{

}

void Spectator::advance()
{
	const double PI = acos(-1);
	if (keys[static_cast<int>('w')])
	{
		speed += Vertex (cos(direction) * 0.5, sin(direction) * 0.5, 0);
	}
	if (keys[static_cast<int>('s')])
	{
		speed -= Vertex (cos(direction) * 0.5, sin(direction) * 0.5, 0);
	}
	if (keys[static_cast<int>('a')])
	{
		speed += Vertex (cos(direction + PI / 2) * 1, sin(direction + PI / 2) * 1, 0);
	}
	if (keys[static_cast<int>('d')])
	{
		speed -= Vertex (cos(direction + PI / 2) * 1, sin(direction + PI / 2) * 1, 0);
	}
	if (position.z() < 50)
	{
		position.z() = 50;
	}
	if (keys[static_cast<int>(' ')])
	{
		if (position.z() == 50)
		{
			speed.z() += 20;
		}
	}
	speed.z() -= 1;
	speed /= 1.01;

	Vertex eye = position;
	eye -= Vertex (cos(direction) * - 200, sin(direction) * -200, position.z() + 100);
	position += speed;
	if (position.z() < 50)
	{
		position.z() = 50;
		speed.z() = 0;
	}
	glLoadIdentity();
	gluLookAt(-1500, 0, 300, position.x(), position.y(), position.z(), 0, 0, 1);
}

void Spectator::render()
{
	glPushMatrix();
	glColor3d(1, 1, 1);
	GLUquadric* quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_LINE);
	glTranslated(position.x(), position.y(), position.z());
	gluSphere(quad, 50, 20, 20);

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