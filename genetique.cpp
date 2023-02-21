#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
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
            int a = std::numeric_limits<HUGE_VAL>::infinity();
            return a;
        };
        else
        {
            adapt+ = distance[vec[i]][vec[i+1]];
        }
    }
    return adapt;
}


void hybridation(const Individu& c1, const Individu& c2, Individu& ij, Individu& ji)
{
    int n = c1.vec.size();
    int l = rand()%n + 1 ; //indice d'hybridation
    //hybridation
    for (int i=0; i<n; i++)
    {
        if (i>l)
        {
            ij.vec[i] = c1.vec[i];
            ji.vec[i] = c2.vec[j];
        }
        else
        {
            ij.vec[i] = c2.vec[i];
            ji.vec[i] = c1.vec[j];
        }
    }

}


void mutation(const Individu& c, Individu& c_mute)
{
    int n = c1.vec.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    c_mute = c;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[l] = c.vec[k];
}

Individu mutation_flip(const Individu& c)
{
    int n = c1.vec.size();
    int k = rand()%n +1;
    int l = rand()%n +1;
    Chemin c_mute = c;
    c_mute.vec[k] = c.vec[l];
    c_mute.vec[k-1] = c.vec[l-1];
    c_mute.vec[l] = c.vec[k];
    c_mute.vec[l-1] = c.vec[k-1];
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
