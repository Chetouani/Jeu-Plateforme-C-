#include <QApplication>
#include <mainwindow.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "monde.h"
#include "evenement.h"
#include "deplacement.h"
#include "gestionjeu.h"
#include "Personnage.h"
#define UTILISER_LA_VRAM SDL_HWSURFACE
#undef main
const int LARGEUR_FENETRE = 1000;
const int HAUTEUR_FENETRE = 700;

using namespace std;


void AfficherPerso(SDL_Rect* posi,SDL_Surface* perso,SDL_Surface* screen,
                   int xscroll,int yscroll)
{
    SDL_Rect positionsurecran = *posi;
    positionsurecran.x -= xscroll;
    positionsurecran.y -= yscroll;
    SDL_BlitSurface(perso,NULL,screen,&positionsurecran);
}

int main(int argc, char **argv) {
//--------------------------------- MOURAD -----------------------------------//
/*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();
    if (w.quit) //Si l'user a cliqué sur "Quitter"
        return 1;
*/
//------------------------------- FIN MOURAD ---------------------------------//

//---------------------------------- ABDEL -----------------------------------//

    // initialise SDL
    if ( SDL_Init(SDL_INIT_VIDEO) == -1) {
        cerr << "Erreur d'initialisation de SDL" << endl;
        exit(EXIT_FAILURE);
    }
    // notre fenetre ,param (taille,taille,couleur,option)
    SDL_Surface * fenetre = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,
                                             32,SDL_HWSURFACE);

    // renomer la fenetre
    SDL_WM_SetCaption("Jeu de plateforme", NULL);

    // demander une couleur en UINT32
    // SDL_MAPRGB(format de couleur de la surface,R,V,B)
    // Uint32 couleurFond = SDL_MapRGB(fenetre->format,164,0,0); //bleu ciel
    // remplir une surface d'une couleur
    // param -> la Surface a remplir, la partie de la surface, la couleur UINT32
    //SDL_FillRect(fenetre,NULL,couleurFond);

    // notre personnage
    Personnage * hero = new Personnage("img/walkright.png", 0, 0,LARGEUR_FENETRE,HAUTEUR_FENETRE);
    Monde * m;
    try{
         m = new Monde("MaMapTest.txt",LARGEUR_FENETRE,HAUTEUR_FENETRE);
         Evenement * evt = new Evenement();

         while(!evt->key[SDLK_ESCAPE] && !evt->quit){


             evt->ActiveAttenteEvenement();
             SDL_Rect  positionPerso ;
             positionPerso = hero->getPositionHero();
             m->AfficherMonde(fenetre,&positionPerso);
             hero->gestionDeplacement(evt,m,fenetre);
             hero->drawAnimatedPlayer(fenetre);

             //Affiche l'écran
             SDL_Flip(fenetre);
             //Delai
             SDL_Delay(5);
         }
    }catch(ExceptionGame eg){
        cerr << eg.what() << endl;
        SDL_FreeSurface(fenetre);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // libere la memoire
    SDL_FreeSurface(fenetre);
    SDL_Quit();
    exit(EXIT_SUCCESS);

//------------------------------- FIN ABDEL ----------------------------------//
}
