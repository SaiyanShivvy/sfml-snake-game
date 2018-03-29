// SnakeGame.cpp : Defines the entry point for the console application.
// Author: Shivneel Achari
// For Unitec, Game Programming, Assignment 1
//

#include "stdafx.h"

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "snake.h"
#include "coord.h"

using namespace std;

enum Direction { UP, DOWN, RIGHT, LEFT, SPACE }; //declares enum
int direction = DOWN;

//functions
int snakeEat(COORD &food, SNAKE &asnake); //snake eats and get score
void snakeReset(bool &run, SNAKE &snake); //resets snake to inital position and restarts game after colliding

//main
int main() {
	//variables
	SNAKE snake; //snake class
	COORD food = snake.food(); //coords of the food
	bool run = true; //game over condition
	bool gamerun = true;

	while (gamerun) {
		sf::Event event;
		sf::Clock clock;

		snake.setDirection(); //initial set direction func
		snake.grow(); //inital growth of snake

		sf::RenderWindow window(sf::VideoMode(950, 800), "SNAKE GAME {Test}");
		window.setKeyRepeatEnabled(false); //disables keys being held down
		window.setFramerateLimit(60); //limits the framerate

		//sfml window loop
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
				}

				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Left) {
						direction = LEFT; //switches snake direction
						snake.move(direction); //calls the move func
					}
					if (event.key.code == sf::Keyboard::Right) {
						direction = RIGHT; //switches snake direction
						snake.move(direction); //calls the move func
					}
					if (event.key.code == sf::Keyboard::Up) {
						direction = UP; //switches snake direction
						snake.move(direction); //calls the move func
					}
					if (event.key.code == sf::Keyboard::Down) {
						direction = DOWN; //switches snake direction
						snake.move(direction); //calls the move func
					}
				}
			}

			//function calls
			snakeEat(food, snake);//detect the food
			snakeReset(run, snake);//resets game after collision

			//clock for the game // still testing that func
			if (clock.getElapsedTime().asMilliseconds() > 100) {
				snake.justAte = false;
			}
			if (clock.getElapsedTime().asMilliseconds() >= 120) {
				run = snake.move(snake.getDirection());
				clock.restart();
			}
			window.clear(sf::Color::Black);

			// SFML Draw elements //

			//draw food
			int x = food.getX(); //coords of the food
			int y = food.getY();

			sf::RectangleShape foodPos(sf::Vector2f(25, 25)); //using rect shape to represent the food
			foodPos.setFillColor(sf::Color::Blue); //color of the food
			foodPos.setPosition(x, y); //sets the coord of the food
			window.draw(foodPos); //draws to screen

			//draws the snake
			for (unsigned int i = 1; i < (snake.getCoords().size()); i++) {
				int x = (snake.getCoords()[i].getX());
				int y = (snake.getCoords()[i].getY());

				sf::RectangleShape coord(sf::Vector2f(24, 24));
				coord.setFillColor(sf::Color::Green); //color of snake
				coord.setPosition(x, y); //sets the x and y coords of the snake
				window.draw(coord); //draws the snake
			}

			//calc food count
			int snakecore = snake.foodCount;

			window.display();
		}
		return 0;
	}
}

//increase snake size
int snakeEat(COORD &food, SNAKE &snake) {
	if (snake.foodCollide(food)) {
		snake.grow(); //makes the snake grow after it collides with food
		food = snake.food();
		snake.justAte = true;
		cout << "FOOD COUNT: " << snake.foodCount << endl; //debug

		return snake.foodCount++;
	}
}

//reset the game
void snakeReset(bool &run, SNAKE &snake) {
	if (!run) {
		snake.setDirection(); //sets the default direction
		snake.reset();
		run = true;
		cout << "Game Over!" << endl; //debug
	}
}