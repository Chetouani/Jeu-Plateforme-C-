#ifndef GESTIONJEU_H
#define GESTIONJEU_H
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <QString>
#include <QList>
class GestionJeu
{
private:
    QString nomJeu;
    SDL_Surface *surfaceEcran = NULL;
    QList<SDL_Surface *> listeSurfaces;
public:

    GestionJeu();
    GestionJeu(const char *nomJeu);
    GestionJeu(QString nomJeu);
    GestionJeu(std::string nomJeu);
    void actualiserFenetre();
    void pauseFenetre();
    void initialiserJeu();
    void setNomJeu(const char *nom);
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
    SDL_Surface *ajouterSurface(int largeur, int hauteur,
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
     * @brief Permet de colorier une zone d'une surface
     * @param surface La surface à colorier
     * @param zone La zone à colorier (NULL = toute la surface)
     * @param rouge Niveau de rouge
     * @param vert Niveau de vert
     * @param bleu Niveau de bleu
     */
    void colorierSurface(SDL_Surface *surface,
                         SDL_Rect *zone = NULL,
                         int rouge = 0, int vert = 0, int bleu = 0);

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
};

#endif // GESTIONJEU_H
