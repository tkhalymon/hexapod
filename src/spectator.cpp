#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>

#include "spectator.hpp"

Spectator::Spectator(std::shared_ptr<Field> field) : field (field)
{
	boost = 0.2;
	invertMouseControls = true;
	size = 50;
	minDistance = 100;
	distance = 600;
	position = Vertex(0, 0, 50);
	acc = Vertex(0, 0, 0);
	direction = Vector(0, -0.3, 0);
	directionSpeed = Vector(0, 0, 0);
	directionAcc = Vector(0, 0, 0);
	for (int i = 0; i < 255; ++i)
	{
		keys[i] = false;
	}
	eye = Vertex (position.x() + cos(direction.lat()) * -distance, position.y() + sin(direction.lat()) * -distance, 0);
}

Spectator::~Spectator()
{

}

void Spectator::advance()
{

	handleControlls();

	eye = (Vertex (position.x() - cos(direction.lat()) * cos(direction.lon()) * distance,
	       position.y() - sin(direction.lat()) * cos(direction.lon()) * distance,
	       position.z() - sin(direction.lon()) * distance));
	
	acc += accDeriv;
	speed += acc;
	position += speed;

	directionAcc += directionAccDeriv;
	directionSpeed += directionAcc;
	distanceAcc += distanceAccDeriv;
	distanceSpeed += distanceAcc;
	distance += distanceSpeed;
	if (distance < minDistance)
	{
		distance = minDistance;
	}
	direction.lat() += directionSpeed.lat() / 50;
	direction.lon() += directionSpeed.lon() / 50;
	direction.rot() += directionSpeed.rot() / 50;

	static const double PI = acos(-1); 

	if (direction.lon() > PI / 2.001)
	{
		direction.lon() = PI / 2.001;
		directionSpeed.lon() = 0;
	}
	if (direction.lon() < -PI / 2.001)
	{
		direction.lon() = -PI / 2.001;
		directionSpeed.lon() = 0;
	}

	if (field->bouncing)
	{
		wallBounce();
	}
	else
	{
		wallApproach();
	}
	
	acc /= 1.1;
	speed /= 1.1;

	distanceAcc /= 1.1;
	distanceSpeed /= 1.1;

	directionAcc.lat() /= 1.1;
	directionAcc.lon() /= 1.1;
	directionAcc.rot() /= 1.1;

	directionSpeed.lat() /= 1.1;
	directionSpeed.lon() /= 1.1;
	directionSpeed.rot() /= 1.1;
}

void Spectator::render()
{
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glColor3d(0.7, 0.7, 0.7);
	glTranslated(position.x(), position.y(), position.z());

		glRotated(90, 1, 0, 0);
		glRotated(direction.lat() / acos(-1) * 180 - 90, 0, 1, 0);
		// glRotated(direction.rot() / acos(-1) * 180 - 90, 0, 0, 1);
		// glRotated(direction.lon() / acos(-1) * 180 - 90, 0, 1, 0);
		GLUquadric* quad = gluNewQuadric();
		gluQuadricDrawStyle(quad, GLU_LINE);
		gluSphere(quad, 50, 20, 20);

	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}

void Spectator::look()
{
	glLoadIdentity();
	gluLookAt(eye.x(), eye.y(), eye.z(), position.x(), position.y(), position.z(), 0, sin(direction.rot()), cos(direction.rot()));
}

void Spectator::keyPressed(const unsigned char& key)
{
	keys[key] = true;
}

void Spectator::keyRelease(const unsigned char& key)
{
	keys[key] = false;
}

void Spectator::wallBounce()
{
	if (position.x() < -field->rWidth + size && speed.x() < 0)
	{
		position.x() = -field->rWidth + size;
		speed.x() *= -0.9;
		acc.x() *= 0;
	}
	if (position.y() < -field->rLength + size && speed.y() < 0)
	{
		position.y() = -field->rLength + size;
		speed.y() *= -0.9;
		acc.y() *= 0;
	}
	if (position.x() > field->rWidth - size && speed.x() > 0)
	{
		position.x() = field->rWidth - size;
		speed.x() *= -0.9;
		acc.x() *= 0;
	}
	if (position.y() > field->rLength - size && speed.y() > 0)
	{
		position.y() = field->rLength - size;
		speed.y() *= -0.9;
		acc.y() *= 0;
	}
}

void Spectator::wallApproach()
{
	
}

void Spectator::handleControlls()
{
	// other controls
	// if (keys[static_cast<int>('w')] && !keys[static_cast<int>('s')])
	// {
	// 	speed += Vertex (cos(direction.lat()) * boost, sin(direction.lat()) * boost, 0);
	// }
	// if (keys[static_cast<int>('s')] && !keys[static_cast<int>('w')])
	// {
	// 	speed -= Vertex (cos(direction.lat()) * boost, sin(direction.lat()) * boost, 0);
	// }
	// if (keys[static_cast<int>('a')] && !keys[static_cast<int>('d')])
	// {
	// 	speed += Vertex (cos(direction.lat() + PI / 2) * boost, sin(direction.lat() + PI / 2) * boost, 0);
	// }
	// if (keys[static_cast<int>('d')] && !keys[static_cast<int>('a')])
	// {
	// 	speed += Vertex (cos(direction.lat() - PI / 2) * boost, sin(direction.lat() - PI / 2) * boost, 0);
	// }
	// if (keys[static_cast<int>('z')])
	// {
	// 	direction.lat() += 0.05;
	// }
	// if (keys[static_cast<int>('c')])
	// {
	// 	direction.lat() -= 0.05;
	// }


	static const double PI = acos(-1); 

	accDeriv *= 0;
	directionAccDeriv = Vector(0, 0, 0);

	if (keys[static_cast<int>('w')])
	{
		accDeriv = Vector(direction.lat(), /*direction.lon()*/0, 0) * boost / 2;
	}

	if (keys[static_cast<int>('s')])
	{
		accDeriv = Vector(direction.lat(), /*direction.lon()*/0, 0) * -boost / 2;
	}
	
	if (keys[static_cast<int>('a')])
	{
		accDeriv = Vector(direction.lat() + PI / 2, 0, 0) * boost / 2;
		// directionAccDeriv.lat(boost / 10);
	}

	if (keys[static_cast<int>('d')])
	{
		accDeriv = Vector(direction.lat() - PI / 2, 0, 0) * boost / 2;
		// directionAccDeriv.lat(-boost / 10);
	}

	if (keys[static_cast<int>(' ')])
	{
		speed /= 1.1;
	}
}

void Spectator::rotate(Vertex mouseMove)
{
	if (mouseMove.l() > 5)
	{
		mouseMove *= 5 / mouseMove.l();
	}
	directionAcc.lat() = pow(mouseMove.x() / 3., 3) / 20. * (1. - invertMouseControls * 2.);
	directionAcc.lon() = pow(mouseMove.y() / 3., 3) / 20. * (1. - invertMouseControls * 2.);
}

void Spectator::move(Vertex mouseMove)
{
	static const double PI = acos(-1);
	acc *= 0;
	acc += Vector (direction.lat() + PI / 2, 0, 0) * mouseMove.x() / 1 * boost;
	acc += Vector (direction.lat(), direction.lon() + PI / 2, 0) * mouseMove.y() / 1 * boost;
}

void Spectator::zoom(int dir)
{
	if (dir > 0)
	{
		distanceAcc = sqrt(distance) * 0.1;
	}
	else
	{
		distanceAcc = -sqrt(distance) * 0.1;
	}
}