#include <GL/glut.h>
#include <math.h>

#include "paw.hpp"

#define __USE_MATH_DEFINES

Paw::Paw(double x, double y, double z, double lat) : position(x, y, z), direction(lat + M_PI / 2, M_PI / 3, 0)
{

}

Paw::~Paw()
{

}

void Paw::render()
{
	glPushMatrix();
	glTranslated(position.x(), position.y(), position.z() - 10);
	glRotated(direction.lat() / M_PI * 180, 0, 0, 1);
	glRotated(direction.lon() / M_PI * 180, 0, -1, 0);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(30, 0, 0);
	glEnd();
	glPopMatrix();
}

const Vertex& Paw::pos() const
{
	return position;
}
