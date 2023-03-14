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
void print(const Ville & ville);
double distance(const Ville & ville1, const Ville & ville2);
ostream & operator<<(ostream & os, const Ville & v);


class MatriceAdjacence
{
    public :
        int n;
        vector<int> adjacence; //matrice d'adjacence

    //constructeur
    MatriceAdjacence(){};
    MatriceAdjacence(vector<Ville> const &villes, vector<pair<int,int>> const& vois): n(villes.size()),adjacence(n*n,-1)
    {
        for (int k=0; k < vois.size(); k++)
        {
            int i=vois[k].first;
            int j=vois[k].second;
            double d = distance(villes[i],villes[j]);
            adjacence[i*n + j] = d;
            adjacence[j*n + i] = d;
        }
    }
    int operator[](int i) const{return adjacence[i];}
    int& operator[](int i) {return adjacence[i];}
    double operator()(int i, int j) const {return adjacence[(i-1)*n + (j-1)];} //on commence à compter les lignes et les colonnes à partir de 1
    //double& operator()(int i, int j) {return adjacence[i*n +j];}
};
void printAdjacence(const MatriceAdjacence & adj);



#endif // PROJET_HPP_INCLUDED
