# Projet Tutoré : Développement d'un jeu de type Arcade

## Objectif Pédagogique

Développer dans un contexte professionel un mini-jeu de type Arcade en C/SDL (git, make, documentations).

## Le jeu
Nous implémentons le jeu *Pontu*, un jeu de plateau de 2 à 4 joueurs.
### Les rêgles principales
Le plateau est une grille d'iles 5 par 5 reliées par des ponts sur laquelle les joueurs disposent de 3 pions (2 à 4 joueurs). L'objectif est d'isoler les pions adverses avant de voir les siens isolés. Pour cela, le tour d'un joueur est composé de 2 actions : déplacer un de ses pions (en passant par un pont) puis retirer un pont du jeu.
### Précisions
* Un pion est isolé si aucun pont ne part de l'île sur laquelle il est.
* Un joueur est éliminé losque tous ses pions sont isolés.
* Si un joueur ne peut plus déplacer de pion sans pour autant être éliminé, il retire uniquement un pont. 

## Versions du projet

Nous développerons successivement les versions suivantes :
* Jouer sur un même ordinateur à plusieurs
* Jouer contre des IAs (eventuellement mixées avec des joueurs)
* Jouer en réseau sur un seveur de mise en relation (attendre qu'un adversaire se connecte)

## Comment télécharger, compiler et executer Pontu

### Sur Linux:

```BASH
git clone [urlToThisRepo]
cd [thisRepo]
git submodule init
git submodule update
mkdir bin
cd bin
cmake ..
make
cd .. #Se mettre dans le dossier Pontu
./bin/Pontu
```

### Sur Windows:

```BASH
git clone [urlToThisRepo]
cd [thisRepo]
git submodule init
git submodule update
mkdir bin
cd bin
cmake ..
mingw32-make
cd .. #Se mettre dans le dossier Pontu
./bin/Pontu.exe
```

