#ifndef PROJET_HPP_INCLUDED
#define PROJET_HPP_INCLUDED
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Ville
{
public :
    string nom;
    double x;
    double y;
    int indice; //indice de la ville dans le fichier texte, commence à 1
    //constructeur
    Ville(string name, double a, double b, int indice);
};
void print(const Ville & ville); //affichage de la ville
double distance(const Ville & ville1, const Ville & ville2); //calcul de la disgance entre deux villes
ostream & operator<<(ostream & os, const Ville & v); //surcharge de l'opérateur flux pour l'affichage


class MatriceAdjacence
{
    public :
        int n;
        vector<int> adjacence; //matrice d'adjacence

    //constructeur
    MatriceAdjacence(){};
    MatriceAdjacence(vector<Ville> const &, vector<pair<int,int>> const& );

    int operator[](int i) const{return adjacence[i];}
    int& operator[](int i) {return adjacence[i];}
    double operator()(int i, int j) const {return adjacence[(i-1)*n + (j-1)];} //on commence à compter les lignes et les colonnes à partir de 1
    //double& operator()(int i, int j) {return adjacence[i*n +j];}
};
void printAdjacence(const MatriceAdjacence & adj);



#endif // PROJET_HPP_INCLUDED
