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

enum GameState { MENU, LEAVE, PLAY, GAMEOVER };
enum Direction { UP, DOWN, RIGHT, LEFT, SPACE, W, S, A, D }; //declares enum
int direction = DOWN;

//functions
int snakeEat(COORD &food, SNAKE &asnake); //snake eats and get score
void snakeReset(bool &run, SNAKE &snake); //resets snake to inital position and restarts game after colliding
void warpSnake(SNAKE &snake, sf::RenderWindow &window); //should act like a portal and allow the snake to warp around the window
void mainGame(GameState &CurrentState);

//variables
SNAKE snake; //snake class
COORD food = snake.food(); //coords of the food
bool run = true; //game over condition

//main
int main() {
	GameState CurrentState; //Initalizes Game State
	CurrentState = MENU; //Sets the currentstate
	srand(time(NULL)); //gets a random seed
	//sf::Event event;
	char res;
	switch (CurrentState)
	{
	case MENU:
		cout << "Hello, Would you like to play?" << endl;
		cin >> res;
		if (res == 'y') {
			CurrentState = PLAY;
		}
		else {
		}
	case PLAY:
		mainGame(CurrentState);
	case GAMEOVER:
		cout << "You did well, would you like to try again?";
		cin >> res;
		if (res == 'y') {
			CurrentState = PLAY;
		}
		else {
			CurrentState = LEAVE;
		}
	case LEAVE:
		cout << "Thanks for Playing!" << endl;
	default:
		break;
	}
}

void mainGame(GameState &CurrentState) {
	if (CurrentState == PLAY) {
		sf::Event event;
		sf::Clock clock;

		snake.foodCount = 1; //Counts from 1 onwards, cause starting at 0 made it say the first food eaten was 0

		snake.setDirection(); //initial set direction func
		snake.grow(); //inital growth of snake

		sf::RenderWindow window(sf::VideoMode(800, 600), "SNAKE GAME {Test}");
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
			warpSnake(snake, window); //should act like a portal and allow the snake to warp around the window

			//clock for the game // still testing that func
			if (clock.getElapsedTime().asMilliseconds() > 60) {
				snake.justAte = false;
			}
			if (clock.getElapsedTime().asMilliseconds() >= 120) {
				run = snake.move(snake.getDirection());
				clock.restart();
			}
			window.clear(sf::Color::Black);

			// SFML Draw elements //
			//Create a grid
			sf::VertexArray rows(sf::Lines, 2);
			sf::VertexArray cols(sf::Lines, 2);

			for (float gy = 0; gy < 600; gy += 25) {
				rows[0].position = sf::Vector2f(800, gy);
				rows[1].position = sf::Vector2f(0, gy);

				window.draw(rows);

				for (float gx = 0; gx < 800; gx += 25) {
					cols[0].position = sf::Vector2f(gx, 600);
					cols[1].position = sf::Vector2f(gx, 0);

					window.draw(cols);
				}
			};

			//draw food
			int x = food.getX(); //coords of the food
			int y = food.getY();

			sf::RectangleShape foodPos(sf::Vector2f(25, 25)); //using rect shape to represent the food
			foodPos.setFillColor(sf::Color::Red); //color of the food
			foodPos.setPosition(x, y); //sets the coord of the food
			window.draw(foodPos); //draws to screen

			//draws the snake
			for (unsigned int i = 1; i < (snake.getCoords().size()); i++) {
				int x = (snake.getCoords()[i].getX());
				int y = (snake.getCoords()[i].getY());
				sf::RectangleShape coord(sf::Vector2f(24, 24));

				if (snake.justAte) {
					coord.setFillColor(sf::Color(rand() % (10, 255), rand() % (10, 255), rand() % (10, 255)));
					snake.justAte = false;
				}
				else {
					coord.setFillColor(sf::Color::Green); //color of snake
				}
				coord.setPosition(x, y); //sets the x and y coords of the snake
				window.draw(coord); //draws the snake
			}
			window.display();
		}
	}
}

//if the snake goes off screen it warps to the other size of the screen (window)
void warpSnake(SNAKE &snake, sf::RenderWindow &window) {
	if (snake.getX() < 0) {
		snake.setX(window.getSize().x);
	}
	if (snake.getY() < 0) {
		snake.setY(window.getSize().y);
	}
	if (snake.getX() > window.getSize().x) {
		snake.setX(0);
	}
	if (snake.getY() > window.getSize().y) {
		snake.setY(0);
	}
}

//increase snake size
int snakeEat(COORD &food, SNAKE &snake) {
	if (snake.foodCollide(food)) {
		snake.grow(); //makes the snake grow after it collides with food
		food = snake.food();
		snake.justAte = true;
		cout << "FOOD COUNT: " << snake.foodCount << endl; //debug
		snake.foodCount += 1;

		return snake.foodCount;
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