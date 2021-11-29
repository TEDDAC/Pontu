#include "modele/Joueur.h"

Joueur nouveauJoueur(char      pseudo[PSEUDO_LENMAX],
                     SDL_Color couleur) {
	Joueur joueur;
	strcpy(joueur.pseudo, pseudo);
	joueur.couleur = couleur;
	joueur.classement = 0;
}

