#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <map>

class Sommet
{
    public:
        Sommet(){};
        Sommet(int m_poids);
        Sommet(int num, int poids){m_num = num; m_poids = poids;};
        void ajouterAdjacent(Sommet* adjacent, int num, int poids, int interet, int capacite, std::string type);
        void afficher()const;
        unsigned int getSize()const{return m_adjacent.size();};
        int getNum(int num)const{return m_adjacent[num]->m_num;};
        int getNum()const{return m_num;};
        int getPoids()const{return m_poids;};
        int getPoids(int num)const{return m_tab_poids[num];};
        int getInteret(int num)const{return m_tab_interet[num];};
        int getCapa(int num)const{return m_capacite[num];};
        int getFlot(int num)const{return m_tab_flot[num];};
        int getIndice(int num)const;
        std::string getType(int num)const{return m_tab_type[num];};
        void ajouterFlot(int flot, int num);
    private:
        std::vector<Sommet*> m_adjacent;
        std::vector<int> m_tab_poids;
        std::vector<int> m_tab_interet;
        std::vector<int> m_capacite;
        std::vector<int> m_tab_flot;
        std::vector<std::string> m_tab_type;
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
        Graphe(Graphe *c, std::map<std::string, int> capacite);
        void afficher() const;
        void Dijkstra(int debut, int arrive, bool gene);
        int calculerDuree(int id1, int id2, std::string type);
        std::vector<int> BFS(int numero,int numeroArrive ,bool affichage);
        void legacyBFS(int numero,int numeroArrive, bool affichage);
        void trouverSommetsTrajet();
        void fichier(std::string nomFichier, int ligne);
        void capacite(std::string nomFichier);
        void DijkstraInteret(int debut, int arrive);
        int FF(int affichage);
        void trouverChemin(int sommet);
        void OptimiserCapa();
        int getOrdre(){return m_ordre;};
        int getTaille(){return m_taille;};   
    private:
        int m_ordre;
        int m_taille;
        std::vector<Sommet*> m_tab;
        std::vector<Sommet*> m_tab_FF;
        std::vector<Sommet*> m_tab_ecart;
        std::vector<Trajet> m_tab_trajet;
        std::vector<int> m_I_preds;
        std::map<std::string, int> m_interet;
        std::map<std::string, int> m_capacite;
        std::map<std::string, int> m_temps;
};

int choisir(int plageDebut, int plageFin);
void afficherTemps (int secondes);