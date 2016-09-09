#include <GL/glut.h>
#include <math.h>

#include "paw.hpp"

Paw::Paw(double x, double y, double z, double lon) : position(x, y, z), direction(lon + M_PI / 2, 3 * M_PI / 4, 0)
{
	length[0] = 25;
	length[1] = 40;
	hangle = 0;
	angle[0] = 0;
	angle[1] = -130;
	a = rand() % 100;
}

Paw::~Paw()
{

}

void Paw::advance()
{
	a += 0.1;
	angle[0] = cos(a) * 30;
	hangle = sin(a) * 30;
}

void Paw::render()
{
	glPushMatrix();
	static GLUquadricObj *quadric = gluNewQuadric();
	// gluQuadricDrawStyle(quadric, GLU_LINE);
	glTranslated(position.x(), position.y(), position.z() - 5);
	glColor3d(1.0, 1.0, 1.0);
	glRotated(direction.lon() / M_PI * 180 + hangle, 0, 0, 1);
	glRotated(direction.lat() / M_PI * 180 + angle[0], 0, -1, 0);
	glRotated(180, 0, 1, 0);
	gluSphere(quadric, 5, 50, 50);
	gluCylinder(quadric, 5, 5, length[0], 50, 1);
	glTranslated(0, 0, length[0]);
	gluSphere(quadric, 5, 50, 50);
	glRotated( + angle[1], 0, -1, 0);
	glTranslated(0, 0, 0.3);
	gluCylinder(quadric, 5, 2, length[1] - 2, 50, 1);
	glTranslated(0, 0, length[1] - 2);
	glScaled(1, 1, 2);
	glColor3d(0.1, 0.1, 0.1);
	gluSphere(quadric, 2, 50, 50);
	glPopMatrix();
}

const Vertex& Paw::pos() const
{
	return position;
}
