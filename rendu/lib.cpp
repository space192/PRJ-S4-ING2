#include "lib.hpp"

Graphe::Graphe(std::string nomFichier)
{
    std::string poubelle;
    std::string type;
    int num,poids, id1,id2, temp;
    std::ifstream fichier(nomFichier); //on ouvre le fichier
    if(!fichier) //on verifie que le fichier est bien ouvert et dans le cas contraire on envoie une erreur sur l'écran et on quitte
    {
        std::cout << "erreur lors de l'ouverture du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i = 0 ; i < 12 ;i++) //on recupere dans un premier temps les durée de chacun des trajets et on met les infos inutiles dans la poubelle
        {
            fichier >> poubelle;
            fichier >> m_temps[poubelle];
        }
        for(int i =0 ; i < 12; i++)//on recupere ensuite l'interet de chacun des trajets
        {
            fichier >> poubelle;
            fichier >> m_interet[poubelle];
        }
        for(int i =0 ; i < 12 ;i++)//on recupere finalement la capacite pour les types de trajet
        {
            fichier >> poubelle;
            fichier >> m_capacite[poubelle];
        }
        fichier >> m_ordre; //on recupere l'ordre pour ensuite pour trouver
        for(int i = 0 ; i < m_ordre;i++)
        {
            fichier >> num; //on recupere le numero du sommet
            fichier >> poubelle; //on jette le nom du sommet a la poubelle
            fichier >> poids; //on recupere le poids
            m_tab.push_back(new Sommet(num-1, poids)); //on ajoute le nouveau sommet et on lui donne son numero et son poids
            m_tab_FF.push_back(new Sommet(num-1, poids)); //on ajoute le nouveau sommet au tableau pour utilisation dans l'algorithme de Ford Lukerson
        }
        fichier >> m_taille;
        for(int i = 0 ; i < m_taille;i++)
        {
            fichier >> poubelle; //on met les différentes informations a la poubelle car elle ne nous seront pas utile
            fichier >> poubelle;
            fichier >> type;//on recupere le type de trajet
            fichier >> id1;//le point de depart
            fichier >> id2;//le point d'arrive
            id1 = id1-1; //on fait en sort que les sommet ai pour indice de depart 0
            id2 = id2-1;
            temp = calculerDuree(id1, id2, type); //on calcul la durée a partir du type
            m_tab[id1]->ajouterAdjacent(m_tab[id2], id1, temp, m_interet[type], m_capacite[type], type); //on ajoute l'adjacent dans le tableau de base
            m_tab_FF[id1]->ajouterAdjacent(m_tab[id2], id1, temp, m_interet[type], m_capacite[type], type); //on ajoute les sommets dans le sens direct et indirect pour utilisation
            m_tab_FF[id2]->ajouterAdjacent(m_tab[id1], id2, -temp, m_interet[type], -m_capacite[type], type);//dans Ford Fulkerson
            m_tab_trajet.push_back(Trajet(m_tab[id1], m_tab[id2], temp, m_interet[type]));//on ajoute le trajet dans le tableau de trajet afin de pouvoir les visualier plus tard
        }
        for(int i = 0 ; i < m_ordre+2;i++)
        {
            m_I_preds.push_back(-1); //on creer le tableau de prédecesseur nous servant pour tous les algorithmes
        }
    }
    fichier.close(); //on referme le fichier
}

