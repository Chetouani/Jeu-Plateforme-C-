#include "gestionjeu.h"
#include "SDL.h"

using namespace std;

SDL_Surface *GestionJeu::getSurfaceEcran() const
{
    return surfaceEcran;
}

void GestionJeu::setSurfaceEcran(SDL_Surface *value)
{
    surfaceEcran = value;
}

QList<SDL_Surface *> GestionJeu::getListeSurfaces() const
{
    return listeSurfaces;
}

void GestionJeu::setListeSurfaces(const QList<SDL_Surface *> &value)
{
    listeSurfaces = value;
}

SDL_Surface *GestionJeu::getDerniereSurfaceCree()
{
    return listeSurfaces.back();
}
GestionJeu::GestionJeu()
{
    this->nomJeu = "";
}

GestionJeu::GestionJeu(const char *nomApp)
{
    this->nomJeu = QString(nomApp);
}

GestionJeu::GestionJeu(QString nomApp)
{
    this->nomJeu = nomApp;
}

GestionJeu::GestionJeu(string nomApp)
{
    this->nomJeu = QString::fromStdString(nomApp);
}

void GestionJeu::actualiserFenetre()
{
    SDL_Flip(this->surfaceEcran); /* Mise à jour de l'écran */
}

void GestionJeu::pauseFenetre()
{
    SDL_Event event;     //Mettre le programme "en pause"
    SDL_WaitEvent(&event);
    while (event.type != SDL_QUIT)
        SDL_WaitEvent(&event);
}

void GestionJeu::initialiserJeu()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        throw ExceptionGame(SDL_GetError());
    }
}

void GestionJeu::setNomJeu(const char *nom)
{
    this->nomJeu = QString(nom);
}

void GestionJeu::fermerJeu()
{
    SDL_Quit();
}


void GestionJeu::creerFenetre(int largeur, int hauteur,
                              int bitsParPixels, Uint32 options)
{
    /* La première chose à faire après SDL_Init(),
     * c'est indiquer le mode vidéo que vous voulez utiliser,
     * c'est-à-dire la résolution, le nombre de couleurs et
     * quelques autres options.
     * On va utiliser pour cela la fonction SDL_SetVideoMode()
     * qui prend quatre paramètres :
     * 1) la largeur de la fenêtre désirée (en pixels) ;
     * 2) la hauteur de la fenêtre désirée (en pixels) ;
     * 3) le nombre de couleurs affichables (en bits / pixel) ;
     * 4) des options (des flags).
     *
     *  Les options : comme pour SDL_Init on doit utiliser des flags
     *  pour définir des options. Voici les principaux flags que vous
     *  pouvez utiliser (et combiner avec le symbole |).
     *
     *  SDL_HWSURFACE : les données seront chargées dans la mémoire vidéo,
     *  c'est-à-dire dans la mémoire de votre carte 3D.
     *  Avantage : cette mémoire est plus rapide.
     *  Défaut : il y a en général moins d'espace dans
     *  cette mémoire que dans l'autre (SDL_SWSURFACE).
     *
     *  SDL_SWSURFACE : les données seront chargées dans la mémoire système
     *  (c'est-à-dire la RAM, a priori).
     *  Avantage : il y a beaucoup d'espace dans cette mémoire.
     *  Défaut : c'est moins rapide et moins optimisé.
     *
     *  SDL_RESIZABLE : la fenêtre sera redimensionnable.
     *  Par défaut elle ne l'est pas.
     *
     *  SDL_NOFRAME : la fenêtre n'aura pas de barre de titre ni de bordure.
     *
     *  SDL_FULLSCREEN : mode plein écran. Dans ce mode,
     *  aucune fenêtre n'est ouverte. Votre programme prendra toute
     *  la place à l'écran, en changeant automatiquement la résolution
     *  de celui-ci au besoin.
     *
     *  SDL_DOUBLEBUF : mode double buffering. C'est une technique
     *  très utilisée dans les jeux 2D, et qui permet de faire en
     *  sorte que les déplacements des objets à l'écran soient fluides,
     *  sinon ça scintille et c'est assez laid.
     */
    surfaceEcran = SDL_SetVideoMode(largeur, hauteur,
                                    bitsParPixels, options);
    if (surfaceEcran == NULL) //La création de la fenêtre a échoué
        throw ExceptionGame(SDL_GetError());
    //nom de l'app
    SDL_WM_SetCaption(this->nomJeu.toStdString().c_str(), NULL);
}



SDL_Surface * GestionJeu::creerSurface(Uint16 largeur, Uint16 hauteur,
                                        Sint16 x, Sint16 y, SDL_Surface *parent)
{
    if (parent == NULL)
        parent = FENETRE_PRINCIPALE;
    SDL_Rect pos = {x, y, largeur, hauteur};

    listeSurfaces.append(SDL_CreateRGBSurface(SDL_HWSURFACE,
                                              largeur,hauteur, 32, 0, 0, 0, 0));

    SDL_BlitSurface(listeSurfaces.back(), NULL, parent, &pos);
    actualiserFenetre();
    return listeSurfaces.back();
}

SDL_Surface *GestionJeu::ajouterImage(const char *pathImage, Uint16 largeur,
                                      Uint16 hauteur, Sint16 x, Sint16 y,
                                      SDL_Surface *parent)
{
    if (parent == NULL)
        parent = FENETRE_PRINCIPALE;
    SDL_Rect pos = {x, y, largeur, hauteur};

    listeSurfaces.append(IMG_Load(pathImage));
    SDL_BlitSurface(listeSurfaces.back(), NULL, parent, &pos);
    actualiserFenetre();
    return listeSurfaces.back();
}

void GestionJeu::libererSurfaces()
{
    for(int i = listeSurfaces.size(); i > 0; i--)
    {
        SDL_FreeSurface(listeSurfaces.back());
        listeSurfaces.pop_back();
    }
}

void GestionJeu::colorierSurface(SDL_Surface *surface,
                                 SDL_Rect *zone,
                                 Uint8 rouge, Uint8 vert, Uint8 bleu)
{
    Uint32 couleurSurface = SDL_MapRGB(surface->format, rouge, vert, bleu);
    SDL_FillRect(surface, zone, couleurSurface);
}

void GestionJeu::placerSurface(SDL_Surface *surface, SDL_Surface *parent,
                               Uint16 largeur, Uint16 hauteur,
                               Sint16 x, Sint16 y)
{
    SDL_Rect pos = {x, y, largeur, hauteur};
    SDL_BlitSurface(surface, NULL, parent, &pos);
    actualiserFenetre();
}
