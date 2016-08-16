#ifndef __PAW_HPP__
#define __PAW_HPP__

#include "vertex.hpp"
#include "vector.hpp"

class Paw
{
public:
	Paw(double x, double y, double z);
	~Paw();

	const Vertex& pos() const;

private:

	Vertex position;
	Vector direction;
};

#endif