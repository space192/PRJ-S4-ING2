#include "lib.hpp"

int main()
{
    bool continuer = true;
    int choix,choix2, depart, arrive;
    Graphe graphe("data_arcs.txt");
    while(continuer)
    {
        std::cout << "Bienvenue dans le TP 3" << std::endl;
        std::cout << "que voulez vous faire:" << std::endl;
        std::cout << "1.Algorithme de Dijkstra" << std::endl << "2.Afficher Graphe" << std::endl << "3.Consulter le point d'arrivee et de depart d'un trajet" << std::endl << "4.Consulter les trajets qui arrivent et qui partent d'un sommet" << std::endl << "5.BFS" << std::endl <<"6.Interet" << std::endl <<"7.Quitter" << std::endl;
        std::cin >> choix;
        if(choix == 1)
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" <<std::endl;
            std::cin >> choix2;
            if(choix2 == 1)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                std::cin >> depart;
                std::cout << "sur quel sommet voulez-vous arriver ?" << std::endl;
                std::cin >> arrive;
                graphe.Dijkstra(depart-1, arrive-1,false);
            }
            else if(choix2 == 2)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                std::cin >> depart;
                graphe.Dijkstra(depart-1, 0,true);
            }
            
            
        }
        else if(choix == 2)
        {
            graphe.afficher();
        }
        else if(choix == 3)
        {
            graphe.trouverSommetsTrajet();
        } 
        else if(choix == 4)
        {
            
        }
        else if(choix == 5)
        {
            std::cout << "entrer un point de depart" << std::endl;
            std::cin >> choix2;
            graphe.BFS(choix2-1, true);
        }
        else if(choix == 6)
        {
            graphe.Interet("data_arcs.txt");
        }
        else if(choix == 7)
        {
            continuer = false;
        }
    }
}