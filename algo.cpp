#include "lib.hpp"

void Graphe::Dijkstra(int debut, int arrive)
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

    temp = arrive;
    while(temp != debut)
    {
        std::cout << temp+1 << " <-- " ;
        temp = tab[temp][2];
    }
    std::cout << debut+1;
    std::cout << " : longeur ";
    /*temp = arrive;
    while(temp!=debut)
    {
        if(temp != arrive)
        {
            std::cout << "+";
        }
        std::cout << m_tab[tab[temp][2]]->getPoids(m_tab[tab[temp][2]]->getIndice(temp));
        temp = tab[temp][2];
    }*/
    std::cout << tab[arrive][1] << std::endl;
}