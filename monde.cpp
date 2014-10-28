#include "monde.h"


Monde::Monde(string nomFichier
             , int largeurFenetre , int hauteurFenetre)throw (ExceptionGame){

    _largeurFenetre = largeurFenetre;
    _hauteurFenetre = hauteurFenetre;
    _horiScroll = 0;
    _vertiScroll = hauteurFenetre;

    // ouvre en lecture
    ifstream fichier(nomFichier.c_str(), ios::in);
    if ( fichier ){
        chargerInfoDepuisFichier(fichier);
        chargerNiveauDepuisFichier(fichier);
    }else{
       throw new ExceptionGame("Erreur d'ouverture du fichier");
    }

    fichier.close();
}

void Monde::setHoriScroll(int horiScroll){
    _horiScroll = horiScroll;
}

void Monde::setVertiScroll(int vertiScroll){
    _vertiScroll = vertiScroll;
}
int Monde::getHoriScroll()const{
    return _horiScroll;
}
int Monde::getVertiScroll()const{
    return _vertiScroll;
}
int Monde::getLargeurTuile() const{
    return _largeurTuile;
}
int Monde::getHauteurTuile() const{
    return _hauteurTuile;
}
int Monde::getNbrTuilesEnColonneMonde() const{
    return _nbrTuilesEnColonneMonde;
}
int Monde::getNbrTuilesEnLigneMonde()const{
   return _nbrTuilesEnLigneMonde;
}

void Monde::AfficherMonde(SDL_Surface * fenetre){

    SDL_Rect rectDest;
    int numTuile;
    int minX,minY,maxX,maxY;
    minX = _horiScroll / _largeurTuile-1;
    minY = _vertiScroll / _hauteurTuile-1;
    maxX = ((_horiScroll + _largeurFenetre) / _largeurTuile);
    maxY = ((_vertiScroll + _hauteurFenetre) / _hauteurTuile);

    for ( int i = minX; i <=  maxX ; i++){
        for ( int j = minY ; j <= maxY ; j++){
            rectDest.x = i * _largeurTuile - _horiScroll;
            rectDest.y = j * _hauteurTuile - _vertiScroll;

            if ( i < 0
                 || i >= _nbrTuilesEnColonneMonde
                 || j < 0
                 || j >= _nbrTuilesEnLigneMonde){
                numTuile = 0;
            }else{
                numTuile = _schema[j][i];

            }

            SDL_BlitSurface(_imagesDesTuiles
                            ,&(_tuiles[numTuile].getRectangle()),fenetre,&rectDest);
        }
    }
}

bool Monde::CollisionDecor(SDL_Rect* perso){
    int xmin,xmax,ymin,ymax,i,j,indicetile;
    xmin = perso->x / _largeurTuile;
    ymin = perso->y / _hauteurTuile;
    xmax = (perso->x + perso->w -1) / _largeurTuile;
    ymax = (perso->y + perso->h -1) / _hauteurTuile;

    if (xmin < 0
            || ymin < 0
            || xmax >= _nbrTuilesEnColonneMonde
            || ymax >= _nbrTuilesEnLigneMonde)
        return 1;

    for ( i = xmin ; i <=  xmax  ; i++) {
        for ( j = ymin ; j <= ymax  ; j++){
            indicetile = _schema[j][i];
            if (_tuiles[indicetile].getType() == TypeTuile::MUR){
                return true;
            }
        }
    }
    return false;
}

//*******************************************************//

