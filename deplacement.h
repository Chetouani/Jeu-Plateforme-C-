#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "evenement.h"
#include "monde.h"
#include <cmath>

#define MOVE_SPEED_SCROLL 5

class Deplacement
{


private:
    int LARGEUR_FENETRE;
    int HAUTEUR_FENETRE;

private:
    int signeValeur(int x);

public:
    /*!
     * \brief Deplacement
     * \param lF
     * \param hF
     */
    Deplacement(int lF,int hF);
    /*!
     * \brief RecupererVecteur
     * \param in
     * \param vx
     * \param vy
     */
    void RecupererVecteur(Evenement* in,int* vx,int* vy);
    /*!
     * \brief EssaiDeplacement
     * \param carte
     * \param perso
     * \param vx
     * \param vy
     * \return
     */
    bool EssaiDeplacement(Monde* carte,SDL_Rect* perso,int vx,int vy);
    /*!
     * \brief Affine
     * \param carte
     * \param perso
     * \param vx
     * \param vy
     */
    void Affine(Monde* carte,SDL_Rect* perso,int vx,int vy);
    /*!
     * \brief Deplace
     * \param carte
     * \param perso
     * \param vx
     * \param vy
     * \param LARGEUR_TILE
     * \param HAUTEUR_TILE
     */
    void Deplace(Monde* carte,SDL_Rect* perso,int vx,int vy,int LARGEUR_TILE,int HAUTEUR_TILE);
    /*!
     * \brief Evolue
     * \param in
     * \param carte
     * \param perso
     * \param LARGEUR_TILE
     * \param HAUTEUR_TILE
     */
    void Evolue(Evenement* in,Monde* carte,SDL_Rect* perso,int LARGEUR_TILE,int HAUTEUR_TILE) ;
    /*!
     * \brief Permet de se deplacer dans la map en utilisant les fleches
     * \param monde Le monde dans lequel on veut se déplacé
     * \param event
     */
    void bougerLaMap(Monde * monde, SDL_Rect *positionPerso, Evenement * event);
};

#endif // DEPLACEMENT_H
