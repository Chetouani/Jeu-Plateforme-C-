#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include "monde.h"
#include "evenement.h"
#include "deplacement.h"

//Valeurs attribuées aux états/directions
enum Direction {
  DROITE,GAUCHE
};
enum Etat {
  MARCHE,ARRET,SAUT
};

//Constantes définissant la gravité et la vitesse max de chute
struct Propriete{
    const double GRAVITER = 0.08;
    const int VITESSE_CHUTE = 10;
    const int HAUTEUR_SAUT = 10;
    const int VITESSE_JOUEUR = 5;
    const int VITESSE_SCROLL = 5;
    const int LONGEUR_PERSO = 27;
    const int HAUTEUR_PERSO = 53;
    // Constantes pour l'animation
    const int TIME_BETWEEN_2_FRAMES = 8;
};

class Personnage {

private:
    //Sprite du Héro
    SDL_Surface* _sprite;
    //Coordonnées héro
    int _x, _y, _h, _w;
    //Variables utiles pour animation
    int _frameNumber, _frameTimer;
    int _etat, _direction;
    int _onGround, _timerMort;
    float _dirX, _dirY;
    int _largeurFenetre;
    int _hauteurFenetre;
    Propriete _prop;

public:
    Personnage();
    ~Personnage();
    Personnage(char * name, int x, int y, int largeurFenetre, int hauteurFenetre);
    void drawPlayer(SDL_Surface * screen);
    void drawAnimatedPlayer(SDL_Surface * screen);
    SDL_Rect getPositionHero();
    void gestionDeplacement(Evenement* in, Monde *carte, SDL_Surface *screen);
    void centerScrollingOnPlayer(Monde * m);

private:
    void RecupererVecteur(Evenement* in,int* vx,int* vy);
    bool EssaiDeplacement(Monde* carte,int vx,int vy);

    bool EssaiSaut(Monde* carte,double vx,double vy);
    void Affine(Monde* carte,int vx,int vy);
    void Deplace(Monde* carte,int vx,int vy);
    int signeValeur(int x);
    void bougerLaMap(Monde * monde,SDL_Rect * positionPerso,
                                  Evenement * event);
};

#endif // PERSONNAGE_H
