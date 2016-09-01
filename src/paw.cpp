#include <GL/glut.h>
#include <math.h>

#include "paw.hpp"

#define __USE_MATH_DEFINES

Paw::Paw(double x, double y, double z, double lon) : position(x, y, z), direction(lon + M_PI / 2, M_PI / 3, 0)
{
	angle = 0;
	a = rand() % 100;
	// a = 0;
}

Paw::~Paw()
{

}

void Paw::render()
{
	a += 0.1;
	angle = cos(a) * 50 + 20;
	glPushMatrix();
	static GLUquadricObj *quadric = gluNewQuadric();
	// gluQuadricDrawStyle(quadric, GLU_LINE);
	glTranslated(position.x(), position.y(), position.z() - 5);
	glColor3d(0.3, 0.3, 0.3);
	gluSphere(quadric, 5, 10, 10);
	glRotated(direction.lon() / M_PI * 180, 0, 0, 1);
	glRotated(direction.lat() / M_PI * 180 + angle, 0, -1, 0);
	glRotated(180, 0, 1, 0);
	gluCylinder(quadric, 5, 5, 30, 10, 1);
	glTranslated(0, 0, 30);
	gluSphere(quadric, 5, 10, 10);
	glPopMatrix();
}

const Vertex& Paw::pos() const
{
	return position;
}
