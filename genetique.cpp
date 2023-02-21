#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include "projet.hpp"
#include "genetique.hpp"

//la fonction adaptation renvoie la longueur du chemin ou +inf s'il n'existe pas.
Chemin::double adaptation()
{
    c = this*;
    int n = c.ind.size();
    double adapt;
    for (int i=0; i<n-1,i++)
    {
        if (adj[c[i][c[i+1]]==-1)
        {
            int a = std::numeric_limits<HUGE_VAL>::infinity();
            return a;
        };
        else
        {
            adapt+ = distance[c[i]][c[i+1]];
        }
    }
    return adapt;
}


void hybridation(const Individu& c1, const Individu& c2, Individu& ij, Individu& ji)
{
    int n = c1.ind.size();
    int l = rand()%n + 1 ; //indice d'hybridation
    //hybridation
    for (int i=0; i<n; i++)
    {
        if (i>l)
        {
            ij.ind[i] = c1.ind[i];
            ji.ind[i] = c2.ind[j];
        }
        else
        {
            ij.ind[i] = c2.ind[i];
            ji.ind[i] = c1.ind[j];
        }
    }

}


void mutation(const Individu& c, Individu& c_mute)
{
    int n = c1.ind.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    c_mute = c;
    c_mute.ind[k] = c.ind[l];
    c_mute.ind[l] = c.ind[k];
}

Individu mutation_flip(const Individu& c)
{
    int n = c1.ind.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    Chemin c_mute = c;
    c_mute.ind[k] = c.ind[l];
    c_mute.ind[k-1] = c.ind[l-1];
    c_mute.ind[l] = c.ind[k];
    c_mute.ind[l-1] = c.ind[k-1];
    return c_mute;
}

Population reproduction(const Population& p, int n)
{
    Population<int> p_tilde1;
    Population<int> p_tilde2;
    //vecteurs qui nous donnent l'adaptation des individus adaptes ( < infini) et un autre vecteur qui nous donne leurs indices
    vector<double> adapt;
    vector<int> indices
    int l = p.p.size();

    //calcul de l'adaptation de chaque individu, en supprimant les individus non adaptes
    for (int i=0;i<l;i++)
    {
        double a = adaptation(p.pi[i]);
        if (a<std::numeric_limits<HUGE_VAL>::infinity())
        {
            adapt.pushback(a);
            indices.pushback(i);
        }
    }

    //selection de n individus
    int c = 0; //compteur
    while((c!=n)&(adapt.size()!=0))
    {
        int k = min_element(adapt.begin(),adapt.end());
        adapt.pop(k);
        p_tilde1.p.pushback(k);
        c = c +1;
    }

    for

}
