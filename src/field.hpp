#ifndef __FIELD_HPP__
#define __FIELD_HPP__

class Field
{
public:
	Field(int width, int length, int height, bool bouncing = true);
	~Field();

	void render();

private:

	friend class Spectator;

	int cellSize;

	int width;
	int length;
	int height;

	int rWidth;
	int rLength;
	int rHeight;

	bool bouncing;
};

#endif