#include "lib.hpp"
#include "sha256.hpp"

int main()
{
    bool continuer = false;
    int choix,choix2,choix3, depart, arrive;
    int heureD, heureA, minD, minA;
    bool moni = false;
    std::string exclure, mdp,login,temp, localisation;
    while(!continuer) //premiere partie du programme permettant de gerer si il s'agit du compte admin ou le compte d'un skieur
    {
        std::cout << "Bienvenue dans le programme de gestion de la station des arcs" << std::endl;
        std::cout << "Etes-vous ?" << std::endl << "1. un skieur" << std::endl << "2. l'administrateur" << std::endl;
        choix = choisir(1,2);
        if(choix == 1)
        {
            std::cout << "Bienvenue !" << std::endl << "que voulez vous faire ?" << std::endl << "1.Creer un compte" << std::endl << "2.Se connecter" << std::endl;
            choix2 = choisir(1,2);
            if(choix2 == 1)
            {
                std::cout << "entrer un nom d'utilisateur (sans espace)" << std::endl;
                std::getline(std::cin, login);
                std::cout << "entrer un mot de passe" << std::endl;
                std::getline(std::cin, mdp);
                if(IsPathExist(login))
                {
                    std::cout << "erreur l'utilisateur existe deja :(" << std::endl;
                }
                else
                {
                    temp = "mkdir ";
                    temp += login;
                    system(temp.c_str());
                    if(IsPathExist(login))
                    {
                        std::cout << "Dossier cree" << std::endl;
                        std::ofstream locmdp(login + "/mdp.txt");
                        if(locmdp)
                        {
                            locmdp << sha256(mdp);
                            continuer = true;
                        }
                        locmdp.close();
                        temp = "copy data_arcs.txt ";
                        temp += login;
                        temp += "/data_arcs.txt >/dev/null";
                        system(temp.c_str());
                    }
                    else
                    {
                        std::cout << "erreur" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else if(choix2 == 2)
            {
                std::cout << "Entrer votre identifiant" << std::endl;
                std::cin >> login;
                std::cout << "entrer votre mot de passe" << std::endl;
                std::cin >> mdp;
                std::ifstream locmdp(login + "/mdp.txt");
                locmdp >> temp;
                if(temp == sha256(mdp))
                {
                    std::cout << "Bienvenue !" << std::endl;
                    continuer = true;
                }
                else
                {
                    std::cout << "Mauvais mot de passe" << std::endl;
                }
                locmdp.close();
            }
        }
        else if(choix == 2)
        {
            std::cout << "Veuillez entrer le mot de passe" << std::endl;
            std::cin >> mdp;
            if(mdp == "Touchousse")
            {
                std::cout << "Bienvenue Mr.Touchousse !!" << std::endl;
                continuer = true;
                moni = true;
            }
            else
            {
                std::cout << "Mauvais mot de passe Mr.Touchousse" << std::endl;
            }
        }
    }
    Graphe *graphe;
    if(moni)
    {
        localisation = "data_arcs.txt";
    }
    else
    {
        localisation = login + "/data_arcs.txt";
    }
    graphe = new Graphe(localisation);
    while(continuer)
    {

        std::cout << "que voulez vous faire:" << std::endl;
        std::cout << "1.Afficher Graphe" << std::endl << "2.Chemin le plus court (en temps de trajet)" <<std::endl << "3.chemin le plus court(en nombre d'arc)" <<std::endl << "4.chemin le plus court avec interet" << std::endl << "5.Consulter le point d'arrivee et de depart d'un trajet" << std::endl;
        std::cout << "6.Consulter les trajets qui arrivent et qui partent d'un sommet" << std::endl << "7.Explorer tous les pistes de la station" << std::endl << "8.Modifer les temps" << std::endl <<"9.Modifier les interets" << std::endl;
        if(moni == true)
        {
            std::cout << "10.modifier les capacites" << std::endl << "11.Optimiser les capacite max " << std::endl << "12.Optimiser le flot des pistes" << std::endl << "13.Quitter" << std::endl;
        }
        else
        {
            std::cout <<"10.Quitter" << std::endl;
        }
        if(moni)
        {
            choix = choisir(1, 13);
        }
        else
        {
            choix = choisir(1,10);
        }
        if(choix == 1)
        {
            graphe->afficher();
        }
        else if(choix == 2)
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" <<std::endl << "3->arriver avant le dejeuner" << std::endl << "4->exclure une piste" << std::endl;
            choix2 = choisir(1,4);
            if(choix2 == 1)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                std::cout << "sur quel sommet voulez-vous arriver ?" << std::endl;
                arrive = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->Dijkstra(depart-1, arrive-1,false);
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
            else if(choix2 == 2)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->Dijkstra(depart-1, 0,true);
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
            else if(choix2 == 3)
            {
                std::cout << "les pistes sont ouvertes entre 8h00 et 17h00 entrez une horaire de depart" << std::endl;
                std::cout << "heure: ";
                heureD = choisir(8, 16);
                std::cout << "minutes: ";
                minD = choisir(0,59);
                std::cout << "A quel horaire voulez vous dejeuner ?" << std::endl;
                std::cout << "heure: ";
                heureA = choisir(8,16);
                std::cout << "minutes: ";
                minA = choisir(0,59);
                std::cout << "finalement ou etes-vous ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    if((heureA- heureD) > 0)
                    {
                        graphe->Dijkstra(depart-1, 0,true, true, ((heureA - heureD) * 3600 + (minA-minD) * 60));
                    }
                    else if(heureA == heureD && (minA - minD) > 0)
                    {
                        graphe->Dijkstra(depart-1, 0,true, true, ((heureA - heureD) * 3600 + (minA-minD) * 60));
                    }
                    else
                    {
                        std::cout << "vous ne pouvez pas arrive avant de partir :/" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
            else if(choix2 ==4)
            {
                std::cout << "quel type de piste voulez interdire ? (type disponible : V - B - R - N - KL - SURF - TC - TSD - TS - TK - BUS)" << std::endl;
                std::cin >> exclure;
                std::cout << "de quel sommet voulez vous demarer ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->Dijkstra(depart-1, 0,true, false, 0, true, exclure);
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
        }
        else if(choix == 3)
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" << std::endl;
            choix2 = choisir(1,2);
            if(choix2 == 1)
            {
                std::cout << "a partir de quel sommet voulez vous partir ?" << std::endl;
                depart = choisir(1,graphe->getOrdre());
                std::cout << "sur quel sommet voulez vous arriver ?" << std::endl;
                arrive = choisir(1,graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->legacyBFS(depart-1, arrive-1, true, 1);
                }
                else
                {
                    std::cout << "Impossible one peut pas partir de ce sommet :/" << std::endl;
                }
            }
            else if(choix2 == 2)
            {
                std::cout << "a partir de quel sommet voulez vous partir ?" << std::endl;
                depart = choisir(1,graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->legacyBFS(depart-1, 0, true, 2);
                }
            }
        }
        else if(choix == 4)
        {
            std::cout << "Quel est votre sommet de depart?" << std::endl;
            depart = choisir(1, graphe->getOrdre());
            std::cout << "Quel est votre sommet d'arrive?" << std::endl;
            arrive = choisir(1, graphe->getOrdre());
            if(depart != 6 && depart != 29)
            {
                graphe->DijkstraInteret(depart-1, arrive-1);
            }
            else
            {
                std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
            }
            
        } 
        else if(choix == 5)
        {
            graphe->trouverSommetsTrajet();
        }
        else if(choix == 6)
        {
            std::cout << "sur quel sommet voulez-vous regardez les trajets ?" << std::endl;
            choix2 = choisir(1, graphe->getTaille());
            graphe->trouverChemin(choix2-1);
        }
        else if(choix == 7)
        {
            std::cout << "Voulez vous les explorer pour obtenir:  " << std::endl << "1.Un temps minimum" << std::endl << "2.Un interet maximum" << std::endl;
            choix2 = choisir(1,2);
            std::cout << "Voullez vous afficher les etapes de resolution de l'algoritme de Kruskal?" << std::endl;
            std::cout << "1.OUI" << std::endl;
            std::cout << "2.NON" << std::endl;
            choix3 = choisir(1,2);
            if(choix3 == 1)
            {
                graphe->Kruskal(choix2, true);
            }
            else if(choix3 == 2)
            {
                graphe->Kruskal(choix2);
            }

        }
        else if(choix == 8)
        {
            if(moni)
            {
                graphe->fichier(localisation, 3);
                delete graphe;
                graphe = new Graphe(localisation);
            }
            else
            {
                graphe->fichier(localisation, 3, false);
                delete graphe;
                graphe = new Graphe(localisation);
            }
        }
        else if(choix == 9)
        {
            graphe->fichier(localisation, 1);
            delete graphe;
            graphe = new Graphe(localisation);
        }
        else if(choix == 10 && moni)
        {
            graphe->fichier(localisation, 2);
            delete graphe;
            graphe = new Graphe(localisation);
        }
        else if(choix == 11)
        {
            graphe->OptimiserCapa();
        }
        else if(choix == 12)
        {
            std::cout << "Voulez-vous ?"<< std::endl << "1.Calculer le flot maximal en affichant les etapes de calcul?" << std::endl;
            std::cout << "2.Calculer le flot maximal sans afficher les etapes de calcul?" << std::endl ;
            std::cout << "3.Afficher le graphe d'ecart des chemin trouve?" << std::endl;
            choix2 = choisir(1,3);
            graphe->FF(choix2);
            delete graphe;
            graphe = new Graphe(localisation);
        }
        else if(choix == 13 || (!moni && choix == 10))
        {   
            continuer = false;
        }
    }
    return 0;
}