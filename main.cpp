#include "lib.hpp"

int main()
{
    bool continuer = true;
    int choix, depart, arrive;
    Graphe graphe("data_arcs.txt");
    while(continuer)
    {
        std::cout << "Bienvenue dans le TP 3" << std::endl;
        std::cout << "que voulez vous faire:" << std::endl;
        std::cout << "1.Algorithme de Dijkstra" << std::endl << "2.Afficher Graphe" <<std::endl <<"3.Quitter" << std::endl;
        std::cin >> choix;
        if(choix == 1)
        {
            std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
            std::cin >> depart;
            std::cout << "sur quel sommet voulez-vous arriver ?" << std::endl;
            std::cin >> arrive;
            graphe.Dijkstra(depart-1, arrive-1);
        }
        else if(choix == 2)
        {
            graphe.afficher();
        }
        else if(choix == 3)
        {
            continuer = false;
        }
    }
}