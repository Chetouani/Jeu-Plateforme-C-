#include "Personnage.h"

Personnage::Personnage(){
    _sprite = nullptr;
    //On charge les coordonnées du hero
    _x = 0;
    _y = 0;
    _w = _prop.LONGEUR_PERSO;
    _h = _prop.HAUTEUR_PERSO;
    //On initialise les variables pour l'animation
    _frameNumber = 0;
    _frameTimer = 0;
}

Personnage::Personnage(char * name, int x, int y,int largeurFenetre,int hauteurFenetre){
    //On charge le sprite
    _sprite = IMG_Load(name);
    //On charge les coordonnées du hero
    _x = x;
    _y = y;
    _w = _prop.LONGEUR_PERSO;
    _h = _prop.HAUTEUR_PERSO;

    //On indique l'état et la direction du héro
    _direction = DROITE;
    _etat = ARRET;

    //On initialise les variables pour l'animation
    _frameNumber = 0;
    _frameTimer = _prop.TIME_BETWEEN_2_FRAMES;

    //Variables nécessaires au fonctionnement de la gestion des collisions
    _timerMort = 0;
    _onGround = 1;

    _largeurFenetre = largeurFenetre;
    _hauteurFenetre = hauteurFenetre;
}

Personnage::~Personnage(){
    SDL_FreeSurface(_sprite);
}

void Personnage::drawPlayer(SDL_Surface * screen){
    // Rectangle de destination à blitter
    SDL_Rect dest;

    dest.x = _x;
    dest.y = _y;
    dest.w = _prop.LONGEUR_PERSO;
    dest.h = _prop.HAUTEUR_PERSO;
    // Rectangle source à blitter
    SDL_Rect src;

    //On choisit la bonne frame à blitter
    src.x = _frameNumber * _prop.LONGEUR_PERSO;
    src.y = 0;
    src.w = _prop.LONGEUR_PERSO;
    src.h = _prop.HAUTEUR_PERSO;

    // Blitte notre héros sur l'écran aux coordonnées x et y
    SDL_BlitSurface(_sprite, &src, screen, &dest);
}

void Personnage::drawAnimatedPlayer(SDL_Surface * screen){
    //On utilise un timer pour animer le héro
    if (_etat == MARCHE) {
        if (_frameTimer <= 0) {
            //Lorsqu'il arrive à zéro, on le réinitialise
            _frameTimer = _prop.TIME_BETWEEN_2_FRAMES;

            //Et on incrémente notre variable pour passer à la frame suivante
            _frameNumber++;

            //Si on dépasse la frame max, il faut revenir à la première
            //Pour connaître la frame max, il suffit de diviser la longueur du spritesheet
            //par la longueur de notre héros : 480 / 40 = 12 frames
            //Puisque la première frame est la numéro 0, la dernière est donc la numéro 11

            if(_frameNumber >= _sprite->w / _prop.LONGEUR_PERSO)
                _frameNumber = 0;
            //Sinon, on décrémente notre timer
        } else {
            _frameTimer--;
        }
    }else{
        _frameNumber = 0;
    }
    //Ensuite, on peut passer la main à notre fonction
    this->drawPlayer(screen);
}

SDL_Rect Personnage::getPositionHero(){
    SDL_Rect positionPerso;
    positionPerso.h = _prop.HAUTEUR_PERSO;
    positionPerso.w = _prop.LONGEUR_PERSO;
    positionPerso.x = _x;
    positionPerso.y = _y;
    return positionPerso;
}

void Personnage::gestionDeplacement(Evenement* in,Monde * carte,SDL_Surface * screen){
    int vx,vy;
    RecupererVecteur(in,&vx,&vy);
    if (_etat == SAUT) {
        // Les variables de la troisieme methode
        double v_x = 2;
        if (_direction == GAUCHE)
            v_x = -2;
        double v_grav = 0.9;
        double v_y = -18;
        while(v_y < 19) {
            this->EssaiSaut(carte,v_x,v_y);
            SDL_Rect  positionPerso ;
            positionPerso = this->getPositionHero();
            this->bougerLaMap(carte,&positionPerso,in);
            v_y += v_grav;
            carte->AfficherMonde(screen,&positionPerso);
            drawPlayer(screen);
            //Affiche l'écran
            SDL_Flip(screen);
            SDL_Delay(20);
        }
        _etat = MARCHE;
    }else{
        Deplace(carte,vx,vy);
        SDL_Rect  positionPerso ;
        positionPerso = this->getPositionHero();
        this->bougerLaMap(carte,&positionPerso,in);
        centerScrollingOnPlayer(carte);
    }
}

// recupere le vecteur pour le sens du deplacement
// si c'est en bas on ferra un deplacement
// avec un vecteurX = 0 et un vecteurY = + 2
void Personnage::RecupererVecteur(Evenement* in,int* vx,int* vy){
    *vx = *vy = 0;
    if (in->key[SDLK_UP] && _etat != SAUT){
        _etat = SAUT;
        *vy = -_prop.HAUTEUR_SAUT;
        //*vy = -_prop.VITESSE_JOUEUR;
    }else
    if (in->key[SDLK_DOWN]){
        _etat = MARCHE;
        *vy = _prop.VITESSE_JOUEUR;
       // cout << "B ";
    }else
    if (in->key[SDLK_LEFT]){
        _etat = MARCHE;
        _direction = GAUCHE;
        _sprite = IMG_Load("img/walkleft.png");
        *vx = -_prop.VITESSE_JOUEUR;
       // cout << "L ";
    }else
    if (in->key[SDLK_RIGHT]){
        _etat = MARCHE;
        _direction = DROITE;
        _sprite = IMG_Load("img/walkright.png");
        *vx = _prop.VITESSE_JOUEUR;
      //  cout << "R ";
    }else{
        *vy = _prop.VITESSE_CHUTE;
       // cout << "??";
    }
}
// on essaye un deplacement, si on vas pas sur un obstacle
bool Personnage::EssaiDeplacement(Monde* carte,int vx,int vy) {
    SDL_Rect test;
    test.h = _h;
    test.w = _w;
    test.x = _x + vx;
    test.y = _y + vy;

    if ( ! carte->CollisionDecor(&test) ){
        _x = test.x ;
        _y = test.y ;
        return true;
    }
    return false;
}

