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
    Individu(){};   //constructeur
    virtual void hybridation() const=0;
    virtual void mutation() const=0;
    virtual double adaptation () const = 0;
};


class Chemin : public Individu
{
    public :
    MatriceAdjacence adj;
    vector<Ville> vec;
    Chemin(){};
    Chemin(MatriceAdjacence const & adjacence, vector<Ville> const & v){adj=adjacence; vec = v;};

    void hybridation() const override { /* implementation here */ }
    void mutation() const override { /* implementation here */ }
    double adaptation() const override { /* implementation here */ }

    //void hybridation();
    //void mutation();
    //double adaptation();

    int size();
    void push_back(const Ville&);
    void affiche();
    //void operator<<(std::ostream& os); bug
    //Ville operator[] (int i)  { return vec[i]; };

};


double adaptation(const Chemin& c);

class Population
{
    public :
    vector<Chemin> p;
    Population(vector<Chemin> const & c){p=c;};

    void push_back(const Chemin&);
    Chemin operator[](int i) {return p[i];} ;
};

void hybridation(Chemin& c1, Chemin& c2, Chemin& ij, Chemin& ji);

/*void mutation(const Chemin& c, Chemin& c_mute);
void mutation_flip(const Chemin& c, Chemin& c_mute);

Population* reproduction(const Population& p, int n, int methode);
Chemin* selection_roulette(const Population& p, vector<double> adapt);*/


#endif
