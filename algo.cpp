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
    int temp,maxi,cheminTotInter,tempInte,maxiInte;
    bool continuer = true;
    bool continuer2 = true;
    infos.push_back(0); //marquage
    infos.push_back(-1000); //interet
    infos.push_back(-1000); //predecesseur
    for(int i=0; i < m_ordre; i++)
    {
        tab.push_back(infos);
    }



    tab[debut][0] = 1;
    tab[debut][1] = 0;
    tab[debut][2] = -1;



    for(unsigned int i = 0 ; i < m_tab[debut]->getSize(); i++)
    {
        temp = m_tab[debut]->getNum(i);
        tempInte = m_tab[debut]->getInteret(i);
        tab[temp][1] = tempInte;
        tab[temp][2] = debut;
    }


    while(continuer)
    {

        if(tab[arrive][0] == 0)
        {
            continuer2 = false;
            continuer = false;
        }

        for(int i =0; i < m_ordre; i++)
        {
            if((tab[i][0] == 0)&&(tab[i][1]!= -1000)&&(i != arrive))
            {
                continuer2= true;
                continuer = true;
            }
        }


        if(continuer2 == true)
        {

            // std::cout << "continuer 1" << std::endl;
            maxiInte = -1000;
            maxi = -1;
            for(int i = 0 ; i < m_ordre; i++)
            {
                if(((tab[i][0] == 0) && (tab[i][1] > maxiInte) && (i != arrive)))
                {
                    maxi = i;
                    maxiInte = tab[i][1];
                }
            }
            if(maxi == -1)
            {
                maxi = arrive;

            }




            tab[maxi][0] = 1;
            inteChemin = tab[maxi][1];
            // std::cout << "continuer 2" << std::endl;
            for(unsigned int i = 0 ; i < m_tab[maxi]->getSize(); i++)
            {
                temp = m_tab[maxi]->getNum(i);
                tempInte = m_tab[maxi]->getInteret(i);
                
                if(tab[temp][1] == -1000)
                {
                    tab[temp][0] = 0;
                    tab[temp][1] = inteChemin + tempInte;
                    tab[temp][2] = maxi;
                }
                else if((tempInte + inteChemin ) > (tab[temp][1]))
                {
                    if(tab[temp][0]!=1)
                    {
                        tab[temp][0] = 0;
                        tab[temp][1] = inteChemin + tempInte;
                        tab[temp][2] = maxi;
                    }

                }
            }
            continuer = false;
            for(int i = 0 ; i < m_ordre; i++)
            {
                if(tab[i][0] == 0)
                {
                    continuer = true;
                }
            }
        }
    }



    temp = arrive;
    while(temp != debut)
    {
        std::cout << temp +1 << " <-- " ;
        temp = tab[temp][2];
    }
    std::cout << debut+1;
    std::cout << " : interet ";
    std::cout << tab[arrive][1] << std::endl;
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
    if(!affichage)
    {
        for(int i = 0 ; i < dejaVu.size();i++)
        {
            std::cout << dejaVu[i] << std::endl;
        }
    }
}


void Graphe::trouverChemin(int sommet)
{
    std::map<int,int> trajet;
    for(int i = 0 ; i < m_tab.size();i++)
    {
        for(int j = 0 ; j < m_tab[i]->getSize();j++)
        {
            if(m_tab[i]->getNum(j) == sommet)
            {
                trajet[i] = j;
            }
        }
    }
    for(auto& elem:trajet)
    {
        std::cout << "depart: " << m_tab[elem.first]->getNum()+1 << " arrive: " << m_tab[elem.first]->getNum(elem.second)+1 << std::endl;
    }
}


void Graphe::FF()
{
    
}