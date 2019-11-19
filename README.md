# Snake Game
Assignment 1 for Game Programming. 

The aim of the project is to recreate the classic snake game using C++ and SFML, with the ability to add another player.
The Snake is controlled using WSAD (or Directional Keys). Collect Apple (Red Squares) to grow your snake. Eating yourself ends the game.

## Usage
- Open Project with Visual Studio 2017. 
- SFML 2.4.2 is added via NuGet Package Manager, so you don't need to install it to your system and Link it to the project. 
- To restore NuGet Packages, goto 'Manage NuGet Packages' in the 'Project' Menu.
- Then either Build the Release or Debug in x86 Version of the Project, or Run using the local debugger. 
  > If you decide to build the and run the .exe file from the Release/Debug folder, copy the sfml dll and font file from the SnakeGame    folder to the Release/Debug folder.

> The game was tested only using Visual Studio for Windows but the code should also works on other systems supported by SFML.

## Technologies
- Made using C++ and [SFML](https://www.sfml-dev.org/). 
- Made in [Visual Studio 2017](https://www.visualstudio.com/).

## Additional Information
> Always in Multiplayer mode due to no option to change mode. 
- Single: Working.
- Multiplayer: Kinda Working.
  - Player 1
    - Colour: Green
    - Control: Directional (Arrow Keys)
    - Cannot eat Blue Snake due to no collision code.
  - Player 2
    - Colour: Blue
    - Control: WSAD
    - Cannot eat Green Snake due to no collision code.

- Score
  - Tracks per snake but is it incomplete when displaying final score, that is done in CLI.
- End Condition
  - When all snakes die. 
- GUI 
  - No real 'GUI', everything is done via CLI.
- Known Bugs
  - When warping from one side to window to the other inputting any direction prior to snake appearing cause it to reamin offscreen.
  - Both Snakes have the exact same starting position.

## Preview 
![preview.gif]

## Author
Shivneel Achari

## LICENSE
MIT LICENSE