Graphe::Graphe(Graphe *c, std::map<std::string, int> capacite) //constructeur par copie créee pour permettre l'optimisation des flots
{
    m_ordre = c->m_ordre; //on copie l'ordre et la taille
    m_taille = c->m_taille;
    for(unsigned int i = 0 ; i < c->m_tab_FF.size();i++) //on recreer tous les sommets
    {
        m_tab_FF.push_back(new Sommet(c->m_tab_FF[i]->getNum(), c->m_tab_FF[i]->getPoids()));
    }
    for(unsigned int i = 0 ; i < c->m_tab_FF.size();i++)
    {
        for(unsigned int j = 0 ; j < c->m_tab_FF[i]->getSize();j++) //on copie tous les adjacents afin de faire tourner l'algorithme de Ford Fulkerson sur ce tableau copié
        {
            if(c->m_tab_FF[i]->getCapa(j) > 0)
            {
                m_tab_FF[c->m_tab_FF[i]->getNum()]->ajouterAdjacent(m_tab_FF[c->m_tab_FF[i]->getNum(j)], c->m_tab_FF[i]->getNum(), c->m_tab_FF[i]->getPoids(j), c->m_tab_FF[i]->getInteret(j), capacite[c->m_tab_FF[i]->getType(j)], c->m_tab_FF[i]->getType(j));
            }
            else if(c->m_tab_FF[i]->getCapa(j) < 0)
            {
                m_tab_FF[c->m_tab_FF[i]->getNum()]->ajouterAdjacent(m_tab_FF[c->m_tab_FF[i]->getNum(j)], c->m_tab_FF[i]->getNum(), c->m_tab_FF[i]->getPoids(j), c->m_tab_FF[i]->getInteret(j), -capacite[c->m_tab_FF[i]->getType(j)], c->m_tab_FF[i]->getType(j));
            }
        }
    }
}

