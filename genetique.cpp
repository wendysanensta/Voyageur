#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include "projet.hpp"
#include "genetique.hpp"


//la fonction adaptation renvoie la longueur du chemin ou +inf s'il n'existe pas.
/* Chemin::adaptation()
{
    int n = vec.size();
    double adapt;
    for (int i=0; i<n-1; i++)
    {
        if (adj((vec[i]).indice, (vec[i+1]).indice)==-1)
        {
            int a = std::numeric_limits<int>::infinity();
            return a;
        }
        else
        {
            adapt =  adapt + distance(vec[i],vec[i+1]);
        }
    }
    return adapt;
}*/

double adaptation(const Chemin& c)
{
    int n = c.vec.size();
    double adapt = 0;
    for (int i=0; i<n-1; i++)
    {
        if (c.adj((c.vec[i]).indice, (c.vec[i+1]).indice)==-1)
        {
            double a = std::numeric_limits<double>::infinity();
            return a;
        } else {
            adapt =  adapt + distance(c.vec[i],c.vec[i+1]);
        }
    }
    return adapt;
}


int Chemin::size() {
    return (*this).vec.size();
}

void Chemin::push_back(const Ville& x) {
    (*this).vec.push_back(x);
}

void Chemin::affiche(){
    int n = vec.size();
    for (int i=0;i<n;i++){
        cout << vec[i] << endl;
    }
}

/*void operator<<(std::ostream& os,const Chemin& c){
    for (int i=0;i<c.vec.size();i++){
        cout << c.vec[i]<< endl;
    }
} bug*/

Chemin init_chemin(const vector<Ville> & v, const MatriceAdjacence& adj){
    bool res = false;
    int n = v.size();
    vector<int> chem;
    double a = std::numeric_limits<double>::infinity();
    Chemin chemin;
    for (int i=0;i<n;i++){
        chem.push_back(i);
    }
    int iter = 0;
    while (res==false){
        iter = iter +1;
        random_shuffle(begin(chem),end(chem));
        cout << "shuffled : " ;
        for (int l=0;l<chem.size()-1;l++){
            cout << chem[l];
        }
        cout<< chem[chem.size()] <<endl;
        vector<Ville> vec;
        for (int k=0;k<n;k++){
            vec.push_back(v[k]);
        }
        chemin.vec = vec;
        chemin.adj = adj;
        res = adaptation(chemin)<a;
        cout << res << endl;
    }
    return chemin;
}


void Population::push_back(const Chemin& c) {
    (*this).p.push_back(c);
}

void Population::affiche()
{
    int n=p.size();
    for (int i=0;i<n;i++)
    {
        p[i].affiche();
    }
}

void hybridation(Chemin& c1, Chemin& c2, Chemin& ij, Chemin& ji)
{
    srand(time(NULL));
    int n = c1.vec.size();
    int l = rand()%n + 1 ; //indice d'hybridation
    //cout << "indice d'hybridation : " << l << endl;
    //hybridation
    vector<Ville> v1;
    vector<Ville> v2;
    for (int i=0; i<n; i++)
    {
        if (i<l)
        {
            v1.push_back(c1.vec[i]);
            v2.push_back(c2.vec[i]);
        }
        else
        {
            v1.push_back(c2.vec[i]);
            v2.push_back(c1.vec[i]);
        }
    }
    ij.vec = v1;
    ji.vec = v2;
}


void mutation(const Chemin& c, Chemin& c_mute)
{
    int n = c.vec.size();
    srand(time(NULL));
    int k = rand()%n;
    int l = rand()%n;
    //cout << "Indices d'hybridation (k,l) = (" << k <<"," << l << ")" << endl;
    c_mute = c;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[l] = c.vec[k];
}

void mutation_flip(const Chemin& c, Chemin& c_mute)
{
    int n = c.vec.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    //cout << "Indices d'hybridation (k,l) = (" << k <<"," << l << ")" << endl;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[k-1] = c.vec[l-1];
    c_mute.vec[l] = c.vec[k];
    c_mute.vec[l-1] = c.vec[k-1];
}


