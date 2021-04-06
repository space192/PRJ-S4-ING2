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
            m_tab_inverse.push_back(new Sommet(num-1, poids));
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
            m_tab[id1]->ajouterAdjacent(m_tab[id2], id1, temp, m_interet[type], m_capacite[type]);
            m_tab_inverse[id2]->ajouterAdjacent(m_tab[id1], id2, temp, m_interet[type], m_capacite[type]);
            m_tab_trajet.push_back(Trajet(m_tab[id1], m_tab[id2], temp));
        }
        for(int i = 0 ; i < m_ordre;i++)
        {
            m_I_preds.push_back(-1);
        }
    }
    fichier.close();
}

void Graphe::fichier(std::string nomFichier, int choix)
{
    std::string tempstring, poubelle, temptype;
    std::string temptab[12];
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
        std::cout << std::endl << "pour chaque type de déplacement vous devrez rentrez un";
        if(choix == 1)
        {
            std::cout <<  "interet";
        }
        else if(choix == 2)
        {
            std::cout << "capacite";
        }
        std::cout << std::endl;
        std::cout << "rentrer l'interet de la piste:" << std::endl;
        for(int i = 0 ; i < 12;i++)
        {
            std::cout << type[i] << ": ";
            std::cin >> tempInt[i];
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
            if(choix == 1)
            {
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
            else if(choix == 2)
            {
                for(int i = 0 ; i < 12; i++)
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
void Sommet::ajouterAdjacent(Sommet* adjacent, int num, int poids, int interet, int capacite) //methode qui ajoute un adjacent de maniere a respecter l'encapsulation
{
    m_adjacent.push_back(adjacent);
    m_tab_poids.push_back(poids);
    m_tab_interet.push_back(interet);
    m_capacite.push_back(capacite);
    m_num = num;
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
    std::cout << "ordre = " << m_ordre << std::endl;
    std::cout << "listes d'adjacence :" << std::endl;
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
        std::cout << m_adjacent[i]->m_num+1 << " " << m_tab_poids[i];
        std::cout << " " << m_tab_interet[i];
        if(m_capacite[i] != -1)
        {
            std::cout << " " << m_capacite[i];
        }
        std::cout << "/";
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
        duree = (300*denivele)/100;
    }
    else if(type == "B")
    {
        duree = (240*denivele)/100;
    }
    else if(type == "R")
    {
        duree = (180*denivele)/100;
    }
    else if(type == "N")
    {
        duree = (120*denivele)/100;
    }
    else if(type == "KL")
    {
        duree = (10*denivele)/100;
    }
    else if(type == "SURF")
    {
        duree = (600*denivele)/100;
    }
    else if(type == "TPH")
    {
        duree = 240 + (120*denivele)/100;
    }
    else if(type == "TC")
    {
        duree = 120 + (1280*denivele)/100;
    }
    else if(type == "TSD")
    {
        duree = 60 + (180*denivele)/100;
    }
    else if(type == "TS" || type == "TK")
    {
        duree = 60 + (240*denivele)/100;
    }
    else if(type == "BUS")
    {
        if((id1 == 6 && id2 == 29)||(id1 == 29 && id2 == 6))
        {
            duree = 2400;
        }
        else if((id1 == 29 && id2 == 35)||(id1 == 35 && id2 == 29))
        {
            duree = 1800;
        }
    }
    return duree;
}
void Graphe::trouverSommetsTrajet()
{
    int choix;
    std::cout << "Quel est le numero du trajet dont vous voullez observer le point de depart et le point d'arrive?" <<std::endl;
    std::cin >> choix;
    std::cout << "Le trajet numero " << choix << " part du sommet " << m_tab_trajet[choix-1].getSommet(0) + 1 << " et arrive au sommet " << m_tab_trajet[choix-1].getSommet(1) + 1 << std::endl;
}