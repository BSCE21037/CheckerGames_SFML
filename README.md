# CheckerGame_using_SFML


https://github.com/BSCE21037/CheckerGames_SFML/assets/91457644/d4dc2c85-ba7f-4134-8a69-cbf5ebaa59a6


The SFML Checker Game is a classic two-player board game designed and developed using C++ library, Simple and Fast Multimedia Library (SFML). This engaging and strategic game allows players to challenge each other in a battle of wits as they take turns moving their pieces across the checkerboard.

**Features:**
-2 player game
-Turn based game
-Multiple Killing
-King when reaches end of enemy territory
-Scoring Kills

**To Play:**

The game runs on macOS, Linux and Windows. You need the SFML 2.x library installed, then build with the included `Makefile`.

*macOS*
```
brew install sfml@2
make run
```

*Linux (Debian/Ubuntu)*
```
sudo apt install build-essential libsfml-dev
make run
```

*Windows (MinGW)*
```
mingw32-make run
```
Windows uses the bundled `SFML-2.5.1/` folder; make sure the DLLs in `SFML-2.5.1/bin` are next to the executable or on your `PATH`.

Run the game from the project root — the sprites, sounds and font are loaded via relative paths.

For this project, VsCode was used as the IDE (`.vscode/` contains build/debug tasks for both macOS and Windows).

*Major Bugs of the game were fixed. However, there are some minor bugs present in the game.