void selection_roulette(Population& p_select, Population& p, int taille_popu)
{
    int taille = 0;
    int n = p.p.size();
    if (n<taille_popu)
    {
        cout << "Erreur : population à sélectionnée plus grande que population initiale" << endl;
    }
    srand(time(NULL));
    double S = 0;
    vector<double> adapt; //adaptation de chaque chemin
    vector<int> track; //pour verifier si un individu a déjà été choisi ou pas
    for (int i = 0; i<n ; i++)
    {
        double a = adaptation(p.p[i]);
        S = S + a;
        adapt.push_back(a);
        track.push_back(0);
    }
    //selection
    while (taille<taille_popu)
    {
        double r = ((double)rand()/RAND_MAX)*S;
        double somme = 0;
        int k = 0;
        while (somme<r)
        {
            somme = somme + adapt[k];
            k = k + 1;
        }
        if (track[k]==0)
        {
            Chemin c;
            c.vec = p[k].vec;
            c.adj = p[k].adj;
            p_select.push_back(c);
            track[k] = 1;
            taille = taille + 1;
        }
    }
}
/*
bool compare_pair(pair p1, pair p2)
{
    return (p1.first<p2.first);
}

Population* reproduction(const Population& p, int n, int methode)
{
    Population p_tilde1;
    Population p_tilde2;
    //vecteurs qui nous donnent l'adaptation des individus adaptes ( < infini) et un autre vecteur qui nous donne leurs indices
    vector<double> adapt;
    vector<int> indices;
    int l = p.p.size();

    //calcul de l'adaptation de chaque individu, en supprimant les individus non adaptes
    for (int i=0;i<l;i++)
    {
        double a = (p.p[i]).adaptation();
        if (a<std::numeric_limits<int>::infinity())
        {
            adapt.push_back(a);
            indices.push_back(i);
        }
    }

    //selection de n individus reproducteurs
    for (int i=0; i<n; i++)
    {
        p_tilde1[i]=selection_roulette(p, adapt);
    }
    /*for (int i=0; i<n; i++){
        if (methode % 4==0){
            p_tilde1(i)=selection_roulette(p);
        }
        if (methode % 4==1) {
            p_tilde1(i)=selection_rang(p);
        }
        if (methode % 4==2) {
            p_tilde1(i)=selection_tournoi(p);
        }
        if (methode % 4==3) {
            p_tilde1(i)=eugenisme(p);
        }
    }


    //hybridation
    int k = 0;
    while (k<n/2)
    {
        int i = rand()%n;
        int j = rand()%n;
        Chemin chem = hybridation(p_tilde1.p[i],p_tilde1.p[j]);
        if (adaptation(chem) < std::numeric_limits<HUGE_VAL>::infinity())
        {
            p_tilde2.pushback(chem);
            k = k + 1;
        }
    }
}
*/



/*int selection_rang(const Population& p, vector<double> rang)
{
    //tri des individus par leur fonction adaptation

    vector<pair<double,int>> paires;
    int n = p.p.size();

    for (int i=0; i<n; i++)
    {
        pair<double, int> paire;
        paire.first = adaptat(i);
        paire.second = i;
        paris.push_back(paire);
    }
    sort(paires.begin(),paires.end(),compare_pair);
    double S = 0;
    for (int i=0; i<n; i++)
    {
        S = S + adapt(i);
    }
    double rang = 0;
        paire.first = adapt(i);
        paire.second = i;
        paires.push_back(paire);
    }
    sort(paires.begin(),paires.end(),compare_pair);

    vector<double> rang;
    for (int i=0; i<n; i++)
    {
        rang(paires(i).second)=i;
    }

    int i = 0;
    while (somme<S)
    {
        somme = somme + ;
        i = i + 1;
    }
    Chemin c = p(paires(i).second);
    p.erase(i);

}
*/

