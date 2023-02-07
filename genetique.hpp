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
    virtual double adaptation(Individu& i) const;
};

class Population
{

};

class Chemin : public Individu
{
    public :

};

//Génération de nouveaux individus
 Tournee hybridation

#endif