void Graphe::fichier(std::string nomFichier, int choix, bool moni)
{
    std::string tempstring, poubelle, temptype;
    std::string temptab[12];
    std::map<std::string, std::string> typeNom;
    typeNom["V"] = "Piste Verte";
    typeNom["B"] = "Piste Bleue";
    typeNom["R"] = "Piste Rouge";
    typeNom["N"] = "Piste Noir";
    typeNom["KL"] = "Piste kilometre lance";
    typeNom["SURF"] = "SnowPark";
    typeNom["TPH"] = "Telepherique"; //permet un affichage plus user friendly pour l'administrateur
    typeNom["TC"] = "Telecabine";
    typeNom["TSD"] = "Telesiege debrayable";
    typeNom["TS"] = "Telesiege";
    typeNom["TK"] = "Teleski";
    typeNom["BUS"] = "Navettes";
    int tempInt[12], temptaille, tempid, tempoids , tempdepart,temparrive;
    std::string type[12] = {"V", "B", "R", "N", "KL", "SURF", "TPH", "TC", "TSD", "TS", "TK", "BUS"};
    std::fstream fichier(nomFichier, std::ios::in | std::ios::out); //ouvre le fichier en lecture en lecture et en écriture en meme temps
    if(!fichier) //si l'ouverture ne fonctionne pas on arrete le programme
    {
        std::cout << "erreur lors de l'ouverture du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Bienvenue dans la customisation des"; //en fonction de la customisation on change l'interface
        if(choix == 1)
        {
            std::cout << "interet";
        }
        else if(choix == 2)
        {
            std::cout << "capacite";
        }
        else if(choix == 3)
        {
            std::cout << "temps";
        }
        std::cout << std::endl << "pour chaque type de déplacement vous devrez rentrez un";
        if(choix == 1)
        {
            std::cout <<  "interet";
        }
        else if(choix == 2)
        {
            std::cout << "capacite";
        }
        else if(choix == 3)
        {
            std::cout << "temps";
        }
        std::cout << std::endl;
        std::cout << "entrer pour la piste:" << std::endl;
        if(moni)
        {
            for(int i = 0 ; i < 12;i++) //on sait que l'utilisateur doit rentrer un certains nombre de piste
            {
                std::cout << typeNom[type[i]] << ": ";
                tempInt[i] = choisir(-1000000, 100000); //on blinde la saisie pour eviter que l'utilisateur ne rentre un caractere
            }
        }
        else
        {
            for(int i = 0 ; i < 6 ; i++)
            {
                std::cout << typeNom[type[i]] << ": ";
                tempInt[i] = choisir(-1000000, 100000);
            }
        }
        std::cout << "Interet enregistrer !" << std::endl; //on enregistre tous les informations
        std::ofstream temp("temp.txt"); //on creer un fichier temporaire pour faire le travail
        if(!temp) //on verifie que la creation de ce fichier temporaire a bien fonctionné
        {
            std::cout << "erreur lors de la creation du fichier temporaire" << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            fichier.seekg(0); //on rewind le fichier
            if(choix == 1) //interet
            {
                for(int i = 0 ; i < 12; i++) //on commence par recuperer le temps dans le fichier original
                {
                    fichier >> poubelle; //on le met dans la poubelle qui est en realité le string temporaire
                    temp << poubelle << " "; //on l'écrit dans le nouveau fichier
                    fichier >> poubelle; //on recupere l'information suivante
                    temp << poubelle << std::endl; //finalement on ecrit la deuxieme information et on retourne a la ligne
                }
                for(int i = 0; i < 12; i++) //on rentre maintenant les interets qui vont reellement nous interesser
                {
                    temp << type[i] << " " << tempInt[i] << std::endl; // on rentre le type (string associé avec une map)
                    fichier >> poubelle; //et ensuite on deplace le curseur dans le fichier en mettant a la poubelle les anciennes informations
                    fichier >> poubelle;
                }
                for(int i = 0 ; i < 12; i++)
                {
                    fichier >> poubelle; //on fait ensuite la copie de la capacité
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle << std::endl;
                }
            }
            else if(choix == 2) //capacite
            {
                for(int i = 0 ; i < 24; i++) //on copie le temps et l'interet
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle <<std::endl;
                }
                for(int i = 0; i < 12; i++)
                {
                    temp << type[i] << " " << tempInt[i] << std::endl; //on ecrie les nouvelles valeurs de capacité
                    fichier >> poubelle;
                    fichier >> poubelle;
                }
            }
            else if(choix == 3) //temps
            {
                if(moni)
                {
                    for(int i = 0; i < 12; i++) //on écrit les nouvelles valeurs de temps utilisé pour le programme
                    {
                        temp << type[i] << " " << tempInt[i] << std::endl;
                        fichier >> poubelle;
                        fichier >> poubelle;
                    }
                }
                else
                {
                    for(int i = 0; i < 6; i++) //on écrit les nouvelles valeurs de temps utilisé pour le programme
                    {
                        temp << type[i] << " " << tempInt[i] << std::endl;
                        fichier >> poubelle;
                        fichier >> poubelle;
                    }
                    for(int i = 0 ; i < 6 ; i++)
                    {
                        fichier >> poubelle;
                        temp << poubelle << " ";
                        fichier >> poubelle;
                        temp << poubelle << std::endl;
                    }
                }
                for(int i = 0 ; i < 24; i++) //on réecrie les valeurs pour l'interet et la capacité
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle <<std::endl;
                }
            }
            fichier >> temptaille; //il recupere ensuite l'ordre du fichier original
            temp << temptaille << std::endl;//puis il l'écrit dans le nouveau fichier
            for(int i = 0 ; i < temptaille; i++) //on réecrit ensuite les informations sans rien changer pour permettre de remettre les trajets
            {
                fichier >> tempid;
                fichier >> poubelle;
                fichier >> tempoids;
                temp << tempid << " " << poubelle << " " <<tempoids << std::endl;
            }
            fichier >> temptaille; //on recupere ensuite la taille en nombre d'arrete
            temp << temptaille << std::endl; //on l'écrit dans le fichier
            for(int i = 0 ; i < temptaille;i++)
            {
                fichier >> tempid;
                fichier >> poubelle;
                fichier >> temptype;
                fichier >> tempdepart;
                fichier >> temparrive;
                temp << tempid << " " << poubelle << " " << temptype << " " << tempdepart << " " << temparrive << std::endl;
            }

        }
        temp.close(); //finalement on ferme les deux fichiers
        fichier.close();
        std::remove(nomFichier.c_str()); //on utilise deux méthodes standards pour supprimer l'ancien fichier et renommé le nouveau pour changer les données
        std::rename("temp.txt", nomFichier.c_str());
    }
}
void Sommet::ajouterAdjacent(Sommet* adjacent, int num, int poids, int interet, int capacite, std::string type) //methode qui ajoute un adjacent de maniere a respecter l'encapsulation
{
    m_adjacent.push_back(adjacent); //permet d'ajouter les sommets de manière synchronisés
    m_tab_poids.push_back(poids); //on utilise alors un seul indice pour parcourir tous les données des adjacents plutot que de devoir en utiliser plus
    m_tab_interet.push_back(interet);
    m_capacite.push_back(capacite);
    m_tab_flot.push_back(0);
    m_tab_type.push_back(type);
    m_num = num;
}

