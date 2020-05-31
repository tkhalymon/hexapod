#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

#include "spectator.hpp"

Spectator::Spectator(std::shared_ptr<Field> field) : field (field)
{
	boost = 0.2;
	invertMouseControls = true;
	minDistance = 100;
	distance = 600;
	position = Vertex(0, 0, 50);
	acc = Vertex(0, 0, 0);
	direction = Vector(0, -0.3, 0);
	directionSpeed = Vector(0, 0, 0);
	directionAcc = Vector(0, 0, 0);
	eye = Vertex (position.x() + cos(direction.lon()) * -distance, position.y() + sin(direction.lon()) * -distance, 0);
}

Spectator::~Spectator()
{

}

void Spectator::advance()
{
	eye = (Vertex (position.x() - cos(direction.lon()) * cos(direction.lat()) * distance,
	       position.y() - sin(direction.lon()) * cos(direction.lat()) * distance,
	       position.z() - sin(direction.lat()) * distance));
	
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
	direction.lon() += directionSpeed.lon() / 50;
	direction.lat() += directionSpeed.lat() / 50;
	direction.rot() += directionSpeed.rot() / 50;

	if (direction.lat() > M_PI / 2.1)
	{
		direction.lat() = M_PI / 2.1;
		directionSpeed.lat() = 0;
	}
	if (direction.lat() < -M_PI / 2.1)
	{
		direction.lat() = -M_PI / 2.1;
		directionSpeed.lat() = 0;
	}

	if (field->bouncing)
	{
		wallBounce();
	}
	else
	{
		wallApproach();
	}
	
	acc /= 1.2;
	speed /= 1.1;

	distanceAcc /= 1.1;
	distanceSpeed /= 1.1;

	directionAcc.lon() /= 1.1;
	directionAcc.lat() /= 1.1;
	directionAcc.rot() /= 1.1;

	directionSpeed.lon() /= 1.1;
	directionSpeed.lat() /= 1.1;
	directionSpeed.rot() /= 1.1;

	accDeriv *= 0;
	directionAccDeriv = Vector(0, 0, 0);
}

void Spectator::render()
{
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glColor3d(0.7, 0.7, 0.7);
	glTranslated(position.x(), position.y(), position.z());

		glRotated(90, 1, 0, 0);
		glRotated(direction.lon() / acos(-1) * 180 - 90, 0, 1, 0);
		// glRotated(direction.rot() / acos(-1) * 180 - 90, 0, 0, 1);
		// glRotated(direction.lat() / acos(-1) * 180 - 90, 0, 1, 0);
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

void Spectator::wallBounce()
{
	if (position.x() < -field->rWidth && speed.x() < 0)
	{
		position.x() = -field->rWidth;
		speed.x() *= -0.9;
		acc.x() *= 0;
	}
	if (position.y() < -field->rLength && speed.y() < 0)
	{
		position.y() = -field->rLength;
		speed.y() *= -0.9;
		acc.y() *= 0;
	}
	if (position.x() > field->rWidth && speed.x() > 0)
	{
		position.x() = field->rWidth;
		speed.x() *= -0.9;
		acc.x() *= 0;
	}
	if (position.y() > field->rLength && speed.y() > 0)
	{
		position.y() = field->rLength;
		speed.y() *= -0.9;
		acc.y() *= 0;
	}
}

void Spectator::wallApproach()
{
	
}

void Spectator::forward()
{
	accDeriv = Vector(direction.lon(), /*direction.lat() * */0, 0) * boost / 5;
}
void Spectator::backward()
{
	accDeriv = Vector(direction.lon(), /*direction.lat() * */0, 0) * -boost / 5;
}

void Spectator::left()
{
	accDeriv = Vector(direction.lon() + M_PI / 2, 0, 0) * boost / 5;
}

void Spectator::right()
{
	accDeriv = Vector(direction.lon() - M_PI / 2, 0, 0) * boost / 5;
}

void Spectator::rotate(Vertex mouseMove)
{
	if (mouseMove.l() > 5)
	{
		mouseMove *= 5 / mouseMove.l();
	}
	directionAcc.lon() = pow(mouseMove.x() / 3., 3) / 20. * (1. - invertMouseControls * 2.);
	directionAcc.lat() = pow(mouseMove.y() / 3., 3) / 20. * (1. - invertMouseControls * 2.);
}

void Spectator::move(Vertex mouseMove)
{
	acc *= 0;
	acc += Vector (direction.lon() + M_PI / 2, 0, 0) * mouseMove.x() / 1 * boost;
	acc += Vector (direction.lon(), direction.lat() + M_PI / 2, 0) * mouseMove.y() / 1 * boost;
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