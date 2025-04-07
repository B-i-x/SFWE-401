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

## CMake

I also made a CMakefile if you know how to run those


## Fuzzing

Make sure you are cd'd into build dir

### Windows

This command worked for me in powershell

```powershell
type ..\test_fuzzing_input\test_input.txt | .\game.exe
```

### Mac

This command might work

```terminal
.\game.exe < ..\test_fuzzing_input\test_input.txt
```