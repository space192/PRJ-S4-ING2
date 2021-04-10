#ifndef LIB_HPP_INCLUDED
#define LIB_HPP_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <cstring>
#include <sys/stat.h>

//fonction de hashage SHA 256 reucpere du site http://www.zedwood.com/article/cpp-sha256-function#:~:text=SHA%2D256%20is%20the%20most,1%20provides%20only%2080%20bits).


class Sommet
{
    public:
        Sommet(){}; //constructeur par defaut
        Sommet(int m_poids); //constructeur surchargé
        Sommet(int num, int poids){m_num = num; m_poids = poids;}; //constructeur Pincipal
        void ajouterAdjacent(Sommet* adjacent, int num, int poids, int interet, int capacite, std::string type); //permet d'ajouter des adjacents a un sommet
        void afficher()const; //methode d'affichage pour les sommets
        unsigned int getSize()const{return m_adjacent.size();};
        int getNum(int num)const{return m_adjacent[num]->m_num;};
        int getNum()const{return m_num;};
        int getPoids()const{return m_poids;};
        int getPoids(int num)const{return m_tab_poids[num];};                   //differents getter et setter utilisé
        int getInteret(int num)const{return m_tab_interet[num];};
        int getCapa(int num)const{return m_capacite[num];};
        int getFlot(int num)const{return m_tab_flot[num];};
        int getIndice(int num)const;
        std::string getType(int num)const{return m_tab_type[num];};
        void ajouterFlot(int flot, int num); //permet d'ajouter du flot au different trajet
    private:
        std::vector<Sommet*> m_adjacent; //different vecteur synchronisé utilisé pour les algos
        std::vector<int> m_tab_poids;
        std::vector<int> m_tab_interet;
        std::vector<int> m_capacite;
        std::vector<int> m_tab_flot;
        std::vector<std::string> m_tab_type; //contient le type de chaque trajet pour l'exclusion
        int m_num;
        int m_poids;
};

class Trajet
{
    public:
        Trajet(Sommet* id1, Sommet* id2, int poids, int interet); //constructeur surchagé principal
        Trajet(){}; //constructeur par défaut
        void afficher()const; //methode qui permet d'afficher les trajet
        int getPoids()const{return m_poids;}; //different getter
        int getInteret()const{return m_interet;};
        int getSommet(int num)const{return m_tab_adj[num]->getNum();};
    private:
        int m_poids;
        int m_interet;
        Sommet* m_tab_adj[2];
};

class Graphe
{
    public:
        Graphe(std::string nomFichier); //constructeur par défaut
        Graphe(Graphe *c, std::map<std::string, int> capacite); //constructeur par copie
        void afficher() const; //methode permettant d'afficher le graphe
        void Dijkstra(int debut, int arrive, bool gene, bool horaire = false, int temps = 0, bool exclu = false, std::string type = "");
        //algorithme de Djikstra avec des paramètres par défaut permettant de changer la sortie final
        int calculerDuree(int id1, int id2, std::string type); //calcul la durée du trajet entre 2 sommets
        std::vector<int> BFS(int numero,int numeroArrive ,bool affichage); //BFS utilisé pour Ford Fulkerson permettant de recuperer le chemin utilisé
        void legacyBFS(int numero,int numeroArrive, bool affichage, int tabgene = 0); //BFS original permettant de trouver le chemin le plus rapide en nombre d'arcs
        void trouverSommetsTrajet();
        void fichier(std::string nomFichier, int ligne, bool moni=true); //permet de moidifer le fichier afin d'y ajouter de nouvelles informations
        void DijkstraInteret(int debut, int arrive); //version de djikstra avec interet qui va changer de trajectoire en fonction des interets marqués dans le fichier
        int FF(int affichage); //Algorithme de Ford Fukerson pour trouver le flot
        void trouverChemin(int sommet); //trouve tous les chemins menant a un sommet
        void OptimiserCapa(); //optimise la capacité de chacun des trajets pour optimiser le flot
        void Kruskal(int choix, bool affichage = false);
        int getOrdre(){return m_ordre;}; //getter de la classe graphe
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

int choisir(int plageDebut, int plageFin); //fonction permettant de blinder la saisie de l'utilisateur pour eviter tous problemes
void afficherTemps (int secondes); //permet d'afficher le temps en le convertissant de seconde a heure et minutes
bool IsPathExist(const std::string &s); //https://www.systutorials.com/how-to-test-a-file-or-directory-exists-in-c/

#endif
