#include <cmath>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include "projet.hpp"
#include "genetique.hpp"


double adaptation(const Chemin& c)
{
    int n = c.vec.size();
    double adapt = 0;
    vector<int> licite (n,0);
    bool res = true;
    for (int i=0; i<n-1; i++)
    {
        double a = std::numeric_limits<double>::infinity();
        if (licite[i]==1)
        {
            return a;
        }
        licite[i]=1;
        if (c.adj((c.vec[i]).indice+1, (c.vec[i+1]).indice+1)==-1)
        {
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
        //cout << "chemin numero " << i+1 <<endl;
        p[i].affiche();
        cout<<endl;
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
    bool res = false;
    int iter = 0; //on définit un nombre maximum d'itérations
    while((res==false)&(iter<1000))
    {
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
        res = ((adaptation(ij)<=std::numeric_limits<double>::infinity())&(adaptation(ji)<=std::numeric_limits<double>::infinity())); //on vérifie que l'hybridation soit licite
        iter = iter + 1;
    }
    if (iter==1000)
    {
        ij=c1;
        ji=c2;
    }
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
    double S = 0;
    vector<double> adapt; //adaptation de chaque chemin
    for (int i = 0; i<n ; i++)
    {
        double a = adaptation(p.p[i]);
        cout << adaptation(p.p[i]) << endl;
        S = S + a;
        adapt.push_back(a);
    }
    //selection
    while (taille<taille_popu)
    {
        static default_random_engine re (unsigned(time(nullptr)));
        std::uniform_real_distribution<double> unif(0,S);
        double r = unif(re);
        double somme = 0;
        int k = 0;
        while (somme<r)
        {
            somme = somme + adapt[k];
            k = k + 1;
        }
        //Chemin c = p[k];
        p_select.push_back(p[k-1]);
        taille = taille + 1;
    }
}

bool compare_pair(pair<double,int> p1, pair<double,int> p2)
{
    return (p1.first<p2.first);
}

void selection_rang(Population& p_select, Population& p, int taille_popu)
{
    //tri des individus par leur fonction adaptation

    vector<pair<double,int>> paires; //on initialise le vecteur de paires (adaptation, numero de la ville)
    int n = p.p.size();
    double S = 0;
    srand(time(NULL));

    for (int i=0; i<n; i++)
    {
        pair<double, int> paire;
        double a = adaptation(p.p[i]);
        S = S + a;
        paire.first = a ;
        paire.second = i;
        paires.push_back(paire);
    }
    sort(paires.begin(),paires.end(),compare_pair); //on trie les paires de ville en fonction de leur adaptation

    //selection
    int taille = 0;
    while (taille!=taille_popu)
    {
        int rang = rand()%n; //on genere un rang au hasard
        int somme_rang = 0;
        int compteur = 0;
        while (somme_rang<rang)
        {
            compteur = compteur + 1;
            somme_rang = somme_rang + compteur;
        };
    p_select.push_back(p.p[compteur]);
    taille = taille + 1;
    }
}

void selection_tournoi(Population& p_select, Population& p, int taille_popu)
{
    int n = p.p.size();
    vector <double> adapt;
    for (int i=0;i<n;i++)
    {
        double a = adaptation(p.p[i]);
        adapt.push_back(a);
    }
    srand(time(NULL));
    int taille = 0;
    while(taille<taille_popu)
    {
        int a = rand()%n; //on genere le premier adversaire
        int b = rand()%n; //on genere le deuxieme adversaire
        int victoire = rand()%100;
        int proba = rand()%30 + 70;
        if (adapt[a]>=adapt[b])
        {
            victoire = victoire<=proba;
        }
        if (victoire)
        {
            p_select.push_back(p.p[a]);
        } else
        {
            p_select.push_back(p.p[b]);
        }
        taille = taille + 1;
    }
}

void eugenisme(Population& p_select, Population& p, int taille_popu)
{
    int n = p.p.size();
    if (taille_popu<n)
    {
        for (int i = 0; i<taille_popu ; i++)
        {
            p_select.push_back(p.p[i]);
        }
    } else
    {
        for (int i = 0 ; i<n; i++)
        {
            p_select.push_back(p.p[i]);
        }
        srand(time(NULL));
        int taille = n;
        while (taille<taille_popu)
        {
            int a = rand()%n;
            p_select.push_back(p.p[a]);
            taille = taille + 1;
        }
    }
}


void reproduction(Population& p, Population& p_new, int taille_popu, int methode)
{
    cout << "ok1" << endl;
    Population p_tilde; //generation de la population de reproducteurs
    if (methode % 4 == 0)
    {
        cout << "ok2" << endl;
        selection_roulette(p_tilde, p, taille_popu);
    } if (methode % 4 == 1)
    {
        cout << "ok2" << endl;
        selection_rang(p_tilde, p, taille_popu);
    } if (methode % 4 == 2)
    {
        selection_tournoi(p_tilde, p, taille_popu);
    } else
    {
        eugenisme(p_tilde, p, taille_popu);
    }
    int taille = 0;
    int n = p.p.size();
    srand(time(NULL));
    while (taille<taille_popu)
    {
        cout << "ok3" << endl;
        int a = rand()%n;
        int b = rand()%n;
        Chemin c1_mute;
        Chemin c2_mute;
        //hybridation(p_tilde.p[a], p_tilde.p[b], c1, c2); on abandonne l'hybridation
        cout << "Hybridation ok" << endl;
        mutation_flip(p_tilde[a], c1_mute);
        cout << "Mutation ok" << endl;
        mutation_flip(p_tilde[b], c2_mute);
        p_new.push_back(c1_mute);
        cout << "pushback ok" << endl;
        p_new.push_back(c2_mute);
        taille = taille + 1;
    }
}

void selection_finale(Population& p_finale, Population& p_init, int taille_popu, int methode, int q, int iter)
{
    int n = p_init.p.size();
    Population pk = p_init;
    Population p_enfants;
    for (int i=0; i<iter; i++)
    {
        reproduction(pk, p_enfants, taille_popu, methode);
        if (q==0) //q = 0 seuls les enfants survivent
        {
            pk = p_enfants;
        } else
        {
            q = q % n; //au cas où q est plus grand que n
            vector<pair<double,int>> adaptation_pk;
            vector<pair<double,int>> adaptation_enfants;
            for (int i=0;i<n;i++)
            {
                double a = adaptation(pk.p[i]);
                pair<double,int> paire;
                paire.first = a;
                paire.second = i;
                adaptation_pk.push_back(paire);

                double a2 = adaptation(p_enfants.p[i]);
                pair<double,int> paire2;
                paire2.first = a2;
                paire2.second = i;
                adaptation_enfants.push_back(paire2);
            }
            sort(adaptation_pk.begin(),adaptation_pk.end(),compare_pair);
            sort(adaptation_enfants.begin(),adaptation_enfants.end(),compare_pair);
            for (int i=0;i<n;i++)
            {
                if (i<q)
                {
                    pk.push_back(pk.p[adaptation_pk[i].second]);
                } else
                {
                    pk.push_back(p_enfants.p[adaptation_enfants[i].second]);
                }
            }
        }
    }
}

//fonction pour initialiser un chemin valide. Elle prend en arguments les indices des villes de départ et  d'arrivée, la matrice d'adjacence et le vecteur contenant toute les villes dans l'ordre

//Chemin init_heur(const int I, const MatriceAdjacence& adj, const vector<Ville> & villes){
//    int n=adj.n;
//
//    vector<int> visite(n, 0);
//    vector<int> id_chemin;
//    id_chemin.push_back(I);
//    vector<Ville> v;
//
//    int a_traiter=I;
//
//    while (!visite[a_traiter]){
//        visite[a_traiter] = 1;
//        int dis=numeric_limits<int>::max();
//        int temp;
//        for (int i = 0; i < n; i++) {
//            if (adj(a_traiter+1, i+1)>=0 && adj(a_traiter+1, i+1) < dis && !visite[i]) {
//                dis=adj(a_traiter+1 ,i+1);
//                temp=i;
//            }
//        }
//        cout<<"temp : "<<temp<<endl;
//        id_chemin.push_back(temp);
//        a_traiter=temp;
//
//    }
//    for (int i : id_chemin) {
//        v.push_back(villes[i]);
//    }
//    return Chemin(adj, v);
//}

Chemin init_heur(const int I, const MatriceAdjacence& adj, const vector<Ville>& villes) {
    int n = adj.n;

    vector<int> visite(n, 0);
    vector<int> id_chemin;
    id_chemin.push_back(I);
    vector<Ville> v;

    int a_traiter = I;

    while (id_chemin.size() < n) {
        visite[a_traiter] = 1;
        int dis = numeric_limits<int>::max();
        int temp = -1;
        for (int i = 0; i < n; i++) {
            if (adj(a_traiter+1, i+1) >= 0 && adj(a_traiter+1, i+1) < dis && !visite[i]) {
                dis = adj(a_traiter+1, i+1);
                temp = i;
            }
        }
        if (temp == -1) {
            // no unvisited neighbor found, choose an unvisited city at random
            for (int i = 0; i < n; i++) {
                if (!visite[i]) {
                    temp = i;
                    break;
                }
            }
        }
        id_chemin.push_back(temp);
        a_traiter = temp;
    }
    for (int i : id_chemin) {
        v.push_back(villes[i]);
    }
    return Chemin(adj, v);
}



Population pop_init(const int& p, const MatriceAdjacence& adj, const vector<Ville> & villes){
    //if (p < adj.n){
        vector<Chemin> vp;
        for (int i=0; i<p; i++){
            vp.push_back(init_heur(i, adj, villes));
        }
    return Population(vp);
    //}
    //return Population();
}
