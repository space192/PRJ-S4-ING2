#include "lib.hpp"

Graphe::Graphe(std::string nomFichier)
{
    std::string poubelle;
    std::string type;
    int num,poids, id1,id2;
    std::ifstream fichier(nomFichier);
    if(!fichier)
    {
        std::cout << "erreur lors de l'ouverture du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        fichier >> m_ordre;
        for(int i = 0 ; i < m_ordre;i++)
        {
            fichier >> num;
            fichier >> poubelle;
            fichier >> poids;
            m_tab.push_back(new Sommet(num-1, poids));
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
            m_tab[id1]->ajouterAdjacent(m_tab[id2], id1, calculerDuree(id1, id2, type));
        }
        afficher();
    }
}

void Sommet::ajouterAdjacent(Sommet* adjacent, int num, int poids) //methode qui ajoute un adjacent de maniere a respecter l'encapsulation
{
    m_adjacent.push_back(adjacent);
    m_tab_poids.push_back(poids);
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
        std::cout << m_adjacent[i]->m_num+1 << " " << m_tab_poids[i] << " / ";
    }
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