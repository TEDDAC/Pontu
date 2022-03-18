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

Utiliser l'option -DCMAKE_BUILD_TYPE=Debug pour build en debug
                  -DCMAKE_BUILD_TYPE=Release pour build en release

```BASH
git clone [urlToThisRepo]
cd [thisRepo]/Pontu
git submodule init
git submodule update
mkdir bin #ou un autre nom de fichier comme "build_debug" ou "build_release"
cd bin
cmake ..
make # ou mingw32-make avec Mingw
cd .. #Se mettre dans le dossier Pontu
./bin/Pontu
```

## Comment jouer
Une fois le jeu lancé :
* Cliquez sur le bouton "Nouvelle partie"
* Choisissez avec les boutons + et - le nombre de joueur
* Saisissez les pseudonymes de chaque joueur et affectez leur une couleur, puis cliquez sur "Jouer"
* Lorsque la partie est lancée, chaque joueur va, à chacun tour, déplacer son joueur avec un glisser-déposer, puis supprimer un pont en cliquant sur celui désiré
* De plus, il est également possible de retourner au menu principal et de couper le son du jeu via les boutons associés
* Une fois la partie terminée, un tableau des scores avec le classement des joueurs est affiché 

