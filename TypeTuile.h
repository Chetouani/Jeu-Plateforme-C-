#ifndef TYPETUILE_H
#define TYPETUILE_H

/*!
 * \brief Représente le type d'une tuile
 */
enum class TypeTuile : unsigned short{
    CIEL,/*On peut traverser*/
    MUR,/*On peut pas traverser, c'est un obstacle*/
    EAU/*On peut traverser mais on meurt*/
};

#endif // TYPETUILE_H
