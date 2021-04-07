#include "lib.hpp"

Graphe::Graphe(std::string nomFichier)
{
    std::string poubelle;
    std::string type;
    bool continuer = true;
    int num,poids, id1,id2, temp;
    std::ifstream fichier(nomFichier);
    if(!fichier)
    {
        std::cout << "erreur lors de l'ouverture du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        for(int i = 0 ; i < 12 ;i++)
        {
            fichier >> poubelle;
            fichier >> m_temps[poubelle];
        }
        for(int i =0 ; i < 12; i++)
        {
            fichier >> poubelle;
            fichier >> m_interet[poubelle];
        }
        for(int i =0 ; i < 12 ;i++)
        {
            fichier >> poubelle;
            fichier >> m_capacite[poubelle];
        }
        fichier >> m_ordre;
        for(int i = 0 ; i < m_ordre;i++)
        {
            fichier >> num;
            fichier >> poubelle;
            fichier >> poids;
            m_tab.push_back(new Sommet(num-1, poids));
            m_tab_FF.push_back(new Sommet(num-1, poids));
        }
        fichier >> m_taille;
        for(int i = 0 ; i < m_taille;i++)
        {
            fichier >> poubelle;
            fichier >> poubelle;
            fichier >> type;
            fichier >> id1;
            fichier >> id2;
            id1 = id1-1;
            id2 = id2-1;
            temp = calculerDuree(id1, id2, type);
            m_tab[id1]->ajouterAdjacent(m_tab[id2], id1, temp, m_interet[type], m_capacite[type], type);
            m_tab_FF[id1]->ajouterAdjacent(m_tab[id2], id1, temp, m_interet[type], m_capacite[type], type);
            m_tab_FF[id2]->ajouterAdjacent(m_tab[id1], id2, -temp, m_interet[type], -m_capacite[type], type);
            m_tab_trajet.push_back(Trajet(m_tab[id1], m_tab[id2], temp));
        }
        for(int i = 0 ; i < m_ordre+2;i++)
        {
            m_I_preds.push_back(-1);
        }
    }
    fichier.close();
}

Graphe::Graphe(Graphe *c, std::map<std::string, int> capacite)
{
    m_ordre = c->m_ordre;
    m_taille = c->m_taille;
    for(int i = 0 ; i < c->m_tab_FF.size();i++)
    {
        m_tab_FF.push_back(new Sommet(c->m_tab_FF[i]->getNum(), c->m_tab_FF[i]->getPoids()));
    }
    for(int i = 0 ; i < c->m_tab_FF.size();i++)
    {
        for(int j = 0 ; j < c->m_tab_FF[i]->getSize();j++)
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

void Graphe::fichier(std::string nomFichier, int choix)
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
    typeNom["TPH"] = "Telepherique";
    typeNom["TC"] = "Telecabine";
    typeNom["TSD"] = "Telesiege debrayable";
    typeNom["TS"] = "Telesiege";
    typeNom["TK"] = "Teleski";
    typeNom["BUS"] = "Navettes";
    bool continuer = true;
    int tempInt[12], temptaille, tempid, tempoids , tempdepart,temparrive;
    std::string type[12] = {"V", "B", "R", "N", "KL", "SURF", "TPH", "TC", "TSD", "TS", "TK", "BUS"};
    std::fstream fichier(nomFichier, std::ios::in | std::ios::out);
    if(!fichier)
    {
        std::cout << "erreur lors de l'ouverture du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Bienvenue dans la customisation des";
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
        for(int i = 0 ; i < 12;i++)
        {
            std::cout << typeNom[type[i]] << ": ";
            tempInt[i] = choisir(-1000000, 100000);
        }
        std::cout << "Interet enregistrer !" << std::endl;
        std::ofstream temp("temp.txt");
        if(!temp)
        {
            std::cout << "erreur lors de la creation du fichier temporaire" << std::endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            fichier.seekg(0);
            if(choix == 1) //interet
            {
                for(int i = 0 ; i < 12; i++)
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle << std::endl;
                }
                for(int i = 0; i < 12; i++)
                {
                    temp << type[i] << " " << tempInt[i] << std::endl;
                    fichier >> poubelle;
                    fichier >> poubelle;
                }
                for(int i = 0 ; i < 12; i++)
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle << std::endl;
                }
            }
            else if(choix == 2) //capacite
            {
                for(int i = 0 ; i < 24; i++)
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle <<std::endl;
                }
                for(int i = 0; i < 12; i++)
                {
                    temp << type[i] << " " << tempInt[i] << std::endl;
                    fichier >> poubelle;
                    fichier >> poubelle;
                }
            }
            else if(choix == 3) //temps
            {
                for(int i = 0; i < 12; i++)
                {
                    temp << type[i] << " " << tempInt[i] << std::endl;
                    fichier >> poubelle;
                    fichier >> poubelle;
                }
                for(int i = 0 ; i < 24; i++)
                {
                    fichier >> poubelle;
                    temp << poubelle << " ";
                    fichier >> poubelle;
                    temp << poubelle <<std::endl;
                }
            }
            fichier >> temptaille;
            temp << temptaille << std::endl;
            for(int i = 0 ; i < temptaille; i++)
            {
                fichier >> tempid;
                fichier >> poubelle;
                fichier >> tempoids;
                temp << tempid << " " << poubelle << " " <<tempoids << std::endl;
            }
            fichier >> temptaille;
            temp << temptaille << std::endl;
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
        temp.close();
        fichier.close();
        std::remove(nomFichier.c_str());
        std::rename("temp.txt", nomFichier.c_str());
    }
}
void Sommet::ajouterAdjacent(Sommet* adjacent, int num, int poids, int interet, int capacite, std::string type) //methode qui ajoute un adjacent de maniere a respecter l'encapsulation
{
    m_adjacent.push_back(adjacent);
    m_tab_poids.push_back(poids);
    m_tab_interet.push_back(interet);
    m_capacite.push_back(capacite);
    m_tab_flot.push_back(0);
    m_tab_type.push_back(type);
    m_num = num;
}

