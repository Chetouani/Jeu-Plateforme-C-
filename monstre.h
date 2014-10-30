#ifndef MONSTRE_H
#define MONSTRE_H
#include <SDL.h>
#include <SDL_image.h>
class Monstre
{
SDL_Surface *left,*right;
SDL_Rect position;
bool versGauche;
public:
    Monstre(const char *fichierL,const char*fichierR
            , SDL_Rect pos, SDL_Surface *parent);
    void deplacement(SDL_Surface *parent);
    SDL_Rect getPosition() const;
    ~Monstre();
};

#endif // MONSTRE_H
