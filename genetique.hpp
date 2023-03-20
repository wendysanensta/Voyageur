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
    Chemin(const Chemin& c) //constructeur par copie
    {
        adj = c.adj;
        vec = c.vec;
    };
    Chemin(MatriceAdjacence const & adjacence, vector<Ville> const & v){adj=adjacence; vec = v;};
    void hybridation() const override {};
    void mutation() const override {};
    double adaptation() const override {};

    int size();
    void push_back(const Ville&);

    void affiche();
    //Ville operator[] (int i)  { return vec[i]; };

};

Chemin init_chemin(const vector<Ville> & v, const MatriceAdjacence& adj); //fonction qui cree un chemin licite

double adaptation(const Chemin& c);

class Population
{
    public :
    vector<Chemin> p;
    Population(vector<Chemin> const & c){p=c;};
    Population(){};
    //Population(const Population& popu){p=popu.p;};
    void push_back(const Chemin&);
    Chemin operator[](int i) {return p[i];};

    void affiche();
};

void hybridation(const Chemin& c1, const Chemin& c2, Chemin& ij, Chemin& ji);

void mutation(const Chemin& c, Chemin& c_mute);
void mutation_flip(const Chemin& c, Chemin& c_mute);

void selection_roulette(Population& p_select, Population& p, int taille_popu); //methode 1
void selection_rang(Population& p_select, Population& p, int taille_popu); //methode 2
void selection_tournoi(Population& p_select, Population& p, int taille_popu); //methode 3
void eugenisme(Population& p_select, Population& p, int taille_popu); //methode 4

void reproduction(Population& p, int n, int methode);
void selection_finale(Population& p_finale, Population& p_init, int taille_popu, int methode, int q, int iter);


Chemin init_heur(const int, const MatriceAdjacence&, const vector<Ville>&);
int factorial(int n);
int binomialCoefficient(int n, int k) ;
Population pop_init(const int& , const MatriceAdjacence& , const vector<Ville> & );

#endif