void Sommet::ajouterFlot(int flot, int num)
{
    m_tab_flot[num] += flot;
}

int Sommet::getIndice(int num)const
{
    int temp;
    for(unsigned int i = 0;i < m_adjacent.size();i++)
    {
        if(num == m_adjacent[i]->m_num)
        {
            temp = i;
        }
    }
    return temp;
}

void Graphe::afficher()const
{
    std::cout << "Ordre du graphe = " << m_ordre << std::endl;
    std::cout << "Sommet X : numero adjacent - duree - interet - capacite - flot" << std::endl;
    for(unsigned int i = 0 ; i < m_tab.size() ; i++)
    {
        std::cout << "sommet " << i+1 << " : ";
        m_tab[i]->afficher();
        std::cout << std::endl;
    }
}

void Sommet::afficher()const
{
    for(unsigned int i = 0 ; i < m_adjacent.size(); i++) //methode d'affichage des adjacents afin de respecter l'encapsulation
    {
        std::cout << m_adjacent[i]->m_num+1 << "  " << m_tab_poids[i];
        std::cout << "  "<< m_tab_interet[i];
        if(m_capacite[i] != -1)
        {
            std::cout << "  " << m_capacite[i];
        }
        std::cout << "  " << m_tab_flot[i];
        if(i != m_adjacent.size()-1)
        {
            std::cout << " // ";
        }
    }
}
Trajet::Trajet(Sommet* id1, Sommet* id2, int poids)
{
    m_tab_adj[0] = id1;
    m_tab_adj[1] = id2;
    m_poids = poids;
}

void Trajet::afficher()const
{
    std::cout << "depart: " << m_tab_adj[0]->getNum() << " arrive: " << m_tab_adj[1]->getNum() << " poids du trajet: " << m_poids << std::endl;
}

int Graphe::calculerDuree(int id1, int id2, std::string type)
{
    int altitude1 = m_tab[id1]->getPoids();
    int altitude2 = m_tab[id2]->getPoids();
    int denivele = altitude2 - altitude1;
    int duree;
    if(denivele < 0)
    {
        denivele = -denivele;
    }
    if(type == "V")
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
    return duree;
}
void Graphe::trouverSommetsTrajet()
{
    int choix;
    std::cout << "Quel est le numero du trajet dont vous voullez observer le point de depart et le point d'arrive?" <<std::endl;
    choix = choisir(1, m_tab_trajet.size());
    std::cout << "Le trajet numero " << choix << " part du sommet " << m_tab_trajet[choix-1].getSommet(0) + 1 << " et arrive au sommet " << m_tab_trajet[choix-1].getSommet(1) + 1 << std::endl;
}


int choisir(int plageDebut, int plageFin)
{
    int resultat;
    bool erreur = false;
    do
    {
        if(erreur == true)
        {
            std::cout << "Erreur dans l'entrer des valeurs veuillez entrez une valeur entre " << plageDebut << " et " << plageFin << std::endl;
        }
        std::cin >> resultat;
        std::cin.clear();
        std::cin.ignore();
        erreur = true;
    }while(resultat < plageDebut || resultat > plageFin);
    return resultat;
}

void afficherTemps (int secondes)
{
    int heures;
    int minutes;
    int reste;
    heures = secondes / 3600;
    minutes = (secondes - heures * 3600)/ 60;
    reste = secondes % 60;
    std::cout << heures << " H "<< minutes << " m " << reste << " s ";
}