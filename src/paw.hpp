#ifndef __PAW_HPP__
#define __PAW_HPP__

#include "vertex.hpp"
#include "vector.hpp"

class Paw
{
public:
	Paw(double x, double y, double z, double lat);
	~Paw();

	void advance();

	void render();

	const Vertex& pos() const;

	// void move (double hangle, double angle1, double angle2);

private:
	Vertex position;
	Vector direction;
	double hangle;
	double angle[2];
	double length[2];
	double a;
};

#endif