void Sommet::ajouterFlot(int flot, int num)
{
    m_tab_flot[num] += flot; //ajoute le flot au flot actuel pour l'utilisation dans Ford Fulkerson
}

int Sommet::getIndice(int num)const
{
    int temp;
    for(unsigned int i = 0;i < m_adjacent.size();i++) //recupere l'indice dans les tableau d'adjacent
    {
        if(num == m_adjacent[i]->m_num)
        {
            temp = i;
        }
    }
    return temp;
}

void Graphe::afficher()const //permet d'afficher les informations du graphe en explicant toutes le données
{
    std::cout << "Ordre du graphe = " << m_ordre << std::endl;
    std::cout << "Sommet X : numero adjacent - duree - interet - capacite - flot" << std::endl;
    for(unsigned int i = 0 ; i < m_tab.size() ; i++)
    {
        std::cout << "sommet " << i+1 << " : ";
        m_tab[i]->afficher(); //appele la méthode afficher des sommets permettant d'afficher les informations des adjacents
        std::cout << std::endl;
    }
}

void Sommet::afficher()const
{
    for(unsigned int i = 0 ; i < m_adjacent.size(); i++) //methode d'affichage des adjacents afin de respecter l'encapsulation
    {
        std::cout << m_adjacent[i]->m_num+1 << "  " << m_tab_poids[i]; //affiche dans un premier temps le numero du sommet et sont poids
        std::cout << "  "<< m_tab_interet[i]; //puis il affiche l'interet des sommets en utilisant le meme indice
        std::cout << "  " << m_capacite[i]; //on affiche ensuite la capacité de ce trajet
        std::cout << "  " << m_tab_flot[i]; //on affiche sont flot actuel
        if(i != m_adjacent.size()-1) //et finalement si on ne se trouve pas sur le dernier adjacent on affiche un "//" pour separer les adjacents
        {
            std::cout << " // ";
        }
    }
}
Trajet::Trajet(Sommet* id1, Sommet* id2, int poids, int interet) //constructeur de trajet prenant deux sommet* en parametre pour eviter la copie ainsi que le poids de ce trajet
{
    m_tab_adj[0] = id1;
    m_tab_adj[1] = id2;
    m_poids = poids;
    m_interet = interet;
}

void Trajet::afficher()const
{
    std::cout << "depart: " << m_tab_adj[0]->getNum() << " arrive: " << m_tab_adj[1]->getNum() << " poids du trajet: " << m_poids << " interet du trajet " << m_interet <<std::endl;
    //affiche les differents informations d'un trajet a l'aide des méthodes des Sommets
}

