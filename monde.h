#ifndef MONDE_H
#define MONDE_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <string>
#include <fstream>

#include "tuile.h"
#include "exceptiongame.h"

using namespace std;
/*!
 * \brief Représente un Monde
 */
class Monde
{

public:
    /*!
    * \brief Crée un monde sur base d'un fichier texte, respectant
    * une certaine structure.
    * \param nomFichier Le nom du fichier qui contient la configuration
    * du monde
    * \param largeurFenetre Largeur de la fenetre
    * \param hauteurFenetre Hauteur de la fenetre
    */
   Monde(string nomFichier , int largeurFenetre , int hauteurFenetre) throw(ExceptionGame);


   ~Monde();

   /*!
    * \brief Modifie la valeur de la coordonnée Horizontale(x) de
    * scroll ( la position de la fenetre qui bouge dans le monde)
    * \param horiScroll la coordonné horizontale (x) de scroll
    */
   void setHoriScroll(int horiScroll);
   /*!
    * \brief Modifie la valeur de la coordonnée Verticale(y) de
    * scroll ( la position de la fenetre qui bouge dans le monde)
    * \param vertiScroll la coordonné verticale (y) de scroll
    */
   void setVertiScroll(int vertiScroll);
   /*!
    * \brief Permet l'affichage du monde dans une fenetre
    * \param fenetre la fenetre dans laquel on affiche le monde
    */
   void AfficherMonde(SDL_Surface * fenetre);
   /*!
    * \brief Permet de savoir si l'élément (personnage,ennemie,...,tous les éléments
    * qui bougent) est en collison avec
    * un element du monde qu'il ne peut pas traverser
    * \param perso élement du jeu qui bouge (personnage,ennemie,...)
    * \return true si il y'a collision, faux sinon
    */
   bool CollisionDecor(SDL_Rect* perso);
   /*!
    * \brief Donne la position Horizontale (x) de scroll
    * \return la position horizontale (x) de scroll
    */
   int getHoriScroll()const;
   /*!
    * \brief Donne la position Verticale (y) de scroll
    * \return la position verticale (y) de scroll
    */
   int getVertiScroll()const;
   /*!
    * \brief Donne la largeur d'une tuile(un élément du monde)
    * \return la largeur d'une tuile
    */
   int getLargeurTuile() const;
   /*!
    * \brief Donne la hauteur d'une tuile(un élément du monde)
    * \return la hauteur d'une tuile
    */
   int getHauteurTuile() const;
   /*!
    * \brief Donne le nombre de tuile en colonne du monde
    * \return le nombre de tuile en colonne du monde
    */
   int getNbrTuilesEnColonneMonde() const;
   /*!
    * \brief Donne le nombre de tuile en ligne du monde
    * \return le nombre de tuile en ligne du monde
    */
   int getNbrTuilesEnLigneMonde()const;

private:

   int _largeurTuile;       // largeur d'une tuile
   int _hauteurTuile;       // hauteur d'une tuile
   int _nbrTuilesEnColonne; // nbr de tuile en colonne de l'image tuiles.bmp
   int _nbrTuilesEnLigne;   // nbr de tuile en ligne de l'image tuile.bmp
   SDL_Surface * _imagesDesTuiles; // l'image tuiles.bmp
   vector<Tuile> _tuiles;   // liste des tuiles presente dans l'image tuiles.bmp
   // rpz le monde entier et pour chaque case si c'est un mur un ciel ou de l'eau
   vector<vector<Uint16>> _schema;
   int _nbrTuilesEnColonneMonde; // nbr de tuiles en colonne du monde
   int _nbrTuilesEnLigneMonde;   // nbr de tuiles en ligne du monde
   int _horiScroll;     // position horizontale actuel du scroll
   int _vertiScroll;    // position verticale actuel du scroll
   int _largeurFenetre;
   int _hauteurFenetre;


   const string BALISE_FICHIER_IMAGE = "#nomFichierImage";
   const string BALISE_NBR_T_H_FI = "#nbrTuilesColonneFichierImage";
   const string BALISE_NBR_T_V_FI = "#nbrTuilesLigneFichierImage";
   const string BALISE_TYPE_TUILE = "#typeTuile";
   const string BALISE_NIVEAU = "#niveau";
   const string BALISE_TAILLE_MONDE = "#tailleMonde";



private:
   // charge
   // - le nom du fichier images des tuiles
   // - le nombre de tuiles en Hori et Verti de l'image
   // - et les different type de tuiles
   void chargerInfoDepuisFichier(ifstream& fichier) throw (ExceptionGame);
   // renvoie l'image
   SDL_Surface* chargerImage(string nomFichierImage);
   // charge le niveau depuis le fichier
   void chargerNiveauDepuisFichier(ifstream& fichier);
};

#endif // MONDE_H
