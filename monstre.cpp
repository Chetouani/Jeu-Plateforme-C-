#include "monstre.h"

Monstre::Monstre(const char *fichierL,const char*fichierR
                 , SDL_Rect pos, SDL_Surface *parent)
{
    left = IMG_Load(fichierL);
    right = IMG_Load(fichierR);
    position = pos;
    versGauche =true;
}

void Monstre::deplacement(SDL_Surface *parent)
{
   if(versGauche && position.x >1){ // + ajouter verifier case gauche vide
       position.x-=1;
       if(position.x<2)
           versGauche= false;
   } else if(position.x <parent->w-1){ // + ajouter verifier case droite vide
       position.x+=1;
       if(position.x>parent->w-2)
           versGauche=true;
   }
   if (versGauche)
       SDL_BlitSurface(left,NULL,parent,&position);
   else
       SDL_BlitSurface(right,NULL,parent,&position);
}

SDL_Rect Monstre::getPosition() const
{
    return position;
}

Monstre::~Monstre()
{
    SDL_FreeSurface(left);
    SDL_FreeSurface(right);
}
