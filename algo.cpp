#include "lib.hpp"

void Graphe::Dijkstra(int debut, int arrive, bool gene)
{
    std::vector<std::vector<int>> tab;
    std::vector<int> infos;
    int poidsChemin = 0;
    int temp,tempPoids,min,minPoids;
    bool continuer = true;
    infos.push_back(0); //marquage
    infos.push_back(-1); //poids
    infos.push_back(-1); //predecesseur
    for(int i=0; i < m_ordre; i++)
    {
        tab.push_back(infos);
    }
    tab[debut][0] = 1;
    tab[debut][1] = 0;
    tab[debut][2] = -1 ;
    for(unsigned int i = 0 ; i < m_tab[debut]->getSize();i++)
    {
       temp = m_tab[debut]->getNum(i);
       tempPoids = m_tab[debut]->getPoids(i);
       tab[temp][0] = 0;
       tab[temp][1] = tempPoids;
       tab[temp][2] = debut;
    }
    while(continuer)
    {
	    minPoids = 1000;
        for(int i = 0 ; i < m_ordre;i++)
        {
            if((tab[i][0] == 0) && (tab[i][1] != -1) && tab[i][2] < minPoids)
            {
                min = i;
                minPoids = tab[i][2];
            }
        }
        tab[min][0] = 1;
        poidsChemin = tab[min][1];
        for(unsigned int i = 0 ; i < m_tab[min]->getSize();i++)
        {
            temp = m_tab[min]->getNum(i);
            tempPoids = m_tab[min]->getPoids(i);
            if(((tempPoids + poidsChemin) < tab[temp][1]) || (tab[temp][1] == -1))
            {
                tab[temp][0] = 0;
                tab[temp][1] = poidsChemin + tempPoids;
                tab[temp][2] = min;
            }
        }
        continuer = false;
        for(int i = 0 ; i < m_ordre;i++)
        {
            if(tab[i][0] == 0)
            {
                continuer = true;
            }
        }
    }

    //for(unsigned int i = 0 ; i < tab.size();i++)
    //{
        //std::cout << i << " : "<< tab[i][0] << " " << tab[i][1] << " " << tab[i][2] << " " << std::endl;
    //}
    if(gene == false)
    {
        temp = arrive;
        while(temp != debut)
        {
            std::cout << temp+1 << " <-- " ;
            temp = tab[temp][2];
        }
        std::cout << debut+1;
        std::cout << " : longeur ";
        std::cout << tab[arrive][1] << std::endl;
    }
    else
    {
        for(int i = 0 ; i < tab.size();i++)
        {
            temp = i;
            while(temp != debut)
            {
                std::cout << temp+1 << " <-- " ;
                temp = tab[temp][2];
            }
            std::cout << debut+1;
            std::cout << " : duree du trajet ";
            std::cout << tab[i][1] << std::endl;
        }
    }
}

void Graphe::DijkstraInteret(int debut, int arrive)
{
    std::vector<std::vector<int>> tab;
    std::vector<int> infos;
    int inteChemin = 0;
    int temp,tempInte,min,minPoids;
    bool continuer = true;
    infos.push_back(0); //marquage
    infos.push_back(-1); //interet
    infos.push_back(-1); //predecesseur
     for(int i=0; i < m_ordre; i++)
    {
        tab.push_back(infos);
    }
    tab[debut][0] = 1;
    tab[debut][1] = 0;
    tab[debut][2] = -1 ;
    for(unsigned int i = 0 ; i < m_tab[debut]->getSize();i++)
    {
       temp = m_tab[debut]->getNum(i);
       tempInte = m_tab[debut]->getInteret(i);
       tab[temp][0] = 0;
       tab[temp][1] = tempInte;
       tab[temp][2] = debut;
    }
}

void Graphe::BFS(int numero, bool affichage) //algorithme de BFS prend en parametre le numero du point de part valeur par defaut de l'affichage sur true
{
    std::queue<int> indice; //creer la queue pour le BFS
    std::vector<int> dejaVu; //creer le vecteur des sommets visités
    indice.push(numero);
    dejaVu.push_back(numero);
    int temp;
    if(affichage)
    {
        std::cout << "parcour du BFS a partir du sommet " << numero+1 <<" :"<< std::endl;
    }
    while(indice.size() != 0)
    {
        for(unsigned int j = 0; j < m_tab[indice.front()]->getSize() ; j++)
        {
            if(std::find(dejaVu.begin(),dejaVu.end(),m_tab[indice.front()]->getNum(j)) == dejaVu.end()) //verifie si le sommet a deja été visité lors de l'algo
            {
                m_I_preds[m_tab[indice.front()]->getNum(j)] = indice.front();
                indice.push(m_tab[indice.front()]->getNum(j)); //si il ne l'as jamais vu il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                dejaVu.push_back(m_tab[indice.front()]->getNum(j));
            }
        }
        indice.pop();
    }
    if(affichage)
    {
        for(unsigned int i = 0 ; i < m_I_preds.size();i++)
        {
            temp = m_I_preds[i];
            if(i != numero)
            {
                std::cout << i + 1;
                while(temp != numero)
                {
                    std::cout << " <-- ";
                    std::cout << temp + 1;
                    temp = m_I_preds[temp];
                }
                std::cout <<" <-- "<< numero + 1;
                std::cout << std::endl;
            }
            else if(i == numero)
            {
                std::cout << numero + 1 << std::endl;
            }
        }
    }
}
