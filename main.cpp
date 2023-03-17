#include <iostream>
#include <fstream>
using namespace std;
#include "projet.hpp"
#include "genetique.hpp"

int main()
{
    ifstream fichier("C:/users/wen21/downloads/projet sim test/villes.txt");  //On ouvre le fichier
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
        Ville v(nom,x,y,i);
        villes.push_back(v);
    }

    //Boucle d'affichage des villes lues dans le fichier
    /*cout << "Lecture des villes dans le fichier texte "<< endl;
    for (int k=0; k<nbr; k++)
    {
        cout << villes[k] << endl;
    }*/


    //Creation de la liste des paires de voisins
    vector<pair<int,int>> voisins;
    ifstream fichier2("C:/users/wen21/downloads/projet sim test/voisins.txt");
    int i; int j;
    //boucle for sur le nombre de lignes
    while (fichier2 >> i >> j)
    {
        pair<int,int> paire; paire.first = i-1; paire.second = j-1; //on commence à copter les villes à partir de 1
        voisins.push_back(paire);
    }

    //création de la matrice d'adjacence + affichage
    MatriceAdjacence adjacence(villes, voisins);
    printAdjacence(adjacence);

    cout << "Test de la fonction adjacence(i,j) pour i=2, j =4 : " << adjacence(2,4) << endl; //test de l'opérateur M(i,j)


    //creation d'un chemin pour tester la fonction adaptation
    vector<Ville> v_test1;
    v_test1.push_back(villes[1]);
    v_test1.push_back(villes[3]);
    v_test1.push_back(villes[5]);
    v_test1.push_back(villes[4]);

    Chemin chemin_test1(adjacence, v_test1); //adaptation finie
    Chemin chemin_test2(adjacence, villes); // adaptation infinie
    double adapt = adaptation(chemin_test2);
    cout << "L'adaptation du chemin est : " << adapt << endl; // semble fonctionner OK

    //creation d'une population
    vector<Chemin> popu;
    popu.push_back(chemin_test1);
    popu.push_back(chemin_test2);
    Population p(popu);
    /*cout << "Affichage de la population :" << endl;
    cout << "Chemin test 1 :" << endl;
    chemin_test1.affiche();
    cout << "Chemin test 2 :" << endl;
    chemin_test2.affiche();*/

    //test fonction hybridation
    Chemin hybride1 = chemin_test1;
    Chemin hybride2 = chemin_test2;
    hybridation(chemin_test2, chemin_test2, hybride1, hybride2);
    /*cout << "Hybride 1 :" << endl;
    hybride1.affiche();
    cout << "Hybride 2 :" << endl;
    hybride2.affiche();*/

    /*test initialisation de chemin
    Chemin c1 = init_chemin(villes,adjacence);
    cout << "Affichage d'un chemin licite :" << endl;
    c1.affiche();*/

    /*test mutation et hybridation
    cout << "Chemin initial : " << endl;
    chemin_test2.affiche();
    cout << "Chemin muté : " << endl;
    Chemin chemin_mute = chemin_test2;
    Chemin chemin_mute2 = chemin_test2;
    Chemin chemin_mute3 = chemin_test2;
    //mutation(chemin_test2, chemin_mute);
    mutation_flip(chemin_test2, chemin_mute);
    chemin_mute.affiche();


    hybridation(chemin_test2,chemin_test2,chemin_mute,chemin_mute2);
    cout << "Test de l'hybridation : " << endl;
    chemin_mute2.affiche();
    chemin_mute3.affiche(); //je crois que ça marche*/


    //test selection
    cout << "Population initiale" << endl;
    p.affiche();
    Population p_select;
    //selection_roulette(p_select, p, 1);
    selection_rang(p_select,p,1);
    cout << "Affichage selection" << endl;
    p_select.affiche(); //il faudrait davantage de chemins pour tester la selection


    return 0;
}
