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
#include <stdlib.h>

#include "snake.h"
#include "coord.h"

using namespace std;

enum GameState { MENU, LEAVE, PLAY, GAMEOVER };
enum Direction { UP, DOWN, RIGHT, LEFT, SPACE }; //declares enum
int direction = DOWN;

//functions
int snakeEat(COORD &food, SNAKE &asnake); //snake eats and get score
void snakeReset(bool &run, SNAKE &snake, GameState &CurrentState, sf::RenderWindow &window); //resets snake to inital position and restarts game after colliding
void warpSnake(SNAKE &snake, sf::RenderWindow &window); //should act like a portal and allow the snake to warp around the window
void mainGame(GameState &CurrentState); //plays the game
void menu(GameState &CurrentState); //switchs between states, effectively a finite state machine

//variables
SNAKE snake; //snake class
GameState CurrentState; //Initalizes Game State
COORD food = snake.food(); //coords of the food
bool run = true; //game over condition

//main
int main() {
	CurrentState = MENU; //sets the current state
	srand(time(NULL)); //gets a random seed
	menu(CurrentState);
}

void menu(GameState &CurrentState) {
	char res;
	switch (CurrentState)
	{
	case MENU:
		cout << "Hello, Would you like to play?" << endl;
		cin >> res;
		if (res == 'y') {
			CurrentState = PLAY;
			mainGame(CurrentState);
			break;
		}
		else {
			CurrentState = LEAVE;
			menu(CurrentState);
			break;
		}
	case GAMEOVER:
		cout << "Nice Try!, Would you like to try again?";
		cin >> res;
		if (res == 'y') {
			CurrentState = PLAY;
			mainGame(CurrentState);
			break;
		}
		else {
			CurrentState = LEAVE;
			menu(CurrentState);
			break;
		}
	case LEAVE:
		cout << "Thanks for Playing!" << endl;
		cout << "Have a nice day! <3" << endl;
		break;
	default:
		break;
	}
}

void mainGame(GameState &CurrentState) {
	if (CurrentState == PLAY) {
		sf::Clock clock;

		snake.setDirection(); //initial set direction func
		snake.grow(); //inital growth of snake

		sf::RenderWindow window(sf::VideoMode(800, 600), "SNAKE GAME {Single Player}");
		window.setKeyRepeatEnabled(false); //disables keys being held down
		window.setFramerateLimit(30); //limits the framerate

		window.setVisible(true);

		//sfml window loop
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
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
			snakeReset(run, snake, CurrentState, window);//resets game after collision
			warpSnake(snake, window); //should act like a portal and allow the snake to warp back around if it went off-screen

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

			int color = rand() % (10, 255);

			//draws the snake
			for (unsigned int i = 1; i < (snake.getCoords().size()); i++) {
				int x = (snake.getCoords()[i].getX());
				int y = (snake.getCoords()[i].getY());
				sf::RectangleShape coord(sf::Vector2f(24, 24));

				coord.setFillColor(sf::Color::Green);
				coord.setPosition(x, y); //sets the x and y coords of the snake
				window.draw(coord); //draws the snake
			}

			////gets food count can coverts to displayable string from int
			//int sScore = snake.foodCount;
			//std::ostringstream ostr; //outputs the string stream
			//ostr << sScore; //uses string stream like cout
			//std::string scoreString = ostr.str(); //converts to string

			////display score ingame
			//sf::Font lato;
			//if (!lato.loadFromFile("lato.tff")) {
			//	cout << "Font file could not be found" << endl;
			//}
			//sf::Text score;
			//score.setFont(lato);
			//score.setString("Score: " + scoreString);
			//score.setCharacterSize(25);
			//score.setFillColor(sf::Color::Cyan);
			//score.setOutlineColor(sf::Color::Black);
			//score.setPosition(505, 50);
			//window.draw(score);

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
		if (snake.foodCount == 0) {
			snake.foodCount = 1; //Counts from 1 onwards, cause starting at 0 made it say the first food eaten was 0
		}
		snake.grow(); //makes the snake grow after it collides with food
		food = snake.food();
		snake.justAte = true;
		cout << "FOOD COUNT: " << snake.foodCount << endl; //debug
		snake.foodCount += 1;
		return snake.foodCount;
	}
}

//reset the game
void snakeReset(bool &run, SNAKE &snake, GameState &CurrentState, sf::RenderWindow &window) {
	if (!run) {
		cout << "Game Over!\n" << "Your score was: " << snake.foodCount << endl; //debug
		snake.reset();
		window.close();
		run = true;
		CurrentState = GAMEOVER;
		menu(CurrentState);
	}
}