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
	void rotatePaw(int paw, int servo, double angle);

private:

	void renderBody();
	
	enum PawIndexes { LF = 0, RF = 1, LM = 2, RM = 3, LB = 4, RB = 5 };

	Vertex position;
	Vertex speed;
	Vertex acc;
	Vertex accDeriv;

	Vector direction;
	Vector directionSpeed;
	Vector directionAcc;
	Vector directionAccDeriv;

	Paw* paws[6];

};

#endif