#include <GL/glut.h>
#include <math.h>

#include "hexapod.hpp"


Hexapod::Hexapod()
{
	position = Vertex(0, 0, 50);
	paws[LF] = new Paw(-20, 40, 5, M_PI / 3);
	paws[LM] = new Paw(-30, 0, 5, M_PI / 2);
	paws[LB] = new Paw(-20, -40, 5, 2 * M_PI / 3);
	paws[RF] = new Paw(20, 40, 5, -M_PI / 3);
	paws[RM] = new Paw(30, 0, 5, -M_PI / 2);
	paws[RB] = new Paw(20, -40, 5, -2 * M_PI / 3);
	direction = Vector (0, 0, 0);
}

Hexapod::~Hexapod()
{

}

void Hexapod::advance()
{

}

void Hexapod::render()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);
	float specular[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	// glNormal3d(0, 0, 1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glTranslated(position.x(), position.y(), position.z());
	glRotated(-90, 0, 0, 1);
	glColor3d(1, 1, 1);
	glRotated(direction.lon() / M_PI * 180, 0, 0, 1);
	glRotated(direction.lat() / M_PI * 180, 1, 0, 0);
	glRotated(direction.rot() / M_PI * 180, 0, 1, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z() - 10);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; ++i)
	{
		glVertex3d(paws[i]->pos().x(), paws[i]->pos().y(), paws[i]->pos().z());
	}
	glEnd();
	// glColor4d(0.8, 0.8, 0.8, 0.5);
	// glColor3d(1, 1, 1);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 7; ++i)
	{
		int j = i % 6;
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z());
		glVertex3d(paws[j]->pos().x(), paws[j]->pos().y(), paws[j]->pos().z() - 10);
	}
	glEnd();
	glColor3d(0.1, 0.1, 0.1);
	glLineWidth(2);
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
	for (int i = 0; i < 6; ++i)
	{
		paws[i]->render();
	}
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Hexapod::look()
{
	glLoadIdentity();
	Vertex eye = position - direction * 200;
	double lon = direction.lon();
	double lat = direction.lat();
	double rot = direction.rot();
	Vertex normal = Vertex(-sin(rot + M_PI / 2) * sin(lat), -cos(rot - M_PI / 2), sin(rot + M_PI / 2) * cos(lat));
	double len = sqrt(pow(normal.x(), 2) + pow(normal.y(), 2));
	double angle = normal.y() < 0 ? acos(normal.x() / len) : 2 * M_PI - acos(normal.x() / len);
	angle -= lon;
	normal.x() = cos(angle) * len;
	normal.y() = -sin(angle) * len;
	eye += normal * 100;
	gluLookAt(eye.x(), eye.y(), eye.z(), position.x(), position.y(), position.z(), normal.x(), normal.y(), normal.z());
}
