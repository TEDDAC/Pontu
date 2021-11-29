#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef enum {Absent, Present} EtatPont;

typedef struct {
	SDL_Rect zone;
	EtatPont pontsH[5][4]; // [y][x] pour acceder au coord
	EtatPont pontsV[4][5]; // [y][x] pour acceder au coord
} Plateau;

Plateau CreatePlateau(int x, int y, int w, int h) {
	Plateau p = {.zone={x,y,w,h}};
	for (int x = 0; x < 5; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			p.pontsH[x][y] = Present; // inverser ici car les tableaux sont de dimentions transposées
			p.pontsV[y][x] = Present;
		}
	}
	return p;
}

typedef struct {
	int x;
	int y;
} Ile;

typedef struct {
	Ile ileA;
	Ile ileB;
} Pont;

int minInt(const int a, const int b) {
	return a<b ? a : b;
}

bool supprimerPont(Plateau* plateau, const Pont pont) {
	const int dx = abs(pont.ileA.x - pont.ileB.x);  
	const int dy = abs(pont.ileA.y - pont.ileB.y);

	if (dx == 0 && dy == 1) {
		plateau->pontsV[minInt(pont.ileA.y, pont.ileB.y)][pont.ileA.x] = Absent;
		return true;
	}
	else if(dx == 1 && dy == 0) {
		plateau->pontsH[pont.ileB.y][minInt(pont.ileA.x, pont.ileB.x)] = Absent;
		return true;
	}
	return false;
}





typedef enum {NestRien, EstUnPont, EstUneIle} Questce;

typedef struct {
	union {
		Ile ile;
		Pont pont;
	} value;
	Questce questce;
} PontIleOuRien;

PontIleOuRien getObjetClique(const Plateau p, const SDL_Point coordMouse) {
	// On calcule la taille d'une ile / d'un pont (en x et en y)
	const int ecartX = p.zone.w*2/9;
	const int ecartY = p.zone.h*2/9;

	// On calcule si les coordonnees correspondes à des interval (entre iles) ou non
	bool estUnIntervalX = coordMouse.x%ecartX > p.zone.w/9;
	bool estUnIntervalY = coordMouse.y%ecartY > p.zone.h/9;

	// Si on tombe dans un intervalle en X et en Y on est dans un "trou"
	if (estUnIntervalX && estUnIntervalY) {
		PontIleOuRien retVal = {.questce=NestRien};
		return retVal;
	}
	
	// On calcule les indices de l'ile (ou de l'ile "de départ" du pont)
	int indiceX = coordMouse.x/ecartX;
	int indiceY = coordMouse.y/ecartY;

	// On est pas dans un intervalle ni en X ni en Y donc on est sur l'ile (indiceX; indiceY)
	if (!estUnIntervalX && !estUnIntervalY) {
		PontIleOuRien retVal = {.value.ile = {.x=indiceX, .y=indiceY}, .questce=EstUneIle};
		return retVal;
	}
	// On est dans un intervalle en X mais pas en Y donc on est sur le pont horizontal qui va de l'ile (indiceX; indiceY) à l'ile (indiceX+1; indiceY)
	else if (estUnIntervalX && !estUnIntervalY) { // pont h
		PontIleOuRien retVal = {.value.pont = {.ileA={.x=indiceX, .y=indiceY}, .ileB={.x=indiceX+1, .y=indiceY}}, .questce=EstUnPont};
		return retVal;
	}
	// On est dans un intervalle en Y mais pas en X donc on est sur le pont vertical qui va de l'ile (indiceX; indiceY) à l'ile (indiceX; indiceY+1)
	else { // pont v
		PontIleOuRien retVal = {.value.pont = {.ileA={.x=indiceX, .y=indiceY}, .ileB={.x=indiceX, .y=indiceY+1}}, .questce=EstUnPont};
		return retVal;
	} 
}

