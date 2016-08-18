#include <GL/glut.h>
#include <math.h>

#include "hexapod.hpp"

const double Hexapod::PI = acos(-1);

Hexapod::Hexapod()
{
	position = Vertex(500, 0, 50);
	paws[LF] = new Paw(-20, 40, 5);
	paws[LM] = new Paw(-30, 0, 5);
	paws[LB] = new Paw(-20, -40, 5);
	paws[RF] = new Paw(20, 40, 5);
	paws[RM] = new Paw(30, 0, 5);
	paws[RB] = new Paw(20, -40, 5);
	// direction = Vector (PI / 3, 0.5, 0.5);
	direction = Vector (0, 0, 0);
}

Hexapod::~Hexapod()
{

}

void Hexapod::advance()
{
	direction.lon() += 0.05;
	direction.rot() += 0.2;
	position += direction * 5;
}

void Hexapod::render()
{
	glColor3d(1, 1, 1);
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glTranslated(position.x(), position.y(), position.z());
	glRotated(-90, 0, 0, 1);
	glRotated(direction.lat() / PI * 180, 0, 0, 1);
	glRotated(direction.lon() / PI * 180, 1, 0, 0);
	glRotated(direction.rot() / PI * 180, 0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z());
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z() - 10);
	}
	glEnd();
	glColor3d(0.8, 0.8, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 7; ++i)
	{
		int j = i % 6;
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z());
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z() - 10);
	}
	glEnd();
	glColor3d(0, 0, 0);
	glLineWidth(2);
	glScaled(1.01, 1.01, 1.01);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z());
	}
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z() - 10);
	}
	glEnd();
	glBegin(GL_LINES);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z());
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z() - 10);
	}
	glEnd();
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}