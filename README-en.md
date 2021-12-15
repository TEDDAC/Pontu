# Mentored project: developing a arcade-like game

[Français](https://gitlab.iut-clermont.uca.fr/maribemont/projet-tut/-/blob/master/README.md)

## Educational aim

Program a arcade-like minigame in a professional context, using C/SDL (git, make, docs)

## The game
We will develop the game *Pontu*, a board game for 2 to 4 playerrs.
### Main rules
The board consists in a 5 × 5 grid of islands, connected between each other by bridges. Each player starts with 3 pieces (or 2 if there are 4 players).
A player starts their turn by moving one of their pieces to another island, through a bridge, then remove a bridge to try to isolate another player's piece.
They win if all of their opponents' pieces are isolated.
### More details
* A piece is isolated if there is no bridge going to its island.
* A player is out if all of their pieces are isolated.
* If a player cannot move their pieces but they still have non-isolated ones, they only remove a bridge.
This typically happpens when 2 pieces are on adjacent islands, and they have only one bridge (the one coonnected them).
Neither pieces cannot move because the only reachable island is busy, but they aren't isolated because their respective islands have a bridge.

## Versions

We will develop these versions in this order:
* Game on the same computer, with several players
* Game against AIs (and maybe other players)
* Online game on matchmaking server (wait for a player to log in)

## How to get, build and run

### On Linux:

```BASH
git clone https://gitlab.iut-clermont.uca.fr/maribemont/projet-tut.git
cd [thisRepo]/Pontu
git submodule init
git submodule update
mkdir bin
cd bin
cmake ..
make
./Pontu
```

### On Windows:

```BASH
git clone https://gitlab.iut-clermont.uca.fr/maribemont/projet-tut.git
cd [thisRepo]/Pontu
git submodule init
git submodule update
mkdir bin
cd bin
cmake ..
mingw32-make
./Pontu
```


