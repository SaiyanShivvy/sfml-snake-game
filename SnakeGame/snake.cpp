#include "snake.h"
#include "coord.h"
#include <iostream>
#include <deque> //Used to manage snake body, found it a bit easier than vectors
#include <math.h>
#include <cstdlib>
#include <time.h>

using namespace std;

SNAKE::SNAKE() {
	asnake.push_front(COORD(25, 25)); //Inital position of the snake
	asnake.push_front(COORD(50, 25));
	asnake.push_front(COORD(75, 25));
	foodCount = 0;
}

//Resets the snake
void SNAKE::reset() {
	asnake.clear();//clears the snake
	asnake.push_front(COORD(25, 25)); //set new snake
	asnake.push_front(COORD(50, 25));
	asnake.push_front(COORD(75, 25));
	asnake.push_front(COORD(100, 25));
	foodCount = 0; //Reset foodCount 
}


//Grows the Snake
void SNAKE::grow() {
	asnake.push_back(COORD(asnake.back().getX(), asnake.back().getY())); //the snake grows using deque function by adding a section to the end of queue
}

//checks for food collision
bool SNAKE::foodCollide(COORD food) {
	if (asnake.front().getX == food.getX() && asnake.front().getY() == food.getY()) { //Checks if the snake is touching the food
		cout << "FOOD EATEN" << endl; //Debug
		return true;
	}
	else {
		return false;
	}
}

//create food










