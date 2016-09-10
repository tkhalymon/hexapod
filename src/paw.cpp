#include <GL/glut.h>
#include <math.h>

#include "paw.hpp"

Paw::Paw(double x, double y, double z, double lon) : position(x, y, z), direction(lon + M_PI / 2, 0, 0)
{
	length[0] = 25;
	length[1] = 40;
	angle[0] = 0;
	angle[1] = 135;
	angle[2] = -130;
	// a = rand() % 100;
}

Paw::~Paw()
{

}

void Paw::advance()
{
	
}

void Paw::render()
{
	glPushMatrix();
	static GLUquadricObj *quadric = gluNewQuadric();
	// gluQuadricDrawStyle(quadric, GLU_LINE);
	glTranslated(position.x(), position.y(), position.z() - 5);
	glColor3d(1.0, 1.0, 1.0);
	glRotated(direction.lon() / M_PI * 180 + angle[0], 0, 0, 1);
	glRotated(angle[1], 0, -1, 0);
	glRotated(180, 0, 1, 0);
	gluSphere(quadric, 5, 50, 50);
	gluCylinder(quadric, 5, 5, length[0], 50, 1);
	glTranslated(0, 0, length[0]);
	gluSphere(quadric, 5, 50, 50);
	glRotated( + angle[2], 0, -1, 0);
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

const Vertex Paw::getEndPos()
{
	double dir = direction.lon();
	Vertex end = Vertex(
		cos(angle[0] + dir) * (sin(angle[1] / 180 * M_PI) * length[0] + sin((angle[1] + angle[2]) / 180 * M_PI) * (length[1] + 2)),
		sin(angle[0] + dir) * (sin(angle[1] / 180 * M_PI) * length[0] + sin((angle[1] + angle[2]) / 180 * M_PI) * (length[1] + 2)),
		-cos(angle[1] / 180 * M_PI) * length[0] - cos((angle[1] + angle[2]) / 180 * M_PI) * (length[1] + 2) - 5
	);
	return position + end;
}

void Paw::rotate (int servo, double ang)
{
	angle[servo] += ang;
	switch (servo)
	{
	case 0:
		if (angle[servo] < -30) angle[servo] = -30;
		if (angle[servo] > 30) angle[servo] = 30;
		break;
	case 1:
		if (angle[servo] < 90) angle[servo] = 90;
		if (angle[servo] > 155) angle[servo] = 155;
		break;
	case 2:
		if (angle[servo] < -150) angle[servo] = -150;
		if (angle[servo] > -90) angle[servo] = -90;
		break;
	}
}