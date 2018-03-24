#pragma once
//enum maybe replaced to keyboard events.


#ifndef SNAKE_H
#define SNAKE_H

#include "coord.h"
#include <iostream>
#include <deque>

using namespace std;

//Declares the Snake Class
class SNAKE {
private:
	enum Direction {UP, DOWN, RIGHT, LEFT}; //Game Control
	std::deque<COORD> asnake; //coord's of the snake, using deque
	int adirection; //Set default direction of snake

public:
	SNAKE(); //for the snake itself
	COORD food(); //food location using COORD class
	bool move(int); //moves the snake
	bool touch(); //used when checking for collision of the snake colliding with itself
	bool eat(); //used to check if the snake collides with the fruit

	void grow(); //grows the snake
	void reset(); //restores snake to initial size

	//int foodCount; //tracks the amount of food eaten.
	int getDirection() {
		return adirection; //returns the current direction of the snake
	}

	//Gets the position of X and Y
	int getX();
	int getY();
	std::deque<COORD> getCoords(); //return the coord of the snake
};


#endif