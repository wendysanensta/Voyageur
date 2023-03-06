#ifndef GENETIQUE_HPP_INCLUDED
#define GENETIQUE_HPP_INCLUDED
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <random>
#include <bits/stdc++.h>
#include "projet.hpp"


class Individu
{
    public :
    Individu();   //constructeur
    virtual void hybridation() const=0;
    virtual void mutation() const=0;
    virtual double adaptation () const = 0;
};



class Population
{
    public :
    vector<Individu> p;

    Population();
};



class Chemin : public Individu
{
    public :
    static MatriceAdjacence adj;
    vector<Ville> vec;
    double adaptation();
    void hybridation();
    void mutation();


    int size();
    void push_back(const Ville&);
    Ville operator[] (int i)  { return vec[i]; };

};


 // on génère un chemin aléatoire, pas forcément licite (sa fonction d'adaptation est égale à l'infini) On la fait muter :
 // si les mutants sont de fonction d'adaptation infinie, alors on en choisit une aléatoirement, jusqu'à ce qu'on tombe sur une ville d'adaptation finie
// utiliser la fonction min de la STL et l'infini



#endif
