#include "paw.hpp"

Paw::Paw(double x, double y, double z) : position(x, y, z)
{

}

Paw::~Paw()
{

}

const Vertex& Paw::pos() const
{
	return position;
}