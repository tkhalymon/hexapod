#ifndef __SPECTATOR_HPP__
#define __SPECTATOR_HPP__

#include "vertex.hpp"
#include "vector.hpp"

enum Direction { DirLeft, DirRight, DirUp, DirDown };

class Spectator
{
public:
	Spectator();
	~Spectator();

	void advance();
	void render();
	void keyPressed(const unsigned char& key);
	void keyRelease(const unsigned char& key);
	
	void turn(Direction direction, double angle);
	void move(Direction direction, double distance);

private:

	Vertex position;
	Vertex speed;
	Vertex eye;
	
	Vector direction;
	
	bool keys[255];
};

#endif