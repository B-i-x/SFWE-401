# SFWE 401 

## Building the game
To build game, open up a new terminal and run the command below

```bash
cd build
gcc -o game ..\old_175_code\main.c
```

## Running the game

While in the build dir as your active directory and game.exe in that directory

1. First change the code in the terminal to show the correct symbols for the cards
2. Run the game!

The command below does this

```bash
chcp 65001
.\game.exe
```