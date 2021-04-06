#include "lib.hpp"

int main()
{
    bool continuer = true;
    int choix,choix2, depart, arrive;
    Graphe graphe("data_arcs.txt");
    while(continuer)
    {

        std::cout << "que voulez vous faire:" << std::endl;
        std::cout << "1.Algorithme de Dijkstra" << std::endl << "2.Afficher Graphe" << std::endl << "3.Consulter le point d'arrivee et de depart d'un trajet" << std::endl << "4.Consulter les trajets qui arrivent et qui partent d'un sommet" << std::endl << "5.Djikstra avec interet" << std::endl <<"6.Interet" << std::endl << "7.Capacite" << std::endl << "8.Quitter" << std::endl;
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
            graphe.afficherSpecial();
        }
        else if(choix == 5)
        {
            std::cout << "Quel est votre sommet de depart?" << std::endl;
            std::cin >> depart;
            std::cout << "Quel est votre sommet d'arrive?" << std::endl;
            std::cin >> arrive;
            graphe.DijkstraInteret(depart-1, arrive-1);
        }
        else if(choix == 6)
        {
            graphe.fichier("data_arcs.txt", 1);
        }
        else if(choix == 7)
        {
            graphe.fichier("data_arcs.txt", 2);
        }
        else if(choix == 8)
        {
            continuer = false;
        }
        
    }
}