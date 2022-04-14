# MAKiTChess 1.0.0
---
Beware that this was made by an amateur and for fun, so it should be treated like so.

# Usage:
## Compiling
For now, in order to compile the code. You can use the ```build.ps1```, I would personally recommend using the ```-fast```, because it shouldn't be causing any bugs and it is making it significantly better for the AI.

>In order to compile enter the folder ***MAKITCHESS*** *(the file that everything is in)* and only then execute the build.ps1, otherwise the textures won't load.

## Starting
In order to start the program, execute ```start.bat```

# AI

1. Basic:
   - Bruteforcing its way to victory, and not achieving it.
   - Hopes that its opponent will always choose the worst case scenario.
2. Default:
   - Bruteforcing its way to victory.
   - Calculating the realistic game.

# ChangeLog:
### 0.1.0
   - Created the board.
### 0.2.0
   - Added basic pawn movement.
### 0.3.0
   - Added basic rook, bishop and knight movement.
### 0.4.0
   - Added queen and King movement.
### 0.5.0
   - Added Check Checking.
### 0.6.0
   - Added a castle option and some minor debugging options.
### 0.6.1
   - Cleaned up the script, and optimized it.
### 0.7.0
   - Added a basic GUI for the pawn change.
### 0.8.0
   - Added an ending, gameplay element complete.
### 0.9.0
   - Added a functioning GUI.
### 0.9.1
   - Added a GUI for the AI, and added the *Basic AI*.
### 0.9.2
   - Changed the **gameLoop**, so it is no longer dependent on the user input, AI is playing with the same rules
### 0.9.3
   - Added the *Smart AI* option.
### 0.9.4
   - Improved the *Smart AI*, but only on depth 1.
### 1.0.0
   - Finished the script.