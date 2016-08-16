#include <GL/glut.h>
#include "field.hpp"

Field::Field(int width, int length, int height, bool bouncing) : width(width), length(length), height(height), bouncing(bouncing)
{
	cellSize = 100;
	rWidth = width * cellSize;
	rLength = length * cellSize;
	rHeight = height * cellSize;
}

Field::~Field()
{

}

void Field::render()
{
	glPushMatrix();
	glScaled(cellSize, cellSize, cellSize);
	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	
	// grid
	for (int i = -length; i <= length; i++)
	{
		glVertex3d(-width, i, 0);
		glVertex3d(width, i, 0);
	}
	for (int i = -width; i <= width; i++)
	{
		glVertex3d(i, -length, 0);
		glVertex3d(i, length, 0);
	}

	// forward and back vertical border lines
	for (int i = -length; i <= length; i++)
	{
		glVertex3d(-width, i, 0);
		glVertex3d(-width, i, height);

		glVertex3d(width, i, 0);
		glVertex3d(width, i, height);
	}

	// left and right vertical border lines
	for (int i = -width; i <= width; i++)
	{
		glVertex3d(i, -length, 0);
		glVertex3d(i, -length, height);

		glVertex3d(i, length, 0);
		glVertex3d(i, length, height);
	}

	// horizontal border lines
	for (int i = 0; i <= height; i++)
	{
		// left
		glVertex3d(-width, length, i);
		glVertex3d(width, length, i);

		// right
		glVertex3d(width, -length, i);
		glVertex3d(-width, -length, i);

		// forward
		glVertex3d(width, length, i);
		glVertex3d(width, -length, i);

		// back
		glVertex3d(-width, -length, i);
		glVertex3d(-width, length, i);
	}
	glEnd();
	glPopMatrix();
}
