# WAsteroids
A port of my
[DSteroids](https://github.com/DoodlingTurtle/NDS_DSteroids)
project for the Nintendo DS.
The game is based on the 
[OneLoneCoder PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine)
.

The target platform is WebAssembly. So this will run on every platform that has 
a half decent modern Web Browser.


## The Plan
The goal is to create a roughlite Asteroids game, that allows the player to 
purchase "upgrades" in-between levels.
Said upgrades are paid for with the points that the player earns during the main game.

The available upgrades per level are partially randomized.
So each game will turn out slightly different.

The main objective of the game is, to reach the highest score possible, 
in the shortest amount of time.

## Controling the Game
Right now the control scheme is limited to the original Nintendo DS project.
That means Keyboard inputs only.

ASDF = Left / Down / Right / Up\
P = A (confirm)\
L = B (back)\
O = X\
K = Y

F = L (Left shoulder)\
J = R (Right shoulder)

RETURN/ENTER = Start (confirm)\
BACK/BACKSPACE = Select


## How to build
If you want to download the source code, make changes or whatever, then be my guest.

However, please keep in mind, that everything within the olc - namespace 
is bound to its own OLC-3 License and can or should therefore not be changed.

If you build something cool from my source code, and you have a Twitter account, 
then fell free to show it to me at [@TurtleDoodling](https://twitter.com/turtledoodling).
I may even retweet it.

With that out of the way, here is how you setup the build environment for the project.

1. Download and install Emscripten. A guide for that can be found [here](https://emscripten.org/docs/getting_started/downloads.html).
2. Install 'make'. (not cmake, just the plain old make)
3. Clone this repository.
4. Navigate into the cloned project folder.
5. Run ` make emsetup `.

   This will force Emscripten to download and cache everything else, that is needed to 
   build this project. Executing the command can take a while.

   Once it is finished, you will get a bunch of warnings about missing symbols. 

   Since the goal of the command is, to force Emscripten to download 
   and cache its libraries, you can ignore these warnings. They are just a
   necessary evil.

6. After that, you can use ` make ` to build the project into a main.html file.
7. You can use ` make run ` to start a preview server and open the project in your default browser.
   
   You will have to manually stop the server by pressing "Ctrl + C" in your terminal

8. Or you can use ` make debug ` to do the same as ` make run `, but the shown site has a Javascript console attached.
  
   
9. If you are ready to release, you can use ` make release ` to rebuild the 
   project in a more optimized way and copy everything to the 'release' folder.



## Current TODOs     
Right now this port is pretty much a work in progess.

There is a lot to be done, before it reaches a playable state.


- Bring over the other Gamestates
  - Credits/License screen
  - Pause screen
  - GameOver screen
  - Main Game screen
    - requires other Game components
      - Ship
      - Score counter
      - available upgrades
        - Shields
        - Reactors components

- Add support for different window formats and resolutions
- Add Touch controls
- Store highscores and Settings via LocalStorage in the Browser
- Add sound effects

