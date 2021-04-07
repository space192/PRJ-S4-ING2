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
	    minPoids = 1000000;
        for(int i = 0 ; i < m_ordre;i++)
        {
            if((tab[i][0] == 0) && (tab[i][2] != -1) && tab[i][1] < minPoids)
            {
                min = i;
                minPoids = tab[i][1];
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
        std::cout << " : Duree du trajet ";
        afficherTemps(tab[arrive][1]);
        std::cout << std::endl;
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
            afficherTemps(tab[i][1]);

            std::cout << std::endl;
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

std::vector<int> Graphe::BFS(int numero, int numeroArrive, bool affichage) //algorithme de BFS prend en parametre le numero du point de part valeur par defaut de l'affichage sur true
{
    m_I_preds.clear();
    for(int i = 0 ; i < m_ordre+2;i++)
    {
        m_I_preds.push_back(-1);
    }
    std::queue<int> indice; //creer la queue pour le BFS
    std::vector<int> dejaVu; //creer le vecteur des sommets visités
    std::vector<int> chemin;
    indice.push(numero);
    dejaVu.push_back(numero);
    int temp;
    bool doIt = false;
    if(affichage)
    {
        std::cout << "parcour du BFS a partir du sommet " << numero+1 <<" :"<< std::endl;
    }
    while(indice.size() != 0)
    {
        for(unsigned int j = 0; j < m_tab_FF[indice.front()]->getSize() ; j++)
        {
            doIt = false;
            if((m_tab_FF[indice.front()]->getCapa(j) > 0))
            {
                if(m_tab_FF[indice.front()]->getCapa(j) - m_tab_FF[indice.front()]->getFlot(j) > 0)
                {
                    doIt = true;
                }
            }
            else if(m_tab_FF[indice.front()]->getCapa(j) < 0)
            {
                if(m_tab_FF[indice.front()]->getFlot(j) < 0)
                {
                    doIt = true;
                }
            }
            else
            {
                doIt = false;
            }
            if(doIt == true) //verifie si le sommet a deja été visité lors de l'algo
            {
                if(std::find(dejaVu.begin(),dejaVu.end(),m_tab_FF[indice.front()]->getNum(j)) == dejaVu.end())
                {
                    m_I_preds[m_tab_FF[indice.front()]->getNum(j)] = indice.front();
                    indice.push(m_tab_FF[indice.front()]->getNum(j)); //si il ne l'as jamais vu il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                    dejaVu.push_back(m_tab_FF[indice.front()]->getNum(j));
                }

            }
        }
        indice.pop();

    }
    if(std::find(dejaVu.begin(), dejaVu.end(), 38) != dejaVu.end())
    {
        temp = m_I_preds[numeroArrive];
        if(affichage)
        {
            std::cout << numeroArrive + 1;
        }
        chemin.push_back(numeroArrive);
        while(temp != numero)
        {
            if(affichage)
            {
                std::cout << " <-- ";
                std::cout << temp + 1;
            }
            chemin.push_back(temp);
            temp = m_I_preds[temp];
        }
        if(affichage)
        {
            std::cout <<" <-- "<< numero + 1 << std::endl;
        }
        chemin.push_back(numero);
    }
    return chemin;
}

void Graphe::legacyBFS(int numero,int numeroArrive, bool affichage) //algorithme de BFS prend en parametre le numero du point de part valeur par defaut de l'affichage sur true
{
    m_I_preds.clear();
    for(int i = 0 ; i < m_ordre + 2 ;i++)
    {
        m_I_preds.push_back(-1);
    }
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
        for(unsigned int j = 0; j < m_tab_ecart[indice.front()]->getSize() ; j++)
        {
            if(std::find(dejaVu.begin(),dejaVu.end(),m_tab_ecart[indice.front()]->getNum(j)) == dejaVu.end()) //verifie si le sommet a deja été visité lors de l'algo
            {
                m_I_preds[m_tab_ecart[indice.front()]->getNum(j)] = indice.front();
                indice.push(m_tab_ecart[indice.front()]->getNum(j)); //si il ne l'as jamais vu il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                dejaVu.push_back(m_tab_ecart[indice.front()]->getNum(j));
            }
        }
        indice.pop();
    }
    if(affichage)
    {
        temp = m_I_preds[numeroArrive];
        std::cout << numeroArrive+1;
        while(temp != numero)
        {
            std::cout << " <-- ";
            std::cout << temp + 1;
            temp = m_I_preds[temp];
        }
        std::cout <<" <-- "<< numero + 1;
        std::cout << std::endl;
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

int Graphe::FF(int affichage)
{
    std::vector<int> temp;
    int min = 90000;
    int tempPos1, tempPos2;
    bool continuer = true;
    int flotMin = 90000;
    int flotMax = 0;
    int tempPoids;
    int depart;
    int arrive;
    m_tab_FF.push_back(new Sommet(37, -1));
    m_tab_FF.push_back(new Sommet(38, -1));
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[0], 37, -1, -1, 100000, "");
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[29], 37, -1, -1, 100000, "");
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[35], 37, -1, -1, 100000, "");
    m_tab_FF[4]->ajouterAdjacent(m_tab_FF[38], 4, -1, -1, 100000 ,"");
    m_tab_FF[12]->ajouterAdjacent(m_tab_FF[38], 12, -1, -1, 100000, "");
    m_tab_FF[25]->ajouterAdjacent(m_tab_FF[38], 25, -1, -1, 100000, "");
    m_tab_FF[14]->ajouterAdjacent(m_tab_FF[38], 14, -1, -1, 100000, "");
    if(affichage == 1)
    {
        for(int i = 0 ; i < m_tab_FF.size(); i++)
        {
            std::cout << "numero " << i+1 << ": ";
            m_tab_FF[i]->afficher();
            std::cout << std::endl;
        }
    }
    while(continuer)
    {
        temp.clear();
        if(affichage == 1)
        {
            temp = BFS(37,38, true);
        }
        else
        {
            temp = BFS(37,38, false);
        }

        min = 90000;

        for(int i = temp.size() - 1; i > 0 ; i--)
        {
            for(int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)
            {
                if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])
                {
                    if(m_tab_FF[temp[i]]->getCapa(j) < 0)
                    {
                        if(m_tab_FF[temp[i]]->getFlot(j) < min && m_tab_FF[temp[i]]->getFlot(j) != 0)
                        {
                            min = m_tab_FF[temp[i]]->getFlot(j);
                        }
                    }
                    else if(m_tab_FF[temp[i]]->getCapa(j)> 0 && (m_tab_FF[temp[i]]->getCapa(j) != m_tab_FF[temp[i]]->getFlot(j)))
                    {
                        if((m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j))  < min)
                        {
                            min = m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j);
                        }
                    }
                }
            }
        }
        if(min > 0)
        {
            for(int i = temp.size() - 1; i > 0 ; i--)
            {
                for(int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)
                {
                    if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])
                    {
                        if((m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j)) > 0)
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(min, j);
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)
                            {
                                if(((m_tab_FF[temp[i-1]]->getNum(l) == temp[i]))&&(m_tab_FF[temp[i-1]]->getPoids(l) == tempPoids))
                                {
                                    m_tab_FF[temp[i-1]]->ajouterFlot(min, l);
                                }
                            }
                            j = m_tab_FF[temp[i]]->getSize();
                        }
                    }
                }
            }
        }
        if(min < 0)
        {
            for(int i = temp.size() - 1; i > 0 ; i--)
            {
                for(int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)
                {
                    if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])
                    {
                        if(m_tab_FF[temp[i]]->getCapa(j) < 0)
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(-min, j);
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)
                            {
                                if(((m_tab_FF[temp[i-1]]->getNum(l) == temp[i]))&&(m_tab_FF[temp[i-1]]->getPoids(l) == tempPoids))
                                {
                                    m_tab_FF[temp[i-1]]->ajouterFlot(min, l);
                                }
                            }
                        }
                        else if(m_tab_FF[temp[i]]->getCapa(j) > 0)
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(-min, j);
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)
                            {

                                if(((m_tab_FF[temp[i-1]]->getNum(l) == temp[i]))&&(m_tab_FF[temp[i-1]]->getPoids(l) == tempPoids))
                                {
                                    m_tab_FF[temp[i-1]]->ajouterFlot(min, l);
                                }

                            }
                        }

                    }
                }
            }
        }
        if(affichage == 1)
        {
            std::cout << std::endl;
            std::cout << min << std::endl;
            std::cout << std::endl;
            for(int l = 0 ; l < m_tab_FF.size(); l++)
            {
                std::cout << "numero " << l+1 << ": ";
                m_tab_FF[l]->afficher();
                std::cout << std::endl;
            }
        }
        if(min == 90000)
        {
            continuer = false;
        }
    }
    for(int i = 0; i < m_tab_FF[37]->getSize();i++)
    {
        flotMax += m_tab_FF[37]->getFlot(i);
    }
    if(affichage == 2)
    {
        std::cout << std::endl <<"Le flot maximal est de "<< flotMax << " personnes." << std::endl << std::endl;
    }
    if(affichage == 3)
    {
        std::cout << "Graphe d'ecart" << std::endl;
        for(int i = 0 ; i < m_ordre;i++)
        {
            std::cout << "Sommet " << i+1 << ": ";
            for(int j = 0 ; j < m_tab_FF[i]->getSize();j++)
            {
                if(m_tab_FF[i]->getCapa(j) > 0 && m_tab_FF[i]->getCapa(j) < 90000)
                {
                    std::cout << m_tab_FF[i]->getNum(j)+1 << " " << m_tab_FF[i]->getCapa(j) - m_tab_FF[i]->getFlot(j) << " / ";
                }
            }
            std::cout << std::endl;
        }
        m_tab_ecart = m_tab_FF;
        m_tab_ecart.pop_back();
        m_tab_ecart.pop_back();
        std::cout << "entrez le point de depart dans le graphe d'ecart" << std::endl;
        depart = choisir(1, m_tab_ecart.size());
        std::cout << "entrer le point d'arrive dans le graphe d'ecart" << std::endl;
        arrive = choisir(1, m_tab_ecart.size());
        legacyBFS(depart-1, arrive-1, true);
    }
    return flotMax;
}

