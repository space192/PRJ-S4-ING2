#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

class Sommet
{
    public:
        Sommet(){};
        Sommet(int m_poids);
        Sommet(int num, int poids){m_num = num; m_poids = poids;};
        void ajouterAdjacent(Sommet* adjacent, int num, int poids);
        void afficher()const;
        unsigned int getSize()const{return m_adjacent.size();};
        int getNum(int num)const{return m_adjacent[num]->m_num;};
        int getNum()const{return m_num;};
        int getPoids()const{return m_poids;};
        int getPoids(int num)const{return m_tab_poids[num];};
        int getIndice(int num)const;

    private:
        std::vector<Sommet*> m_adjacent;
        std::vector<int> m_tab_poids;
        int m_num;
        int m_poids;
};

class Trajet
{
    public:
        Trajet(Sommet* id1, Sommet* id2, int poids);
        Trajet(){};
        void afficher()const;
        int getPoids()const{return m_poids;};
        int getSommet(int num)const{return m_tab_adj[num]->getNum();};
    private:
        int m_poids;
        Sommet* m_tab_adj[2];
};

class Graphe
{
    public:
        Graphe(std::string nomFichier);
        void afficher() const;
        void Dijkstra(int debut, int arrive);
        int calculerDuree(int id1, int id2, std::string type);
    private:
        int m_ordre;
        int m_taille;
        std::vector<Sommet*> m_tab;
        std::vector<Trajet> m_tab_trajet;
};