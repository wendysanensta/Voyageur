#ifndef GENETIQUE_HPP_INCLUDED
#define GENETIQUE_HPP_INCLUDED
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "projet.hpp"

template <typename T>
class Individu
{
    private :
    int n ; //taille de l'individu
    vector<T> ind ; //vecteur de T
    public :
    Individu(int, vector<T>);   //constructeur

    virtual double adaptation () const = 0;
};

//constructeur
template<typename T>
Individu<T>::Individu(int l, vector<T> v)
{
    n=l;
    ind = v;
}

template<typename T>
class Population
{
    public :
    vector<Individu<T>> p;
};

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
