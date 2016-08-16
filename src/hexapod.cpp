#include <GL/glut.h>

#include "hexapod.hpp"

Hexapod::Hexapod()
{
	position = Vertex(500, 0, 50);
	paws[LF] = new Paw(-20, 40, 5);
	paws[LM] = new Paw(-30, 0, 5);
	paws[LB] = new Paw(-20, -40, 5);
	paws[RF] = new Paw(20, 40, 5);
	paws[RM] = new Paw(30, 0, 5);
	paws[RB] = new Paw(20, -40, 5);
}

Hexapod::~Hexapod()
{

}

void Hexapod::advance()
{

}

void Hexapod::render()
{
	glColor3d(1, 1, 1);
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glTranslated(position.x(), position.y(), position.z());
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
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 7; ++i)
	{
		int j = i % 6;
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z());
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z() - 10);
	}
	glEnd();
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}