# Projet Tutoré : Développement D'Un Jeu De Type Arcade

## Objectif Pédagogique

Développer dans un contexte professionel un mini-jeu de type Arcade en C/SDL (git, make, documentations).

## Détails

Nous nous intéressrons au jeu *le quize vainc* qui est une variante du morpion connu aussi sous le nom de TIC-TAC-TOE ou OXO.


Le principe du *quize vainc* est simple. 2 joueurs munis de 3 pions (de couleurs differentes) posent tour à tour un pion sur une case vide d'un tableau de 9 cases numérotés de 1 à 9. Le pion prend alors la valeur de la case. Si la somme des 3 pions d'un joueur est égale à 15, ce joueur gagne, il vainc !


Si aucun joueur n'as totalisé 15 quand les 6 pions ont été posés, chaque joueur déplace alors lors de son tour un pion dans une case vide adjacente. La partie s'arrete quand un joueur totalise 15.


Nous développerons successivement les versions suivantes :
* 1 contre 1 sue le même PC
* contre une IA (sur le même PC)
* 1 contre 1 en réseau sur un seveur de mise en relation (attendre qu'un adversaire se connecte)

## How to get, build and run

* git clone [urlToThisRepo]
* cd [thisRepo]
* git submodule init
* git submodule update
* mkdir bin
* cd bin
* cmake ..
* make (mingw32-make for mingw's users)
* ./Pontu

