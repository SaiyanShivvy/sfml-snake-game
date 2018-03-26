#pragma once
#ifndef COORD_H
#define COORD_H

#include "stdafx.h"
#include <iostream>
using namespace std;

//Declares the Class COORD
class COORD {
//private variables
private:
	int ax, ay;

//public functions
public:
	COORD(int, int); //Coordinates that are defined by x and y values
	bool same(COORD c1, COORD c2); //boolean func to check if coords are similar

	//accesors
	int getX();
	int getY();

	//mutators
	void setX(int x);
	void setY(int y);
};
#endif //COORD_H
