## Stealth Game
A simple, console-based stealth game written in C. Navigate through a maze, avoid police, and collect gold to increase your score. This game demonstrates basic programming concepts such as structures, control flow, and simple AI for enemy movement.

## Features
Navigate through a dynamically generated maze.
Avoid police patrols while collecting gold.
Simple console-based UI with character representations for the player, police, gold, and walls.
Cross-platform compatibility with conditional compilation for clear screen commands.

## Prerequisites
To compile and run this game, you need:

*A C compiler (GCC recommended for Linux/MacOS, MinGW for Windows)
*Basic command-line utilities

## Installation
1. Clone the repository:
git clone https://github.com/yourusername/stealth-game.git          
cd stealth-game

3. Compile the game:
   For Linux and MacOS:
gcc -o stealth_game main.c
   For Windows:
gcc -o stealth_game.exe main.c

5. Run the game:
   Linux and MacOS:
./stealth_game
   Windows:
stealth_game.exe

## How to Play
Use w, a, s, d to move up, left, down, and right, respectively.
Collect gold ($) to increase your score.
Avoid police (M); getting caught will end the game.
Hitting walls (#) will also end the game.
The game board clears and refreshes after each move for a continuous experience.

## Game Components
Player (P): You, trying to collect gold.
Police (M): Moves randomly. Getting caught or adjacent results in game over.
Gold ($): Increases your score by 1 for each piece collected.
Walls (#): Fixed obstacles that end the game on contact.

## Development
This game is developed in C and is a good starting point for beginners looking to understand game development basics, collision detection, and simple AI for enemy movement.

## Contributing
Contributions are welcome. Please feel free to fork the repository, make improvements, and submit pull requests.

## License
This project is open-sourced under the MIT License. See the LICENSE file for more details.   
