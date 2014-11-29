#include "deplacement.h"

Deplacement::Deplacement(int lF, int hF){
    LARGEUR_FENETRE = lF;
    HAUTEUR_FENETRE = hF;
}

// recupere le vecteur pour le sens du deplacement
// si c'est en bas on ferra un deplacement
// avec un vecteurX = 0 et un vecteurY = + 2
void Deplacement::RecupererVecteur(Evenement* in,int* vx,int* vy){
    int vitesse = 0;
    *vx = *vy = 0; 
    if (in->key[SDLK_UP]){
        *vy = -vitesse;
    }
    if (in->key[SDLK_DOWN]){
        *vy = vitesse;
    }
    if (in->key[SDLK_LEFT]){
        *vx = -vitesse;
    }
    if (in->key[SDLK_RIGHT]){
        *vx = vitesse;
    }
}
// on essaye un deplacement, si on vas pas sur un obstacle
bool Deplacement::EssaiDeplacement(Monde* carte,SDL_Rect* perso,int vx,int vy) {
    SDL_Rect test;
    test = *perso;
    test.x+=vx;
    test.y+=vy;
    if ( ! carte->CollisionDecor(&test) ){
        *perso = test;
        cout << "PAS COLI\n";
        return true;
    }else{
        cout << " COLI\n";
    }
    return false;
}
// permet de ce coller au obstacle
void Deplacement::Affine(Monde* carte,SDL_Rect* perso,int vx,int vy) {
    int i;
    for( i=0 ; i< (int) abs(vx) ; i++){
        if (!EssaiDeplacement(carte,perso,signeValeur(vx),0))
            break; // si on a un deplacement horizontale valide on stop
    }
    for( i=0 ; i < (int) abs(vy) ; i++){
        if (!EssaiDeplacement(carte,perso,0,signeValeur(vy)))
            break; // si on a un deplacement verticale valide on stop
    }
}

void Deplacement::Deplace(Monde* carte,SDL_Rect* perso,int vx,int vy,
                          int LARGEUR_TILE,int HAUTEUR_TILE){
    // PAS UTILE CAR LA VITESSE DU JOUEUR NE DEPASSE PAS LA TAILLE DU PERSO

    if (vx>=LARGEUR_TILE || vy>=HAUTEUR_TILE){
        Deplace(carte,perso,vx/2,vy/2,LARGEUR_TILE,HAUTEUR_TILE);
        Deplace(carte,perso,vx-vx/2,vy-vy/2,LARGEUR_TILE,HAUTEUR_TILE);
        return;
    }

    // on test si le deplacement est possible sinon on bouge pas
    if (EssaiDeplacement(carte,perso,vx,vy))
        return;
    Affine(carte,perso,vx,vy);
}

void Deplacement::Evolue(Evenement* in,Monde* carte,SDL_Rect* perso,
                         int LARGEUR_TILE,int HAUTEUR_TILE) {
    int vx,vy;
    RecupererVecteur(in,&vx,&vy);
    Deplace(carte,perso,vx,vy,LARGEUR_TILE,HAUTEUR_TILE);
}

void Deplacement::bougerLaMap(Monde * monde,SDL_Rect * positionPerso,
                              Evenement * event) {
    if (event->key[SDLK_LEFT]){
        monde->setHoriScroll(monde->getHoriScroll()  - 1);
    }
    if (event->key[SDLK_RIGHT])
         monde->setHoriScroll(monde->getHoriScroll() - 1);

    if (event->key[SDLK_UP])
        monde->setVertiScroll(monde->getVertiScroll()- 1 );

    if (event->key[SDLK_DOWN]){
        monde->setVertiScroll(monde->getVertiScroll() - 1);
    }
    // limitation
    if ( monde->getHoriScroll() < 0 )
        monde->setHoriScroll(0);

    if ( monde->getVertiScroll() < 0 )
        monde->setVertiScroll(0);
    // limitation du perso
   if ( positionPerso->x < 0 )
        positionPerso->x = 0;

    if ( positionPerso->y < 0 )
        positionPerso->y = 0;

    // si la fenetre va plus loin que le perso
    if ( monde->getHoriScroll() >  positionPerso->x/2 ) {
        monde->setHoriScroll(positionPerso->x/2);
    }

    if ( monde->getHoriScroll() <  positionPerso->x/2 ) {
        monde->setHoriScroll(positionPerso->x/2);
    }

    if ( monde->getVertiScroll() <  positionPerso->y/2 ) {
        monde->setVertiScroll(positionPerso->y/2);
    }

    if ( monde->getVertiScroll() >  positionPerso->y/2 ) {
        monde->setVertiScroll(positionPerso->y/2);
    }

    //--------------
    if ( monde->getHoriScroll() > monde->getNbrTuilesEnColonneMonde()
         * monde->getLargeurTuile() - LARGEUR_FENETRE - 1 )

        monde->setHoriScroll(monde->getNbrTuilesEnColonneMonde()
                * monde->getLargeurTuile() - LARGEUR_FENETRE-1);

    if ( monde->getVertiScroll() > monde->getNbrTuilesEnLigneMonde()
         * monde->getHauteurTuile() - HAUTEUR_FENETRE - 1 )

        monde->setVertiScroll(monde->getNbrTuilesEnLigneMonde()
                * monde->getHauteurTuile() - HAUTEUR_FENETRE - 1);
}

int Deplacement::signeValeur(int x) {
    if ( x == 0) {
        return 0;
    } else if ( x < 0 ) {
        return -1;
    } else {
        return 1;
    }
}
