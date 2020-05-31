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
	void look();

	void forward();
	void backward();
	void left();
	void right();

	void rotate(Vertex mouseMove);
	void move(Vertex mouseMove);
	void zoom(int direction);

private:

	void wallBounce();
	void wallApproach();

	Vertex position;
	Vertex speed;
	Vertex acc;
	Vertex accDeriv;
	
	Vertex eye;
	
	Vector direction;
	Vector directionSpeed;
	Vector directionAcc;
	Vector directionAccDeriv;
	
	double minDistance;

	double distance;
	double distanceSpeed;
	double distanceAcc;
	double distanceAccDeriv;

	std::shared_ptr<Field> field;

	double boost;

	bool invertMouseControls;
};

#endif