void Graphe::OptimiserCapa()
{
    bool continuer = true;
    int flotRef, temp;
    std::cout << "Capacites de depart: " << std::endl;
    for(auto& elem:m_capacite)
    {
        std::cout << elem.first << " : " << elem.second << std::endl;
    }
    Graphe *tempO = new Graphe(this, m_capacite);
    flotRef = tempO->FF(4);
    delete tempO;
    std::cout << "Flot de depart " << flotRef << std::endl;
    for(auto& elem:m_capacite)
    {
        while(continuer == true)
        {
            if(elem.second != 0)
            {
                elem.second -=10;
            }
            else
            {
                continuer = false; 
            }
            if(tempO != nullptr)
            {
                delete tempO;
            }
            tempO = new Graphe(this, m_capacite);
            temp = tempO->FF(4);
            if(temp != flotRef  && continuer != false)
            {
                continuer = false;
                elem.second +=10;
            }
            /*else
            {
                continuer = true;
            }*/
        }
        continuer = true;
    }
    
    std::cout << "Capacites optimisees: " << std::endl;

    if(tempO != nullptr)
            {
                delete tempO;
            }
    tempO = new Graphe(this, m_capacite);


    for(auto& elem:m_capacite)
    {
        std::cout << elem.first << " : " << elem.second << std::endl;
    }

    std::cout << "Flot d'arrive " << tempO->FF(4) << std::endl;
}