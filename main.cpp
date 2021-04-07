#include "lib.hpp"



int main()
{
    bool continuer = true;
    int choix,choix2, depart, arrive;
    Graphe *graphe;
    graphe = new Graphe("data_arcs.txt");
    while(continuer)
    {

        std::cout << "que voulez vous faire:" << std::endl;
        std::cout << "1.Afficher Graphe" << std::endl << "2.Chemin le plus court" << std::endl << "3.chemin le plus court avec interet" << std::endl << "4.Consulter le point d'arrivee et de depart d'un trajet" << std::endl;
        std::cout << "5.Consulter les trajets qui arrivent et qui partent d'un sommet" << std::endl << "6.Optimiser le flot des pistes" << std::endl<< "7.Modifer les temps" << std::endl <<"8.Modifier les interets" << std::endl << "9.modifier les capacites" << std::endl << "10.Optimiser les capacite max " << std::endl << "11.Quitter" << std::endl;
        choix = choisir(1, 11);
        if(choix == 1)
        {
            graphe->afficher();
        }
        else if(choix == 2)
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" <<std::endl;
            choix2 = choisir(1,2);
            if(choix2 == 1)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                std::cout << "sur quel sommet voulez-vous arriver ?" << std::endl;
                arrive = choisir(1, graphe->getOrdre());
                graphe->Dijkstra(depart-1, arrive-1,false);
            }
            else if(choix2 == 2)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                graphe->Dijkstra(depart-1, 0,true);
            }
        }
        else if(choix == 3)
        {
            std::cout << "Quel est votre sommet de depart?" << std::endl;
            depart = choisir(1, graphe->getOrdre());
            std::cout << "Quel est votre sommet d'arrive?" << std::endl;
            arrive = choisir(1, graphe->getOrdre());
            graphe->DijkstraInteret(depart-1, arrive-1);
            
        } 
        else if(choix == 4)
        {
            graphe->trouverSommetsTrajet();
        }
        else if(choix == 5)
        {
            std::cout << "sur quel sommet voulez-vous regardez les trajets ?" << std::endl;
            choix2 = choisir(1, graphe->getTaille());
            graphe->trouverChemin(choix2-1);
        }
        else if(choix == 6)
        {
            std::cout << "Voulez-vous ?"<< std::endl << "1.Calculer le flot maximal en affichant les etapes de calcul?" << std::endl;
            std::cout << "2.Calculer le flot maximal sans afficher les etapes de calcul?" << std::endl ;
            std::cout << "3.Afficher le graphe d'ecart des chemin trouve?" << std::endl;
            choix2 = choisir(1,3);
            graphe->FF(choix2);
            delete graphe;
            graphe = new Graphe("data_arcs.txt");
        }
        else if(choix == 7)
        {
            graphe->fichier("data_arcs.txt", 3);
            delete graphe;
            graphe = new Graphe("data_arcs.txt");
        }
        else if(choix == 8)
        {
            graphe->fichier("data_arcs.txt", 1);
            delete graphe;
            graphe = new Graphe("data_arcs.txt");
        }
        else if(choix == 9)
        {
            graphe->fichier("data_arcs.txt", 2);
            delete graphe;
            graphe = new Graphe("data_arcs.txt");
        }
        else if(choix == 10)
        {
            graphe->OptimiserCapa();
        }
        else if(choix == 11)
        {   
            continuer = false;
        }
    }
    return 0;
}