void affichePontsPontu(SDL_Renderer* renderer, const Plateau p) {
	SDL_Color marron = {100, 100, 10, 255};
	SDL_SetRenderDrawColor(renderer, marron.r, marron.g, marron.b, marron.a);

	// Un rect que l'on déplace sur chaque emplacement de pont horizontal
	SDL_Rect pontsH = {p.zone.x+p.zone.w/9, p.zone.y+p.zone.h/(4*9), p.zone.w/9, p.zone.h/(2*9)};
	for (int y = 0; y < 5; ++y)
	{
		pontsH.x = p.zone.x+p.zone.w/9;
		for (int x = 0; x < 4; ++x)
		{
			if (p.pontsH[y][x] == Present) {
				SDL_RenderFillRect(renderer, &pontsH);
			}
			pontsH.x += p.zone.w*2/9;
		}
		pontsH.y += p.zone.h*2/9;
	}

	// Un rect que l'on déplace sur chaque emplacement de pont vertical
	SDL_Rect pontsV = {p.zone.x+p.zone.w/(4*9), p.zone.y+p.zone.h/9, p.zone.w/(2*9), p.zone.h/9};
	for (int y = 0; y < 4; ++y)
	{
		pontsV.x = p.zone.x+p.zone.w/(4*9);
		for (int x = 0; x < 5; ++x)
		{
			if (p.pontsV[y][x] == Present) {
				SDL_RenderFillRect(renderer, &pontsV);
			}
			pontsV.x += p.zone.w*2/9;
		}
		pontsV.y += p.zone.h*2/9;
	}
}

void affichePlateauPontu(SDL_Renderer* renderer, const SDL_Rect zone) 
{
	SDL_Color bleu = {10, 10, 200, 255};
	SDL_Color vert = {50, 220, 10, 255};

	SDL_SetRenderDrawColor(renderer, bleu.r, bleu.g, bleu.b, bleu.a);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, vert.r, vert.g, vert.b, vert.a);

	SDL_Rect iles = {zone.x, zone.y, zone.w/9, zone.h/9};
	for (int y = 0; y < 5; ++y)
	{
		iles.x = zone.x;
		for (int x = 0; x < 5; ++x)
		{
			SDL_RenderFillRect(renderer, &iles);
			iles.x += zone.w*2/9;
		}
		iles.y += zone.h*2/9;
	}
}

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Erreur : %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("Coucouc c Martin",10,10,600,600,SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Erreur : %s\n", SDL_GetError());
		goto Quit;   
	}

	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer)
	{
		fprintf(stderr, "Erreur : %s", SDL_GetError());
		goto Quit;
	}

	//const SDL_Texture* texturePont = CreateTexture("img/pont.bmp");

	Plateau plateau = CreatePlateau(5,5,9*60, 9*60); // Les tailles doivent-être des multiples de 9

	SDL_bool quit = SDL_FALSE;
	while(!quit)
	{
		SDL_Event event;

		while(SDL_PollEvent(&event)) 
		{
			switch (event.type) {
				case SDL_QUIT:
					quit = SDL_TRUE;
					break;
				case SDL_MOUSEBUTTONDOWN: {
					SDL_Point coordMouse = {.x = event.button.x, .y=event.button.y};
					if (SDL_PointInRect(&coordMouse,&(plateau.zone))) {
						PontIleOuRien objetClique = getObjetClique(plateau, coordMouse);
						switch (objetClique.questce) {
							case EstUnPont:
								printf("Pont de {%d; %d} à {%d; %d}\n", objetClique.value.pont.ileA.x, objetClique.value.pont.ileA.y, objetClique.value.pont.ileB.x, objetClique.value.pont.ileB.y);
								supprimerPont(&plateau,objetClique.value.pont);
								break;
							case EstUneIle:
								printf("Ile {%d; %d}\n", objetClique.value.ile.x, objetClique.value.ile.y);
								break;
							default:
								printf("Rien\n");
								break;
						}
					}
					break;
				}
			}
		}
		
		// Affichage
		affichePlateauPontu(renderer, plateau.zone);
		affichePontsPontu(renderer, plateau);

		SDL_RenderPresent(renderer);
		SDL_Delay(20);
	}

	statut = EXIT_SUCCESS;
Quit:
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return statut;
}