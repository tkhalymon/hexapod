#ifndef __HEXAPOD_H__
#define __HEXAPOD_H__

#include "paw.hpp"
#include "vertex.hpp"
#include "vector.hpp"

class Hexapod
{
public:
	Hexapod();
	~Hexapod();

	void advance();
	void render();
	void look();

private:

	enum PawIndexes { LF = 0, LM = 1, LB = 2, RB = 3, RM = 4, RF = 5 };

	Vertex position;
	Vertex speed;
	Vertex acc;
	Vertex accDeriv;

	Vector direction;
	Vector directionSpeed;
	Vector directionAcc;
	Vector directionAccDeriv;

	Paw* paws[6];

	static const double PI;
};

#endif