void Monde::chargerInfoDepuisFichier(ifstream &fichier) throw(ExceptionGame){

    string baliseTitre, nomFichierImage,baliseNbrTuileImg;
    string baliseTypeTuile,typeTuile;

    fichier >> baliseTitre;
    if ( baliseTitre.compare(BALISE_FICHIER_IMAGE) == 0 ){
        fichier >> nomFichierImage;
        _imagesDesTuiles = chargerImage(nomFichierImage);
    }else{
        throw new ExceptionGame("Votre fichier ne contient pas la balise #nomFichierImage");
    }

    fichier >> baliseNbrTuileImg;
    if ( baliseNbrTuileImg.compare(BALISE_NBR_T_H_FI) == 0 ){
        fichier >> _nbrTuilesEnColonne;
    }else{
        throw new ExceptionGame("Votre fichier ne contient pas la balise #nbrTuilesColonneFichierImage");
    }

    fichier >> baliseNbrTuileImg;
    if ( baliseNbrTuileImg.compare(BALISE_NBR_T_V_FI) == 0 ){
        fichier >> _nbrTuilesEnLigne;
    }else{
        throw new ExceptionGame("Votre fichier ne contient pas la balise #nbrTuilesLigneFichierImage");
    }

    _largeurTuile = _imagesDesTuiles->w / _nbrTuilesEnColonne;
    _hauteurTuile = _imagesDesTuiles->h / _nbrTuilesEnLigne;

    fichier >> baliseTypeTuile;
    if ( baliseTypeTuile.compare(BALISE_TYPE_TUILE) == 0 ){
        _tuiles.resize(_nbrTuilesEnLigne*_nbrTuilesEnColonne);

        for ( int j=0,numTuile=0 ; j < _nbrTuilesEnLigne ; j++){
            for ( int i=0 ; i < _nbrTuilesEnColonne ; i++){
                _tuiles[numTuile].setRectangle(_largeurTuile
                                               ,_hauteurTuile
                                               ,i*_largeurTuile
                                               ,j*_hauteurTuile);
                fichier >> typeTuile;
                fichier >> typeTuile;
                if(typeTuile.compare("mur") == 0){
                    _tuiles[numTuile].setType(TypeTuile::MUR);
                }else if(typeTuile.compare("eau") == 0){
                    _tuiles[numTuile].setType(TypeTuile::EAU);
                }else if(typeTuile.compare("ciel") == 0){
                    _tuiles[numTuile].setType(TypeTuile::CIEL);
                }else{
                    _tuiles[numTuile].setType(TypeTuile::CIEL);
                }
                numTuile++;
            }
        }
    }else{
        throw new ExceptionGame("Votre fichier ne contient pas la balise #typeTuile");
    }

}

SDL_Surface* Monde::chargerImage(string nomFichierImage){
    SDL_Surface* image_result;
    // charge l'image dans image_ram en RAM
    SDL_Surface* image_ram = SDL_LoadBMP(nomFichierImage.c_str());

    if (image_ram == NULL){
        throw new ExceptionGame("l'image "+nomFichierImage+" est introuvable ");
    }

    image_result = SDL_DisplayFormat(image_ram);
    SDL_FreeSurface(image_ram);
    return image_result;
}

void Monde::chargerNiveauDepuisFichier(ifstream& fichier){

    string baliseTailleMonde, baliseNiveau;
    int numTuile;
    fichier >> baliseTailleMonde;
    if ( baliseTailleMonde.compare(BALISE_TAILLE_MONDE) == 0){
        fichier >> _nbrTuilesEnColonneMonde;
        fichier >> _nbrTuilesEnLigneMonde;
    }else{
        throw new ExceptionGame("Votre fichier ne contient pas la balise #tailleMonde");
    }

    fichier >> baliseNiveau;
    if ( baliseNiveau.compare(BALISE_NIVEAU) == 0){
        _schema.resize(_nbrTuilesEnLigneMonde
                       ,std::vector<Uint16>(_nbrTuilesEnColonneMonde));

        for ( int i=0; i < _nbrTuilesEnLigneMonde ; i++){
            for ( int j=0; j < _nbrTuilesEnColonneMonde ; j++){

                fichier >> numTuile;
                if ( numTuile >= _nbrTuilesEnColonne * _nbrTuilesEnLigne){
                    throw new ExceptionGame("Numéro de tuiles Hors limite, présent dans votre fichier");
                }else{
                    _schema[i][j] = numTuile;
                }
            }
        }
    }
}
