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
        std::cout << "Bienvenue dans le programme de gestion de la station des arcs" << std::endl; //on demande a l'utilisateur si il est skieur ou si il est l'administrateur de la station M.Touchousse
        std::cout << "Etes-vous ?" << std::endl << "1. un skieur" << std::endl << "2. l'administrateur" << std::endl;
        choix = choisir(1,2); //appel de la fonction de blindage elle prend 2 paramètres, le premier est la plage inférieur, et le deuxieme est la plage supérieur il empeche les problemes liés au charactere
        if(choix == 1) //dans le cas ou l'utilisateur est un skieur
        {
            std::cout << "Bienvenue !" << std::endl << "que voulez vous faire ?" << std::endl << "1.Creer un compte" << std::endl << "2.Se connecter" << std::endl;
            choix2 = choisir(1,2); //possibilité de créer un nouveau compte ou alors de se login dans le cas ou il possede deja un compte
            if(choix2 == 1)
            {
                std::cout << "entrer un nom d'utilisateur (sans espace)" << std::endl; //on recupere son login et son mot de passe
                std::cin >> login;
                std::cout << "entrer un mot de passe" << std::endl;
                std::cin >> mdp;
                if(IsPathExist(login)) //on appelle la fonction de verification qui permettra de voir si l'utilisateur existe deja ou non
                {
                    std::cout << "erreur l'utilisateur existe deja :(" << std::endl;
                }
                else
                {
                    temp = "mkdir "; //on prepare la commande qui permettra de creer un nouvelle utilisateur
                    temp += login; //on y ajoute le nom d'utilisateur
                    system(temp.c_str()); //on envoie la commande au CMD pour creer le nouveau dossier
                    if(IsPathExist(login)) //on test de nouveau si le dossier existe pour savoir si la creation a bien pu se faire
                    {
                        std::cout << "Creation de compte reussi !" << std::endl; //on indique a l'utilisateur que son compte a bien été crée
                        std::ofstream locmdp(login + "/mdp.txt"); //on ouvre un fichier mot de passe
                        if(locmdp)
                        {
                            locmdp << sha256(mdp); //on y insere le mot de passe mis sous encryption SHA-256
                            continuer = true; //on permet a l'utilisateur de passer a l'étape suivante dans le programme
                        }
                        locmdp.close(); //on ferme le fichier
                        temp = "copy data_arcs.txt "; //finalement on prepare la commande permettant de copier les informations de base concernant la station
                        temp += login;
                        temp += "/data_arcs.txt >/dev/null"; //le >/dev/null assure que la sortie de la commande ce fera dans le vide pour eviter d'envoyer des informations inutiles a l'utilisateur
                        system(temp.c_str()); //finalement on envoie la commande
                        std::cout << "Bienvenue " << login << "!!" << std::endl;
                    }
                    else
                    {
                        std::cout << "erreur" << std::endl; //si la creation du dossier a échoué on prefere alors fermer le programme pour eviter tous problemes
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else if(choix2 == 2) //si la personne possede deja un compte elle choisit alors de se login
            {
                std::cout << "Entrer votre identifiant" << std::endl; //on lui demande alors son login et son mot de passe
                std::cin >> login;
                std::cout << "entrer votre mot de passe" << std::endl;
                std::cin >> mdp;
                if(IsPathExist(login)) //on verifie que le compte existe bien
                {
                    std::ifstream locmdp(login + "/mdp.txt"); //on ouvre alors son dossier et on va recuperer le mot de passe encrypté
                    locmdp >> temp; 
                    if(temp == sha256(mdp)) //on verifie alors que le mot de passe entré encrypté est bien égale a la string enregistré
                    {
                        std::cout << "Bienvenue "<< login <<"!" << std::endl; //dans ce cas on indique a l'utilisateur qu'il a pu se login et on lui permet d'acceder a la suite du programme
                        continuer = true;
                    }
                    else
                    {
                        std::cout << "Mauvais mot de passe" << std::endl; //on indique une erreur dans le mot de passe
                    }
                    locmdp.close();
                }
                else
                {
                    std::cout << "le compte n'existe pas !" << std::endl;
                }
            }
        }
        else if(choix == 2) //si l'utilisateur est monsieur touchousse on lui demande alors simplement le mot de passe de la station comme il est l'administrateur de la station
        {
            std::cout << "Veuillez entrer le mot de passe" << std::endl;
            std::cin >> mdp;
            if(mdp == "Touchousse") //on verifie que le mot de passe est égale a Touchousse
            {
                std::cout << "Bienvenue Mr.Touchousse !!" << std::endl; //on lui indique alors la bienvenue et on le laisse acceder a la suite du programme mettant moni sur true
                continuer = true;
                moni = true; //debloque certaines partie du programme si l'utilisateur n'est pas un skieur
            }
            else
            {
                std::cout << "Mauvais mot de passe Mr.Touchousse" << std::endl;
            }
        }
    }
    Graphe *graphe; //on creer alors le pointeur qui nous servira dura le programme
    if(moni)
    {
        localisation = "data_arcs.txt"; //on change la localisation du fichier a modifier en fonction de si il s'agit du skieur ou alors si il s'agit du mono de ski
    }
    else
    {
        localisation = login + "/data_arcs.txt"; //emplacement personnalisé en fonction du login de l'utilisateur
    }
    graphe = new Graphe(localisation); //on appelle le constructeur de graphe et on creer le graphe a partir du fichier
    while(continuer)
    {

        std::cout << "que voulez vous faire:" << std::endl; //on accede finalement au menu et on peut alors acceder au différente partie du menu
        std::cout << "1.Afficher Graphe" << std::endl << "2.Chemin le plus court (en temps de trajet)" <<std::endl << "3.chemin le plus court(en nombre d'arc)" <<std::endl << "4.chemin le plus court avec interet" << std::endl << "5.Consulter le point d'arrivee et de depart d'un trajet" << std::endl;
        std::cout << "6.Consulter les trajets qui arrivent et qui partent d'un sommet" << std::endl << "7.Explorer tous les pistes de la station" << std::endl << "8.Modifer les temps" << std::endl <<"9.Modifier les interets" << std::endl;
        if(moni == true)
        {
            std::cout << "10.modifier les capacites" << std::endl << "11.Optimiser les capacite max " << std::endl << "12.Optimiser le flot des pistes" << std::endl << "13.Quitter" << std::endl;
        }
        else //l'affichage est différent en fonction de si l'utilisateur est Mr.Touchousse ou alors si l'utilisateur est un skieur
        {
            std::cout <<"10.Quitter" << std::endl;
        }
        if(moni)
        {
            choix = choisir(1, 13); //le blindage est alors different pour eviter de pouvoir acceder a tous les choix
        }
        else
        {
            choix = choisir(1,10);
        }
        if(choix == 1)
        {
            graphe->afficher(); //permet d'afficher le graphe entier
        }
        else if(choix == 2) //permet de trouver le trajet le plus rapide entre deux point basé sur la durée, on realise l'algorithme avec le plus petit temps de trajet
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" <<std::endl << "3->arriver avant le dejeuner" << std::endl << "4->exclure une piste" << std::endl;
            choix2 = choisir(1,4);
            if(choix2 == 1) //on peut obtenir le resultat concernant un trajet en particulier
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre()); //blindage basé sur l'ordre du graphe chargé
                std::cout << "sur quel sommet voulez-vous arriver ?" << std::endl;
                arrive = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29)
                {
                    graphe->Dijkstra(depart-1, arrive-1,false); //appel de la methode de djikstra sans affichage général
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
            else if(choix2 == 2)
            {
                std::cout << "de quel sommet voulez-vous partir ?" << std::endl;
                depart = choisir(1, graphe->getOrdre()); //permet d'obtenir tous les trajet possible
                if(depart != 6 && depart != 29)
                {
                    graphe->Dijkstra(depart-1, 0,true); //permet d'appeler l'affichage general de tous les trajets possibles
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
            else if(choix2 == 3) //on peut aussi demander a l'utilisateur a quel heure il part et pour quel heure il veut arriver de tel manière a ne pas rater le dejeuner
            {
                std::cout << "les pistes sont ouvertes entre 8h00 et 17h00 entrez une horaire de depart" << std::endl;
                std::cout << "heure: ";
                heureD = choisir(8, 16); //on demande l'horaire de départ comprise entre 8 heures et 16 heures
                std::cout << "minutes: ";
                minD = choisir(0,59);
                std::cout << "A quel horaire voulez vous dejeuner ?" << std::endl;
                std::cout << "heure: ";
                heureA = choisir(8,16); //on demande l'horaire d'arrivé du skieur
                std::cout << "minutes: ";
                minA = choisir(0,59);
                std::cout << "finalement ou etes-vous ?" << std::endl;
                depart = choisir(1, graphe->getOrdre());
                if(depart != 6 && depart != 29) //on verifie que l'utilisateur ne veut pas partir du sommet 6 ou 29 car il est impossible de sortir de ces deux sommets
                {
                    if((heureA- heureD) > 0) //on verifie que l'heure d'arrivé est bien supérieur a l'heure de départ car on ne peut pas arrivé avant d'étre parti
                    {
                        graphe->Dijkstra(depart-1, 0,true, true, ((heureA - heureD) * 3600 + (minA-minD) * 60));
                    }
                    else if(heureA == heureD && (minA - minD) > 0) //dans le cas ou l'heure d'arrivé sont les memes on verifie les secondes pour verifier que la soustraction est bien supérieur a 0
                    {
                        graphe->Dijkstra(depart-1, 0,true, true, ((heureA - heureD) * 3600 + (minA-minD) * 60));
                    }
                    else
                    {
                        std::cout << "vous ne pouvez pas arrive avant de partir :/" << std::endl; //on affiche un message d'erreur si l'heure de départ et d'arrivé ne sont pas bonnes
                    }
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl; //on affiche un message dans le cas ou on ne peut pas partir
                }
            }
            else if(choix2 ==4) //finalement le dernier choix permet d'exclure un type de piste si il ne nous plait pas
            {
                std::cout << "quel type de piste voulez interdire ? (type disponible : V - B - R - N - KL - SURF - TC - TSD - TS - TK - BUS)" << std::endl;
                std::cin >> exclure; //on demande alors a l'utilisateur la piste a éxlure
                std::cout << "de quel sommet voulez vous demarer ?" << std::endl;
                depart = choisir(1, graphe->getOrdre()); //on demande alors de quel sommet doit on partir
                if(depart != 6 && depart != 29) //dans le cas ou on ne part pas de 6 ou 29 des quel on ne peut pas repartir
                {
                    graphe->Dijkstra(depart-1, 0,true, false, 0, true, exclure); //on demande alors a djikstra d'afficher tous les trajets possibles sans faire d'affichage de debbugage et en excluant une piste
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet" << std::endl;
                }
            }
        }
        else if(choix == 3) //on realise ici l'algorithme par rapport au nombre d'arc.
        {
            std::cout << " Voulez vous realiser l'algorithme : " << std::endl << "1-> en precisant le sommet d'arrive" << std::endl << "2-> ensemble des trajets possibles" << std::endl;
            choix2 = choisir(1,2); //on demande a l'utilisateur si il veut les trajets généraux ou alors si il prefere avoir un trajet entre 2 points
            if(choix2 == 1) //cas ou l'on part d'un point a l'autre
            {
                std::cout << "a partir de quel sommet voulez vous partir ?" << std::endl;
                depart = choisir(1,graphe->getOrdre()); //point de depart blindé
                std::cout << "sur quel sommet voulez vous arriver ?" << std::endl;
                arrive = choisir(1,graphe->getOrdre()); //point d'arrivé blindé
                if(depart != 6 && depart != 29)
                {
                    graphe->legacyBFS(depart-1, arrive-1, true, 1); //si le sommet est différent de 6 ou 29 on appelle l'algorithme BFS original qui pourra trouver le chemin le plus cours
                }                                                   //en nombre d'arcs
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet :/" << std::endl; //sinon on affiche une erreur a l'utilisateur
                }
            }
            else if(choix2 == 2) //si l'utilisateur choisi le cas général
            {
                std::cout << "a partir de quel sommet voulez vous partir ?" << std::endl;
                depart = choisir(1,graphe->getOrdre()); //on lui demande de quel sommet veut il partir ?
                if(depart != 6 && depart != 29)
                {
                    graphe->legacyBFS(depart-1, 0, true, 2); //on appelle alors l'algorithme BFS original en lui precisant qu'on utilisera le tableau m_tab et que l'on sera dans le cas général
                }
                else
                {
                    std::cout << "Impossible on ne peut pas partir de ce sommet :/" << std::endl;
                }
            }
        }
        else if(choix == 4) //on realise ici l'algorithme de Djikstra interet qui permettra de trouver le meilleur chemin avec le plus grand interet sans pour autant partir en boucle infini
        {
            std::cout << "Quel est votre sommet de depart?" << std::endl;
            depart = choisir(1, graphe->getOrdre()); //on demande le sommet de départ a l'utilisateur
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
            delete graphe;
        }
    }
    return 0;
}