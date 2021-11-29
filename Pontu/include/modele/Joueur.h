/**
 * \file Joueur.h
 * \brief Représente un joueur
 * \author Théotime Maillarbaux
 * \date 29/11/2021
 */

#ifndef JOUEUR_H
#define JOUEUR_H

#define PSEUDO_LENMAX 50

#include <SDL2/SDL_pixels.h>

/**
 * \struct Joueur
 * \brief Joueur d'une partie
 */
typedef struct {
	char pseudo[PSEUDO_LENMAX]; //< Le pseudo du joueur
	SDL_Color couleur; //< La couleur des pions du joueur
	int classement; //< La position du joueur dans le classement (vaut 0 s'il n'est pas encore éliminé)
} Joueur;

/**
 * \brief Crée un nouveau joueur
 * \param[in]	pseudo	Le pseudo du nouveau joueur
 * \param[in]	couleur La couleur du nouveau joueur
 * \return Une structure représentant le nouveau joueur
 */
Joueur nouveauJoueur(char pseudo[PSEUDO_LENMAX], SDL_Color couleur);


#endif // JOUEUR_H
