#ifndef __SPECTATOR_HPP__
#define __SPECTATOR_HPP__

#include "vertex.hpp"

class Spectator
{
public:
	Spectator();
	~Spectator();

	void advance();
	void render();
	void keyPressed(const unsigned char& key);
	void keyRelease(const unsigned char& key);
	
	void startPos(int y);
	void moveY(int y);

private:

	Vertex position;
	Vertex speed;
	Vertex eye;
	double direction;
	double directionSpeed;
	int moveYpos;
	bool keys[255];
};

#endif