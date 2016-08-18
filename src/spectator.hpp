#ifndef __SPECTATOR_HPP__
#define __SPECTATOR_HPP__

#include "vertex.hpp"
#include "vector.hpp"
#include "field.hpp"
#include <memory>

enum Direction { DirLeft, DirRight, DirUp, DirDown };
enum ControlMode { DefaultView, PlaneView };

class Spectator
{
public:
	Spectator(std::shared_ptr<Field> field);
	~Spectator();

	void advance();
	void render();

	void keyPressed(const unsigned char& key);
	void keyRelease(const unsigned char& key);
	
	void rotate(Vertex mouseMove);
	void move(Direction direction, double distance);

private:

	void wallBounce();
	void wallApproach();
	void handleControlls();

	Vertex position;
	Vertex speed;
	Vertex acc;
	Vertex accDeriv;
	
	Vertex eye;
	
	Vector direction;
	Vector directionSpeed;
	Vector directionAcc;
	Vector directionAccDeriv;
	
	std::shared_ptr<Field> field;

	int size;

	double boost = 0.2;

	bool keys[255];
};

#endif