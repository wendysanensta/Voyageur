#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "projet.hpp"

using namespace std;

//constructeur de ville
Ville::Ville(string name, double a, double b, int i)
{
    nom=name;
    x=a;
    y=b;
    indice = i;
}


void print(const Ville & ville)
{
    cout<< ville.nom << "(" << ville.x << "," << ville.y << ")" << endl;
}

//calcule la distance entre 2 villes
double distance(const Ville & v1, const Ville & v2)
{
    return sqrt((v1.x -v2.y)*(v1.x -v2.y)+ (v1.y - v2.y)*(v1.y - v2.y));
}

ostream & operator<<(ostream & os, const Ville & v)
{
    os << v.nom << "(" << v.x << "," << v.y << ")";
    return os;
}

void printAdjacence(const MatriceAdjacence & adj)
{
    cout << adj.n <<" "<< adj.adjacence.size() << endl;
    for (int i=0; i<adj.n; i++)
    {
        cout << "[ ";
        for (int j=0; j<adj.n; j++)
        {
            cout << adj[i*adj.n +j] << " ";
        }
        cout << "] \n";
    }
    cout << endl;
};

