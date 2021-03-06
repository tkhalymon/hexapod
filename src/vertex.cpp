#include <iostream>
#include <math.h>
#include "vertex.hpp"

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

double& Vertex::x() const
{
	return coord[0];
}

double& Vertex::y() const
{
	return coord[1];
}

double& Vertex::z() const
{
	return coord[2];
}

const double Vertex::l() const
{
	return sqrt(coord[0] * coord[0] + coord[1] * coord[1] + coord[2] * coord[2]);
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

const Vertex Vertex::operator + (const Vertex& v) const
{
	return Vertex(coord[0] + v.coord[0], coord[1] + v.coord[1], coord[2] + v.coord[2]);
}

const Vertex Vertex::operator - (const Vertex& v) const
{
	return Vertex(coord[0] - v.coord[0], coord[1] - v.coord[1], coord[2] - v.coord[2]);
}

const Vertex Vertex::operator * (const double& k) const
{
	return Vertex (coord[0] * k, coord[1] * k, coord[2] * k);
}

const Vertex Vertex::operator / (const double& k) const
{
	return Vertex (coord[0] / k, coord[1] / k, coord[2] / k);
}
