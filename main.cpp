#include <iostream>
#include <fstream>
using namespace std;
#include "projet.hpp"
#include "genetique.hpp"

int main()
{
    ifstream fichier("villes.txt");  //On ouvre le fichier
    int nbr;
    fichier >> nbr;
    string nom;
    double x,y;
    vector<Ville> villes;
    for (int i=0; i<nbr; i++) //lecture des villes pr�sentes dans le fichier
    {
        fichier >> nom;
        fichier >> x;
        fichier >> y;
        Ville v(nom,x,y,i);
        villes.push_back(v);
    }

    //Boucle d'affichage des villes lues dans le fichier
    /*cout << "Lecture des villes dans le fichier texte :"<< endl;
    for (int k=0; k<nbr; k++)
    {
        cout << villes[k] << endl;
    }*/


    //Creation de la liste des paires de voisins
    vector<pair<int,int>> voisins;
    ifstream fichier2("voisins.txt");
    int i; int j;
    //boucle for sur le nombre de lignes
    while (fichier2 >> i >> j)
    {
        pair<int,int> paire; paire.first = i-1; paire.second = j-1; //on commence � copter les villes � partir de 1
        voisins.push_back(paire);
    }

    //cr�ation de la matrice d'adjacence + affichage
    MatriceAdjacence adjacence(villes, voisins);
    printAdjacence(adjacence);

    cout << "Test de la fonction adjacence(i,j) pour i=2, j =4 : " << adjacence(2,4) << endl; //test de l'op�rateur M(i,j)


    //creation d'un chemin pour tester la fonction adaptation
    vector<Ville> v_test1;
    v_test1.push_back(villes[1]);
    v_test1.push_back(villes[3]);
    v_test1.push_back(villes[5]);
    v_test1.push_back(villes[4]);

    Chemin chemin_test1(adjacence, v_test1); //adaptation finie
    Chemin chemin_test2(adjacence, villes); // adaptation infinie
    double adapt = adaptation(init_heur(4,adjacence,villes));
    cout << "L'adaptation du chemin est : " << adapt << endl; // semble fonctionner OK
    cout << endl;
    //creation d'une population
    vector<Chemin> popu;
    popu.push_back(chemin_test1);
    popu.push_back(chemin_test2);


    Population p=pop_init(4, adjacence, villes);

    cout << "Affichage de la population :" << endl;
    cout << "Chemin test 1 :" << endl;
    chemin_test1.affiche(); cout<<endl;
    cout << "Chemin test 2 :" << endl;
    chemin_test2.affiche(); cout<<endl;

    //test fonction hybridation
    cout << "Test de la fonction hybridation sur les deux chemins precedents : " << endl;
    Chemin hybride1 = chemin_test1;
    Chemin hybride2 = chemin_test2;
    hybridation(chemin_test1, chemin_test2, hybride1, hybride2);
    cout << "Hybride 1 :" << endl;
    hybride1.affiche(); cout<<endl;
    cout << "Hybride 2 :" << endl;
    hybride2.affiche(); cout<<endl;


    //test mutation
    cout << "Test de la fonction mutation/mutation flip" << endl;
    cout << "Chemin initial : " << endl;
    chemin_test2.affiche(); cout<< endl;
    cout << "Chemin mut� : " << endl;
    Chemin chemin_mute = chemin_test2;
    Chemin chemin_mute2 = chemin_test2;
    Chemin chemin_mute3 = chemin_test2;
    //mutation(chemin_test2, chemin_mute);
    mutation_flip(chemin_test2, chemin_mute);
    chemin_mute.affiche(); cout<<endl;


    //test selection
    cout << "Population initiale : " << endl;
    p.affiche(); cout << endl;

    Population p_select;
    //selection_roulette(p_select, p, 3);
    selection_rang(p_select, p, 3);
    //selection_tournoi(p_select, p, 3);
    //eugenisme(p_select,p,3);
    cout << "Affichage selection :" << endl;
    p_select.affiche(); cout << endl;


    //test reproduction
    Population p_repro;
    //reproduction(p, p_repro, 6, 1); bug
    cout << "Affichage population reproduction : " << endl;
    p_repro.affiche();


    /*
    Population pf;
    selection_finale(pf, p, 6, 2, 0, 10);
    cout << "Affichage population finale" << endl;
    pf.affiche();
    int s=0;
    for (int i=0; i<6 ; i++){
            s+=adaptation(pf.p[i]);
    }
    cout<<s;*/

    return 0;
}
