#include "vertex.hpp"
#include <iostream>

Vertex::Vertex()
{
	coord = new double[3]();
}

Vertex::Vertex(const Vertex& v)
{
	coord = new double[3];
	coord[0] = v.coord[0];
	coord[1] = v.coord[1];
	coord[2] = v.coord[2];
}

Vertex::Vertex(double x, double y, double z)
{
	coord = new double[3];
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

Vertex::~Vertex()
{
	delete [] coord;
}

const double Vertex::x() const
{
	return coord[0];
}

const double Vertex::y() const
{
	return coord[1];
}

const double Vertex::z() const
{
	return coord[2];
}

void Vertex::x(const double& x)
{
	coord[0] = x;
}

void Vertex::y(const double& y)
{
	coord[1] = y;
}

void Vertex::z(const double& z)
{
	coord[2] = z;
}

void Vertex::operator = (const Vertex& v)
{
	for (int i = 0; i < 3; ++i)
		coord[i] = v.coord[i];
}

void Vertex::operator += (const Vertex& v)
{
	for (int i = 0; i < 3; ++i)
		this->coord[i] += v.coord[i];
}

void Vertex::operator -= (const Vertex& v)
{
	for (int i = 0; i < 3; ++i)
		this->coord[i] -= v.coord[i];
}

void Vertex::operator *= (const double& k)
{
	for (int i = 0; i < 3; ++i)
		this->coord[i] *= k;
}

void Vertex::operator /= (const double& k)
{
	for (int i = 0; i < 3; ++i)
		this->coord[i] /= k;
}