int Graphe::calculerDuree(int id1, int id2, std::string type)
{
    int altitude1 = m_tab[id1]->getPoids(); //recupere le poids d'un sommet (son altitude dans le cas présent)
    int altitude2 = m_tab[id2]->getPoids();
    int denivele = altitude2 - altitude1; //calcule le denivele grace a ces informations
    int duree;
    if(denivele < 0) //si le dénivelé est négatif on l'inverse pour pouvoir s'en servir dans nos calculs
    {
        denivele = -denivele;
    }
    if(type == "V") //on fait attention au type du trajet et on accede ensuite a notre map, les données sont stockés en seconde dans le fichier pour nous simplifier la vie
    {
        duree = (m_temps["V"]*denivele)/100;
    }
    else if(type == "B")
    {
        duree = (m_temps["B"]*denivele)/100;
    }
    else if(type == "R")
    {
        duree = (m_temps["R"]*denivele)/100;
    }
    else if(type == "N")
    {
        duree = (m_temps["N"]*denivele)/100;
    }
    else if(type == "KL")
    {
        duree = (m_temps["KL"]*denivele)/100;
    }
    else if(type == "SURF")
    {
        duree = (m_temps["SURF"]*denivele)/100;
    }
    else if(type == "TPH")
    {
        duree = 240 + (m_temps["TPH"]*denivele)/100;
    }
    else if(type == "TC")
    {
        duree = 120 + (m_temps["TC"]*denivele)/100;
    }
    else if(type == "TSD")
    {
        duree = 60 + (m_temps["TSD"]*denivele)/100;
    }
    else if(type == "TS")
    {
        duree = 60 + (m_temps["TS"]*denivele)/100;
    }
    else if(type == "TK")
    {
        duree = 60 + (m_temps["TK"]*denivele)/100;
    }
    else if(type == "BUS")
    {
        if((id1 == 6 && id2 == 29)||(id1 == 29 && id2 == 6))
        {
            duree = 600 + m_temps["BUS"];
        }
        else if((id1 == 29 && id2 == 35)||(id1 == 35 && id2 == 29))
        {
            duree = m_temps["BUS"];
        }
    }
    return duree; //on retourne la durée du trajet qui nous permettra de creer les durées des trajets
}
void Graphe::trouverSommetsTrajet()//On cherche les sommets de départ et d'arriver d'un trajet
{
    int choix;
    std::cout << "Quel est le numero du trajet dont vous voullez observer le point de depart et le point d'arrive?" <<std::endl;
    choix = choisir(1, m_tab_trajet.size());//saisi blindé du choix du trajet
    std::cout << "Le trajet numero " << choix << " part du sommet " << m_tab_trajet[choix-1].getSommet(0) + 1 << " et arrive au sommet " << m_tab_trajet[choix-1].getSommet(1) + 1 << std::endl;
}


int choisir(int plageDebut, int plageFin)
{
    int resultat;
    bool erreur = false;
    do
    {
        if(erreur == true) //boucle de blindage qui permet de verifier que la valeur rentré est bien comprise dans la demande de l'utilisateur
        {
            std::cout << "Erreur dans l'entrer des valeurs veuillez entrez une valeur entre " << plageDebut << " et " << plageFin << std::endl;
        }
        std::cin >> resultat;
        std::cin.clear(); //on clear le cin pour eviter de rentrer dans une boucle infini dans le cas ou l'utilisateur rentre un charactère
        std::cin.ignore();
        erreur = true; //on indique par défaut qu'il y'a une erreur car si on ne sort pas de la boucle cela indique bien que l'utilisateur a fait une erreur lors de la saisie
                       //on lui rapelle alors la plage de données a utilisé
    }while(resultat < plageDebut || resultat > plageFin);
    return resultat; //on retourne le resultat qui pourra etre utilisé dans nos menus
}

void afficherTemps (int secondes)// fonction qui permet d'afficher le temps
{
    int heures;
    int minutes;
    int reste;
    heures = secondes / 3600; //on divise le nombre d'heure par 3600 pour obtenir des secondes
    minutes = (secondes - heures * 3600)/ 60; //on recupere le nombre de minute en prenant en compte le nombre d'heure
    reste = secondes % 60; //finalement le modulo de 60 va nous donné le résultat final
    std::cout << heures << " H "<< minutes << " m " << reste << " s ";
}

bool IsPathExist(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}
