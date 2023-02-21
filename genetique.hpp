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

template <typename T>
class Individu
{
    private :
    vector<T> ind ; //vecteur de T
    public :
    Individu();   //constructeur

    int size();
    void push_back(const T&);
    T operator[] (int i)  { return ind[i]; };

    virtual double adaptation () const = 0;
};

template <typename T>
int Individu<T>::size() {
    return *this.ind.size();
}

template <typename T>
void Individu<T>::push_back(const T& x) {
    return *this.ind.push_back(x);
}



template<typename T>
class Population
{
    public :
    vector<Individu<T>> p;

    Population();
};

template<typename T>
Population::Population(){


    }
}

class Chemin : public Individu<Ville>
{
    private :
    static MatriceAdjacence adj;

    public :
    double adaptation() const;


};

 // on génère un chemin aléatoire, pas forcément licite (sa fonction d'adaptation est égale à l'infini) On la fait muter :
 // si les mutants sont de fonction d'adaptation infinie, alors on en choisit une aléatoirement, jusqu'à ce qu'on tombe sur une ville d'adaptation finie
// utiliser la fonction min de la STL et l'infini



#endif