bool Personnage::EssaiSaut(Monde* carte,double vx,double vy) {
    SDL_Rect test;
    test.h = _h;
    test.w = _w;
    test.x = _x + vx;
    test.y = _y + vy;

    if ( ! carte->CollisionDecor(&test) ){
        _x = test.x ;
        _y = test.y ;
        return true;
    }
    return false;
}

// permet de ce coller au obstacle
void Personnage::Affine(Monde* carte,int vx,int vy) {
    int i;
    for( i=0 ; i< (int) abs(vx) ; i++){
        if (!EssaiDeplacement(carte,signeValeur(vx),0))
            break; // si on a un deplacement horizontale valide on stop
    }
    for( i=0 ; i < (int) abs(vy) ; i++){
        if (!EssaiDeplacement(carte,0,signeValeur(vy)))
            break; // si on a un deplacement verticale valide on stop
    }
}

void Personnage::Deplace(Monde* carte,int vx,int vy){
    // PAS UTILE CAR LA VITESSE DU JOUEUR NE DEPASSE PAS LA TAILLE DU PERSO

    if (vx >= _prop.LONGEUR_PERSO || vy >= _prop.HAUTEUR_PERSO){
        Deplace(carte,vx/2,vy/2);
        Deplace(carte,vx-vx/2,vy-vy/2);
        return;
    }

    // on test si le deplacement est possible sinon on bouge pas
    if (EssaiDeplacement(carte,vx,vy))
        return;
    Affine(carte,vx,vy);
}
void Personnage::bougerLaMap(Monde * monde,SDL_Rect * positionPerso,
                              Evenement * event) {

    if (event->key[SDLK_LEFT]){
        monde->setHoriScroll(monde->getHoriScroll() - _prop.VITESSE_SCROLL);
    }
    if (event->key[SDLK_RIGHT]){
        monde->setHoriScroll(monde->getHoriScroll() + _prop.VITESSE_SCROLL);
    }
    if (event->key[SDLK_UP]){
        monde->setVertiScroll(monde->getVertiScroll() - _prop.VITESSE_SCROLL);
    }
    if (event->key[SDLK_DOWN]){
        monde->setVertiScroll(monde->getVertiScroll() + _prop.VITESSE_SCROLL);
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

    //cout << " X " << monde->getHoriScroll() << " Y " << monde->getVertiScroll() <<endl ;

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

    if ( monde->getHoriScroll() > monde->getNbrTuilesEnColonneMonde()
         * monde->getLargeurTuile() - _largeurFenetre - 1 ){

        monde->setHoriScroll(monde->getNbrTuilesEnColonneMonde()
                * monde->getLargeurTuile() - _largeurFenetre -1);
    }
    if ( monde->getVertiScroll() > monde->getNbrTuilesEnLigneMonde()
         * monde->getHauteurTuile() - _hauteurFenetre - 1 )

        monde->setVertiScroll(monde->getNbrTuilesEnLigneMonde()
                * monde->getHauteurTuile() - _hauteurFenetre - 1);

}

void Personnage::centerScrollingOnPlayer(Monde * m){
    //On définit les coordonnées du début de l'affichage de la map par rapport à celles
    //du joueur.
    //Pour centrer le joueur, la map doit donc s'afficher à un demi-écran avant la position
    //du joueur.
    //Puis on "clamp" (limite) l'affichage de l'écran pour ne pas sortir de la map.

    m->setHoriScroll(_x - (_largeurFenetre / 2));
    if (m->getHoriScroll() < 0){
        m->setHoriScroll(0);
    }else if (m->getHoriScroll() + _largeurFenetre >= m->getMaxX()){
        m->setHoriScroll(m->getMaxX() - _largeurFenetre);
    }
    m->setVertiScroll(_y - (_largeurFenetre / 2));
    if (m->getVertiScroll() < 0){
        m->setVertiScroll(0);
    } else if (m->getVertiScroll() + _hauteurFenetre >= m->getMaxY()){
        m->setVertiScroll(m->getMaxY() - _hauteurFenetre);
    }
    if ( m->getHoriScroll() >  _x/2 ) {
        m->setHoriScroll(_x/2);
    }
    if ( m->getHoriScroll() <  _x/2 ) {
        m->setHoriScroll(_x/2);
    }
    if ( m->getVertiScroll() <  _y/2 ) {
        m->setVertiScroll(_y/2);
    }
    if ( m->getVertiScroll() >  _y/2 ) {
        m->setVertiScroll(_y/2);
    }
}

int Personnage::signeValeur(int x) {
    if ( x == 0) {
        return 0;
    } else if ( x < 0 ) {
        return -1;
    } else {
        return 1;
    }
}
