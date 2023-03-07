#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include "projet.hpp"
#include "genetique.hpp"




    int Chemin::size() {
        return (*this).vec.size();
    }

    void Chemin::push_back(const Ville& x) {
        (*this).vec.push_back(x);
    }


//la fonction adaptation renvoie la longueur du chemin ou +inf s'il n'existe pas.
double Chemin::adaptation()
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
}


void hybridation(const Chemin& c1, const Chemin& c2, Chemin& ij, Chemin& ji)
{
    int n = c1.vec.size();
    int l = rand()%n + 1 ; //indice d'hybridation
    //hybridation
    for (int i=0; i<n; i++)
    {
        if (i>l)
        {
            ij.vec[i] = c1.vec[i];
            ji.vec[i] = c2.vec[l];
        }
        else
        {
            ij.vec[i] = c2.vec[i];
            ji.vec[i] = c1.vec[l];
        }
    }

}


void mutation(const Chemin& c, Chemin& c_mute)
{
    int n = c.vec.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    c_mute = c;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[l] = c.vec[k];
}

void mutation_flip(const Chemin& c, Chemin& c_mute)
{
    int n = c.vec.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[k-1] = c.vec[l-1];
    c_mute.vec[l] = c.vec[k];
    c_mute.vec[l-1] = c.vec[k-1];
}

Population reproduction(const Population& p, int n, int methode)
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
        double a = adaptation(p.p[i]);
        if (a<std::numeric_limits<HUGE_VAL>::infinity())
        {
            adapt.pushback(a);
            indices.pushback(i);
        }
    }

    //selection de n individus reproducteurs

    for (int i=0; i<n; i++){
        if (methode % 4==0){
            p_tilde1[i]=selection_roulette(p)

        }
        if (methode % 4==1) {
            p_tilde1[i]=selection_rang(p)
        }
        if (methode % 4==2) {
            p_tilde1[i]=selection_tournoi(p)
        }
        if (methode % 4==3) {
            p_tilde1[i]=eugenisme(p)
        }
    }


    //hybridation
    int k = 0
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

Chemin selection_roulette(const Population& p, vector<double> adapt)
{
    double S = 0;
    int n = p.p.size();

    for (int i = 0; i<n ; i++)
    {
        //S = S + adaptation(p.p[i]);
        S = S + adapt(i);
    }
    double r = ((double)rand()/RAND_MAX)*S;
    double somme = 0;
    int i = 0;
    while (somme<S)
    {
        somme = somme + adaptation(p.pi[i]);
        i = i + 1;
    }
    Chemin c=p(i);
    p.erase(i);
    return c;
}

bool compare_pair(pair p1, pair p2)
{
    return (p1.first<p2.first);
}


int selection_rang(const Population& p, vector<double> adapt)
{
    //tri des individus par leur fonction adaptation
    /*
    vector<pair<double,int>> adapt;
    int n = p.p.size();

    for (int i=0; i<n; i++)
    {
        pair<double, int> paire;
        paire.first = adaptation(p.p[i]);
        paire.second = i;
        adapt.push_back(paire);
    }
    sort(adapt.begin(),adapt.end(),compare_pair);
    */
    vector<double> rang;



}

