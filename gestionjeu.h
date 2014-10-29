#ifndef GESTIONJEU_H
#define GESTIONJEU_H
#define FENETRE_PRINCIPALE getSurfaceEcran()
#define TOUCHE event.key.keysym.sym
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <QString>
#include <QList>
#include "exceptiongame.h"

class GestionJeu
{
private:
    QString nomJeu;
    SDL_Surface *surfaceEcran = NULL;
    QList<SDL_Surface *> listeSurfaces;

public:
    /**
     * @brief GestionJeu
     */
    GestionJeu();

    /**
     * @brief GestionJeu
     * @param nomJeu
     */
    GestionJeu(const char *nomJeu);

    /**
     * @brief GestionJeu
     * @param nomJeu
     */
    GestionJeu(QString nomJeu);

    /**
     * @brief GestionJeu
     * @param nomJeu
     */
    GestionJeu(std::string nomJeu);

    /**
     * @brief actualiserFenetre
     */
    void actualiserFenetre();

    /**
     * @brief Met la fenêtre en pause jusqu'à ce que l'utilisateur
     * ferme la fenetre
     */
    void pauseFenetre();

    /**
     * @brief Permet de lancer le coeur du jeu (Boucle infinie)
     * @param adresseFonctionAExecuter Fonction qu'exécutera le jeu
     * <strong>Attention : Si le code de retour de la fonction est
     * différent de zéro, la fonction s'arrête</strong>
     * Le coeur continue donc TANT QUE la fonction retourne 0
     *
     * C'est au programmeur donc, de retourner une valeur autre que 0 en cas de
     * fin
     */
    void coeurJeu(int (*adresseFonctionAExecuter)());
    /**
     * @brief initialiserJeu
     */
    void initialiserJeu();

    /**
     * @brief setNomJeu
     * @param nom
     */
    void setNomJeu(const char *nom);

    /**
     * @brief fermerJeu
     */
    void fermerJeu();

    /**
     * @brief Permet de créer une nouvelle fenêtre SDL
     * @param largeur Largeur de la fenêtre
     * @param hauteur Hauteur de la fenêtre
     * @param bitsParPixels Bits par pixels (Mettez 32 si vous ne savez pas.)
     * @param options Flags pour la fenêtre.
     * (Voir "SDL_Surface Flags" pour l'ensemble des options possibles combinables
     * avec un '|' (de la ligne 124 à la ligne 145)
     */
    void creerFenetre(int largeur, int hauteur,
                      int bitsParPixels, Uint32 options);

    /**
     * @brief Permet d'ajouter une surface à une autre
     * @param largeur Largeur de la fenêtre
     * @param hauteur Hauteur de la fenêtre
     * @param x Position x dans la surface parent
     * @param y Position y dans la surface parent
     * @param parent Surface où doit être placée celle-ci.
     * (NULL = fenêtre principale)
     */
    SDL_Surface *creerSurface(Uint16 largeur, Uint16 hauteur,
                        Sint16 x, Sint16 y, SDL_Surface * parent = NULL );

    /**
     * @brief Permet d'ajouter une image sur une surface
     * @param pathImage Chemin vers l'image à ajouter
     * @param largeur Largeur de l'image
     * @param hauteur Hauteur de l'image
     * @param x Position x dans la surface parent
     * @param y Position y dans la surface parent
     * @param parent Surface où doit être placée l'image.
     * (NULL = fenêtre principale)
     * @return
     */
    SDL_Surface *ajouterImage(const char *pathImage, Uint16 largeur, Uint16 hauteur,
                              Sint16 x, Sint16 y, SDL_Surface * parent = NULL);
    /**
     * @brief Permet de libérer toute la mémoire allouée par les surfaces
     */
    void libererSurfaces();
    /**
     * @brief Permet de colorier une zone d'une surface (SANS METTRE A JOUR LA
     * FENETRE !!!)
     * @param surface La surface à colorier
     * @param zone La zone à colorier (NULL = toute la surface)
     * @param rouge Niveau de rouge
     * @param vert Niveau de vert
     * @param bleu Niveau de bleu
     */
    void colorierSurface(SDL_Surface *surface,
                         SDL_Rect *zone = NULL,
                         Uint8 rouge = 0, Uint8 vert = 0, Uint8 bleu = 0);

    /**
     * @brief Permet de placer une surface sur une autre.
     * @param surface La surface qu'il faut placer
     * @param parent  La surface sur laquelle placer la surface désirée
     * @param largeur Largeur de la surface
     * @param hauteur Hauteur de la surface
     * @param x Là où sera placée la surface en X
     * @param y Là où sera placée la surface en Y
     */
    void placerSurface(SDL_Surface * surface, SDL_Surface * parent,
                       Uint16 largeur,Uint16 hauteur, Sint16 x, Sint16 y);

    /**
     * @brief getSurfaceEcran
     * @return
     */
    SDL_Surface *getSurfaceEcran() const;

    /**
     * @brief setSurfaceEcran
     * @param value
     */
    void setSurfaceEcran(SDL_Surface *value);

    /**
     * @brief getListeSurfaces
     * @return
     */
    QList<SDL_Surface *> getListeSurfaces() const;

    /**
     * @brief setListeSurfaces
     * @param value
     */
    void setListeSurfaces(const QList<SDL_Surface *> &value);

    SDL_Surface *getDerniereSurfaceCree();
};

#endif // GESTIONJEU_H
