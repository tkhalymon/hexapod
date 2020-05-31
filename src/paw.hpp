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

	const Vertex getEndPos();

	void rotate (int servo, double angle);

	// void move (double hangle, double angle1, double angle2);

private:
	Vertex position;
	Vector direction;
	double angle[3];
	double length[2];
	double a;
};

#endif