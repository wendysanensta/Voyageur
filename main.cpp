#include <iostream>
#include <fstream>
using namespace std;
#include "projet.hpp"
#include "genetique.hpp"

int main()
{
    ifstream fichier("C:/users/wen21/downloads/sim202/villes.txt");  //On ouvre le fichier
    int nbr;
    fichier >> nbr;
    string nom;
    double x,y;
    vector<Ville> villes;
    for (int i=0; i<nbr; i++) //lecture des villes présentes dans le fichier
    {
        fichier >> nom;
        fichier >> x;
        fichier >> y;
        Ville v(nom,x,y);
        villes.push_back(v);
    }

    /*Boucle d'affichage des villes lues dans le fichier
    for (int i=0; i<nbr; i++)
    {
        cout << villes[i] << endl;
    }*/


    vector<pair<int,int>> voisins;
    ifstream fichier2("C:/users/wen21/downloads/sim202/voisins.txt");
    int i; int j;
    //boucle for sur le nombre de lignes
    while (fichier2 >> i >> j)
    {
        pair<int,int> paire; paire.first = i; paire.second = j;
        voisins.push_back(paire);
    }

    //création de la matrice d'adjacence + affichage
    MatriceAdjacence adjacence(villes, voisins);
    printAdjacence(adjacence);

    cout << adjacence(2,4) << endl; //test de l'opérateur M(i,j)
    return 0;
}
