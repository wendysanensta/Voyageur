#ifndef GENETIQUE_HPP_INCLUDED
#define GENETIQUE_HPP_INCLUDED
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "projet.hpp"


class Individu
{
    public :
    virtual double adaptation(Individu& i) const = 0;
};

class Population
{
    public :
    Vector<Individu> p;
};

class Chemin : public Individu
{
    public :
    Vector<Ville> c;
    double adaptation(Chemin& tournee) const;

};

//Génération de nouveaux individus
 Tournee hybridation

 // on génère un chemin aléatoire, pas forcément licite (sa fonction d'adaptation est égale à l'infini) On la fait muter :
 // si les mutants sont de fonction d'adaptation infinie, alors on en choisit une aléatoirement, jusqu'à ce qu'on tombe sur une ville d'adaptation finie
// utiliser la fonction min de la STL et l'infini

#endif
