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

private:

	Vertex position;
	Vertex speed;
	double direction;

	bool keys[255];
};

#endif