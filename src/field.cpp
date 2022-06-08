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
    renderFloor();
    renderWalls();
	glPopMatrix();
}

void Field::renderFloor()
{
    glColor3d(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex3d(-rWidth, -rLength, 0);
        glVertex3d(-rWidth, rLength, 0);
        glVertex3d(rWidth, rLength, 0);
        glVertex3d(rWidth, -rLength, 0);
    glEnd();
    glScaled(cellSize, cellSize, cellSize);

    glColor3d(0, 0, 0);
    glBegin(GL_LINES);
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
    glEnd();
}

void Field::renderWalls()
{
    glColor3d(0.5, 0.5, 0.5);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(-width, -length, 0);
    glVertex3d(-width, -length, height);
    glVertex3d(-width, length, 0);
    glVertex3d(-width, length, height);
    glVertex3d(width, length, 0);
    glVertex3d(width, length, height);
    glVertex3d(width, -length, 0);
    glVertex3d(width, -length, height);
    glVertex3d(-width, -length, 0);
    glVertex3d(-width, -length, height);
    glEnd();
    glColor3d(0., 0., 0.);
    glBegin(GL_LINES);
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
}
