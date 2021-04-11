#include "lib.hpp"


void Graphe::Dijkstra(int debut, int arrive, bool gene, bool horaire, int temps, bool exclu, std::string type)
{
    std::vector<std::vector<int>> tab;
    std::vector<int> infos;
    int poidsChemin = 0;
    int temp,tempPoids,min,minPoids;
    bool continuer = true;
    bool affichageResu = true;
    bool trouver = false;
    infos.push_back(0); //marquage
    infos.push_back(-1); //poids
    infos.push_back(-1); //predecesseur
    for(int i=0; i < m_ordre; i++)
    {
        tab.push_back(infos);//ont crée un tableau comprenant toutes les infos pour chaque sommet du graphe
    }
    tab[debut][0] = 1;//on marque le sommet de départ
    tab[debut][1] = 0;// il est à une distance nulle de lui même
    tab[debut][2] = -1 ;//il n'a pas de pédecesseurs
    for(unsigned int i = 0 ; i < m_tab[debut]->getSize();i++)//on parcours les adjacents de notre sommet de départ
    {
       temp = m_tab[debut]->getNum(i);
       tempPoids = m_tab[debut]->getPoids(i);
       tab[temp][0] = 0;
       tab[temp][1] = tempPoids;//on note la durée pour accéder à ces sommets
       tab[temp][2] = debut;// on note le prédecesseur de ces sommets
    }
    while(continuer)
    {
	    minPoids = 1000000;
        for(int i = 0 ; i < m_ordre;i++)
        {
            if((tab[i][0] == 0) && (tab[i][2] != -1) && tab[i][1] < minPoids)// on sélectionne le sommet non marqué dont la distance est la plus petite par rapport à notre sommet sélectionné
            {
                min = i;
                minPoids = tab[i][1];//le durée minimu devient donc la durée pour accéder à ce sommet
            }
        }
        tab[min][0] = 1;//on marque le sommet sélectionné
        poidsChemin = tab[min][1];
        for(unsigned int i = 0 ; i < m_tab[min]->getSize();i++)//On parcourt tous les adjacents au sommet sélectionné
        {
            temp = m_tab[min]->getNum(i);// on récupère le numéro de l'adjacent
            tempPoids = m_tab[min]->getPoids(i);// on récupère la durée pour accéder à, cet adjacent
            if(((tempPoids + poidsChemin) < tab[temp][1]) || (tab[temp][1] == -1))// soit le sommet était à une durée infini , soit on le met à jour dans le cas ou le nouveau trajet est plus court
            {
                tab[temp][0] = 0;
                tab[temp][1] = poidsChemin + tempPoids; //la durée du trajet est la somme de l'ancienne durée + de la nouvelle
                tab[temp][2] = min;
            }
        }
        continuer = false;
        for(int i = 0 ; i < m_ordre;i++)// on vérifie si tous les sommets ont été marqués
        {
            if(tab[i][0] == 0)
            {
                continuer = true;
            }
        }
    }

    if(gene == false)// dans le cas ou on ne veut afficher qu'un chemin en particulier
    {
        temp = arrive;
        while(temp != debut)// on parcours en utilisant les prédecesserus tant que le numéro du sommet n'est pas celui du sommet de départ
        {
            std::cout << temp+1 << " <-- " ;
            temp = tab[temp][2];
        }
        std::cout << debut+1;
        std::cout << " : Duree du trajet ";
        afficherTemps(tab[arrive][1]);//durée du trajet pour arriver au sommet d'arrivé
        std::cout << std::endl;
    }
    else//dans le cas ou on veut afficher plusierus trajets partant d'un sommet
    {
        for(unsigned int i = 0 ; i < tab.size();i++)
        {
            if(horaire == true && tab[i][1] < temps)//affichage des trajets dans le cas ou on a une horaire à respecter
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
            else if(horaire == false && exclu == false)//cas générale ou l'on ne se soucie pas du type des pistes ni d'une horaire
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
            else if(exclu)//cas on l'on a exclu un certains type de piste
            {
                affichageResu = true;
                temp = i;
                while(temp != debut)
                {
                    for(unsigned int j = 0 ; j < m_tab[tab[temp][2]]->getSize(); j++)
                    {
                        if(m_tab[tab[temp][2]]->getNum(j) == temp)
                        {
                            if(m_tab[tab[temp][2]]->getType(j) == type)//test pour vérifir que la piste emprunté n'est pas le type que l'on a exclu
                            {
                                affichageResu = false;
                            }
                        }
                    }
                    temp = tab[temp][2];
                }
                if(affichageResu == true)//affichage dans le cas ou toutes les pistes empruntés sont conformes à la consigne
                {
                    trouver = true;
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
        if(trouver != true && exclu == true)//cas ou l'on a trouvé aucune piste ne passant pas par le type exclu
        {
            std::cout << "vous etes oblige de passer par le type de piste interdit :/" << std::endl;
        }
    }
}

void Graphe::DijkstraInteret(int debut, int arrive)
{
    std::vector<std::vector<int>> tab;
    std::vector<int> infos;
    int inteChemin = 0;
    int temp,maxi,tempInte,maxiInte;
    bool continuer = true;
    bool continuer2 = true;
    infos.push_back(0); //marquage
    infos.push_back(-1000); //interet
    infos.push_back(-1000); //predecesseur
    for(int i=0; i < m_ordre; i++)//On créé une case pour chaque sommet
    {
        tab.push_back(infos);
    }

    tab[debut][0] = 1;//on marque le premier sommet
    tab[debut][1] = 0;// il est à une distance 0 de lui même
    tab[debut][2] = -1;// Il n'a pas de pédecesseur

    for(unsigned int i = 0 ; i < m_tab[debut]->getSize(); i++)
    {
        temp = m_tab[debut]->getNum(i);
        tempInte = m_tab[debut]->getInteret(i);
        tab[temp][1] = tempInte;// On applique l'intérêt actuel à l'ensemble des adjacents du sommet de départ
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
            if((tab[i][0] == 0)&&(tab[i][1]!= -1000)&&(i != arrive))//si un sommet qui n'est pas l'arrivé n'est pas marqué on continu
            {
                continuer2= true;
                continuer = true;
            }
        }


        if(continuer2 == true)
        {
            maxiInte = -1000;// -1000 est équivalent à un intérêt infinement bas
            maxi = -1;
            for(int i = 0 ; i < m_ordre; i++)
            {
                if(((tab[i][0] == 0) && (tab[i][1] > maxiInte) && (i != arrive)))//On test quel est l'intérêt maximum parmis tous les adjacents
                {
                    maxi = i; // on retient l'adjacent dont l'intérêt est maximum
                    maxiInte = tab[i][1]; // on note ce nouvel intérêt
                }
            }
            if(maxi == -1)
            {
                maxi = arrive;// Dans le cas ou tout les adjacent ont été déja marqué on sélectionne l'arrivé

            }


            tab[maxi][0] = 1;// On marquele sommet sélectionné
            inteChemin = tab[maxi][1];
            // std::cout << "continuer 2" << std::endl;
            for(unsigned int i = 0 ; i < m_tab[maxi]->getSize(); i++)// On parcous tous les adjacents de notre sommet
            {
                temp = m_tab[maxi]->getNum(i);//on récupère le numéro de l'adjacent
                tempInte = m_tab[maxi]->getInteret(i);// on récupère l'intérêt du trajet pour aller à cet adjacent

                if(tab[temp][1] == -1000)//Cas ou l'adjacent est à un intérêt infinement bas de notre qommet
                {
                    tab[temp][0] = 0;
                    tab[temp][1] = inteChemin + tempInte;
                    tab[temp][2] = maxi;
                }
                else if((tempInte + inteChemin ) > (tab[temp][1]))// on vérifie si une mise à jour de l'intérêt pour ce déplacer à l'adjacent est disponible
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
            for(int i = 0 ; i < m_ordre; i++)// on observe si tous les sommets ont été marqués ou pas
            {
                if(tab[i][0] == 0)
                {
                    continuer = true;
                }
            }
        }
    }



    temp = arrive;
    while(temp != debut)// affichage de notre chemin avec le plus grand intérêt
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
    m_I_preds.clear(); //on commence par clear les prédecesseurs car on ne sait pas quel autre méthode a pu s'en servir
    for(int i = 0 ; i < m_ordre+2;i++) //on ajoute 2 a l'ordre pour ajouter les 2 sommets imagnaire utiliser dans le BFS
    {
        m_I_preds.push_back(-1);
    }
    std::queue<int> indice; //creer la queue pour le BFS
    std::vector<int> dejaVu; //creer le vecteur des sommets visités
    std::vector<int> chemin;
    indice.push(numero); //on ajoute le premier terme a traiter a notre pile
    dejaVu.push_back(numero); //on indique que le sommet en question a deja été vu
    int temp;
    bool doIt = false;
    if(affichage)
    {
        std::cout << "parcour du BFS a partir du sommet " << numero+1 <<" :"<< std::endl;
    }
    while(indice.size() != 0) //fait tourner l'algorithme tant que la pile n'est pas vide
    {
        for(unsigned int j = 0; j < m_tab_FF[indice.front()]->getSize() ; j++) //parcours le tableau particulier utiliser pour for fulkerson
        {
            doIt = false; //part du principe que l'on ne pourra pas visiter un sommet car son flot est deja surchargé
            if((m_tab_FF[indice.front()]->getCapa(j) > 0)) //si capacité positive on se trouve dans le cadre d'un chemin direct
            {
                if(m_tab_FF[indice.front()]->getCapa(j) - m_tab_FF[indice.front()]->getFlot(j) > 0) //si le flot n'est pas surchargé
                {
                    doIt = true; //on permet a l'algo de BFS de pouvoir verifier ce sommet
                }
            }
            else if(m_tab_FF[indice.front()]->getCapa(j) < 0) //dans le cas ou le flot est négatif on se trovue dans le cadre d'un chemin indirect
            {
                if(m_tab_FF[indice.front()]->getFlot(j) < 0) //test pour savoir si le flot est deja saturé
                {
                    doIt = true; //dans ce cas on permet a l'algo BFS de pouvoir verifier ce sommet
                }
            }
            else
            {
                doIt = false; //dans les autres cas on blinde pour etre sur qu'il n'ira pas le verifier
            }
            if(doIt == true) //si le flot n'est pas saturé on realise alors le BFS
            {
                if(std::find(dejaVu.begin(),dejaVu.end(),m_tab_FF[indice.front()]->getNum(j)) == dejaVu.end()) //on verifie que le sommet n'a pas déja été visité par le BFS
                {
                    m_I_preds[m_tab_FF[indice.front()]->getNum(j)] = indice.front(); //on indique le predecesseur pour ce sommet
                    indice.push(m_tab_FF[indice.front()]->getNum(j)); //il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                    dejaVu.push_back(m_tab_FF[indice.front()]->getNum(j)); //on ajoute ce sommet au vecteur dejaVu pour eviter de repasser dessus plus tard dans l'algorithme
                }
            }
        }
        indice.pop(); //on enleve le sommet car le processing est terminé

    }
    if(std::find(dejaVu.begin(), dejaVu.end(), 38) != dejaVu.end()) //on verifie que le BFS a bien pu arriver a la fin de l'algorithme si ce n'est pas le cas l'algorithme de
    {                                                               //Ford Fulkerson est terminé et le flot est optimisé
        temp = m_I_preds[numeroArrive];                             //sinon on repars du tableau de prédecesseur et on remonte jusqu'au depart
        if(affichage)
        {
            std::cout << numeroArrive + 1;
        }
        chemin.push_back(numeroArrive);
        while(temp != numero)
        {
            if(affichage) //si le débuggage est activé il affichera tous les étapes
            {
                std::cout << " <-- ";
                std::cout << temp + 1;
            }
            chemin.push_back(temp); //sinon il ajoute simplement les sommets au chemin entrepris pour utilisation dans Ford Fulkerson
            temp = m_I_preds[temp];
        }
        if(affichage)
        {
            std::cout <<" <-- "<< numero + 1 << std::endl;
        }
        chemin.push_back(numero);
    }
    return chemin; //finalement on return le chemin parcouru pour utilisation dans Ford Fulkerson
}

void Graphe::legacyBFS(int numero,int numeroArrive, bool affichage, int tabgene) //Il s'agit ici du BFS original il peut trouver le chemin pour different tableau en fonction de l'appelant
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
    if(affichage && (numero != numeroArrive))
    {
        std::cout << "parcour du BFS a partir du sommet " << numero+1 <<" :"<< std::endl;
    }
    if(tabgene==0) //different méthode ce serve de ce BFS on a besoin d'acceder a different tableau lors de l'utilisation de ce fait on specifie sur quel tableau on veut travailler
    {
        while(indice.size() != 0)
        {
            for(unsigned int j = 0; j < m_tab_ecart[indice.front()]->getSize() ; j++)
            {
                if(std::find(dejaVu.begin(),dejaVu.end(),m_tab_ecart[indice.front()]->getNum(j)) == dejaVu.end()) //verifie si le sommet a deja été visité lors de l'algo
                {
                    m_I_preds[m_tab_ecart[indice.front()]->getNum(j)] = indice.front(); //utilisation des tableau d'ecart dans le cas de Ford Fulkerson
                    indice.push(m_tab_ecart[indice.front()]->getNum(j)); //si il ne l'as jamais vu il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                    dejaVu.push_back(m_tab_ecart[indice.front()]->getNum(j));
                }
            }
            indice.pop();
        }
    }
    else if(tabgene==1 || tabgene == 2) //utilisation du tableau classique de donnés pour trouver le plus cours chemin
    {
        while(indice.size() != 0) //tant que la pile n'est pas vide on continue de faire tourner l'algorithme
        {
            for(unsigned int j = 0; j < m_tab[indice.front()]->getSize() ; j++)
            {
                if(std::find(dejaVu.begin(),dejaVu.end(),m_tab[indice.front()]->getNum(j)) == dejaVu.end()) //verifie si le sommet a deja été visité lors de l'algo
                {
                    m_I_preds[m_tab[indice.front()]->getNum(j)] = indice.front(); //on precise qu'elle est l'antecedent d'un sommet
                    indice.push(m_tab[indice.front()]->getNum(j)); //si il ne l'as jamais vu il ajoute alors l'indice de l'adjacent a la queue ainsi qu'au vecteur des elements deja visité
                    dejaVu.push_back(m_tab[indice.front()]->getNum(j));
                }
            }
            indice.pop(); //on decharge le sommet utilisé car on en a plus besoin
        }
    }
    if(affichage == true && ((tabgene == 0)|| (tabgene == 1)))
    {
        if(numero != numeroArrive) //verification pour le sommet de départ et d'arrivé pour eviter d'acceder a une case mémoire non défini
        {
            temp = m_I_preds[numeroArrive]; //on repart de l'arrivé et on remonte jusqu'au départ
            std::cout << numeroArrive+1;
            while(temp != numero) //tant que l'on est pas arrivé au début on remonte d'antecedent en antecedent
            {
                std::cout << " <-- ";
                std::cout << temp + 1;
                temp = m_I_preds[temp];
            }
            std::cout <<" <-- "<< numero + 1;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "vous etes deja arriver !" << std::endl; //dans le cas ou le depart est égale a l'arrivé on indique a l'utilisateur que l'on est déja arrivé a bon port
        }
    }
    else if(affichage == true && tabgene == 2) //dans le cadre de la version general pour tous les trajet partant de 5
    {
        for(int i = 0 ; i < m_ordre ;i++) //on teste tous les points d'arrivés
        {
            if(i != numero) //on verifie que le numero actuel est différent du départ pour eviter d'acceder a une case mémoire invalide
            {
                temp = m_I_preds[i];
                std::cout << i+1;
                while(temp != numero)
                {
                    std::cout << " <-- ";
                    std::cout << temp+1;
                    temp = m_I_preds[temp];
                }
                std::cout << " <-- " << numero + 1 << std::endl;
            }
        }
    }
}

void Graphe::trouverChemin(int sommet)//fonction qui nous permet à partir d'un sommet tous les trajets amenant de ce dernier
{
    std::map<int,int> trajet; //on comence par creer une map pour enregistrer les trajets sortant
    for(unsigned int i = 0 ; i < m_tab.size();i++) //on parcours tous les sommets
    {
        for(unsigned int j = 0 ; j < m_tab[i]->getSize();j++) //on parcours leurs tableau d'adjacence
        {
            if(m_tab[i]->getNum(j) == sommet) // si le numero est égale on marque le numero i et j
            {
                trajet[i] = j;
            }
        }
    }
    for(auto& elem:trajet)
    {
        std::cout << "depart: " << m_tab[elem.first]->getNum()+1 << " arrive: " << m_tab[elem.first]->getNum(elem.second)+1 << std::endl;
        //on parcours la map pour l'affichage et on affiche les points de départ et d'arrivés
    }
}

int Graphe::FF(int affichage)//fonction réalisant l'algo de Ford-Fulkerson
{
    std::vector<int> temp;
    int min = 90000;
    bool continuer = true;
    int flotMax = 0;
    int tempPoids;
    int depart;
    int arrive;
    m_tab_FF.push_back(new Sommet(37, -1));//on rajoute un sommet de départ imaginaire (S0)
    m_tab_FF.push_back(new Sommet(38, -1));// et un sommet d'arrivé imaginaire (P0)
    //On réaliser les connexions entre ces deux sommets avec les autres sommets du graphe
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[0], 37, -1, -1, 100000, "");
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[29], 37, -1, -1, 100000, "");
    m_tab_FF[37]->ajouterAdjacent(m_tab_FF[35], 37, -1, -1, 100000, "");
    m_tab_FF[4]->ajouterAdjacent(m_tab_FF[38], 4, -1, -1, 100000 ,"");
    m_tab_FF[12]->ajouterAdjacent(m_tab_FF[38], 12, -1, -1, 100000, "");
    m_tab_FF[25]->ajouterAdjacent(m_tab_FF[38], 25, -1, -1, 100000, "");
    m_tab_FF[14]->ajouterAdjacent(m_tab_FF[38], 14, -1, -1, 100000, "");
    if(affichage == 1)
    {
        for(unsigned int i = 0 ; i < m_tab_FF.size(); i++)
        {
            std::cout << "numero " << i+1 << ": ";
            m_tab_FF[i]->afficher();
            std::cout << std::endl;
        }
    }
    while(continuer)
    {
        temp.clear();
        if(affichage == 1)// on distingue les cas ou l on affiche les étapes de calcul de l'algo de FF
        {
            temp = BFS(37,38, true);
        }
        else
        {
            temp = BFS(37,38, false);
        }

        min = 90000;
        //On cherche la plus petites valeurs de différence entre capacité et flot, ou dans le cas ou l on a une arrête dans le sens indirect le plus petits flot
        for(int i = temp.size() - 1; i > 0 ; i--)//On va parcourir tous les sommets de notre chemin donné par le BFS
        {
            for(unsigned int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)//On parcours les adjacents direct et indirect de  notre sommet
            {
                if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])// Test si l'adjacent est égale à notre prédecesseur
                {
                    if(m_tab_FF[temp[i]]->getCapa(j) < 0)// cas ou pour aller à notre prédecesseur on à un trajet indirect
                    {
                        if(m_tab_FF[temp[i]]->getFlot(j) < min && m_tab_FF[temp[i]]->getFlot(j) != 0)//On retient la valeur du flot si c'est la plus petite et si elle est différente de 0
                        {
                            min = m_tab_FF[temp[i]]->getFlot(j);
                        }
                    }
                    else if(m_tab_FF[temp[i]]->getCapa(j)> 0 && (m_tab_FF[temp[i]]->getCapa(j) != m_tab_FF[temp[i]]->getFlot(j)))// cas ou pour aller à notre prédecesseur on à un trajet direct
                    {
                        if((m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j))  < min)//On regarde si la différence du flot et capacité est la plus petite
                        {
                            min = m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j);
                        }
                    }
                }
            }
        }
        if(min > 0)// Dans le cas ou le minimum est négatif on l 'applique dans ce test
        {
            for(int i = temp.size() - 1; i > 0 ; i--)
            {
                for(unsigned int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)
                {
                    if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])//On cherche le somme trajet qui nous permet d'accéder à notre prédecesseur
                    {
                        if((m_tab_FF[temp[i]]->getCapa(j) - m_tab_FF[temp[i]]->getFlot(j)) > 0)
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(min, j);
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(unsigned int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)// On ajoute le flot sur le trajet inverse
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
        if(min < 0)// Dans le cas ou le minimum est positif on l 'applique dans ce test
        {
            for(int i = temp.size() - 1; i > 0 ; i--)
            {
                for(unsigned int j = 0; j < m_tab_FF[temp[i]]->getSize(); j++)
                {
                    if(m_tab_FF[temp[i]]->getNum(j) == temp[i-1])//On cherche le somme trajet qui nous permet d'accéder à notre prédecesseur
                    {
                        if(m_tab_FF[temp[i]]->getCapa(j) < 0)//Cas ou le trajet sur lequel on doit rajouter les flot est indirect
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(-min, j);//ont ajoute le flot sur le trajet
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(unsigned int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)// On soustrait le flot sur le trajet inverse
                            {
                                if(((m_tab_FF[temp[i-1]]->getNum(l) == temp[i]))&&(m_tab_FF[temp[i-1]]->getPoids(l) == tempPoids))
                                {
                                    m_tab_FF[temp[i-1]]->ajouterFlot(min, l);
                                }
                            }
                        }
                        else if(m_tab_FF[temp[i]]->getCapa(j) > 0)//Cas ou le trajet sur lequel on doit rajouter les flot est direct
                        {
                            m_tab_FF[temp[i]]->ajouterFlot(-min, j);//ont ajoute le flot sur notre trajet
                            tempPoids = m_tab_FF[temp[i]]->getPoids(j);
                            for(unsigned int l = 0; l < m_tab_FF[temp[i-1]]->getSize(); l++)// On soustrait le flot sur le trajet inverse
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
        if(affichage == 1)// cas ou l'on souhaite afficher les différentes étapes de calcul
        {
            std::cout << std::endl;
            std::cout << min << std::endl;
            std::cout << std::endl;
            for(unsigned int l = 0 ; l < m_tab_FF.size(); l++)
            {
                std::cout << "numero " << l+1 << ": ";
                m_tab_FF[l]->afficher();
                std::cout << std::endl;
            }
        }
        if(min == 90000)// si aucune différence de flot n'a été sélectionné cela signifie que
        {
            continuer = false;
        }
    }
    for(unsigned int i = 0; i < m_tab_FF[37]->getSize();i++)//On calcul le flot max
    {
        flotMax += m_tab_FF[37]->getFlot(i);
    }
    if(affichage == 2)
    {
        std::cout << std::endl <<"Le flot maximal est de "<< flotMax << " personnes." << std::endl << std::endl;// affichage du flot maximal
    }
    if(affichage == 3)// Cas ou l'on souhaite afficher le graphe d'écart
    {
        std::cout << "Graphe d'ecart" << std::endl;
        for(int i = 0 ; i < m_ordre;i++)
        {
            std::cout << "Sommet " << i+1 << ": ";
            for(unsigned int j = 0 ; j < m_tab_FF[i]->getSize();j++)
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

void Graphe::OptimiserCapa() //Fonction qui nous permet d'optimiser les capcités maximales de nos trajets tout en gardant le même flot maximal
{
    bool continuer = true;
    int flotRef, temp;
    std::cout << "Capacites de depart: " << std::endl;
    for(auto& elem:m_capacite)//On parcours et on affiche le types ainsi que leur capcité maximales associées
    {
        std::cout << elem.first << " : " << elem.second << std::endl;
    }
    Graphe *tempO = new Graphe(this, m_capacite);// création d'un graphe temporaire sur le quel on va effectuer notre FF
    flotRef = tempO->FF(4);// On calcul le flot maximal au départ sans avoir changé les valeurs des capacités
    delete tempO;
    std::cout << "Flot de depart " << flotRef << std::endl;
    for(auto& elem:m_capacite)// On va parcourir chaque type de piste
    {
        while(continuer == true)
        {
            if(elem.second != 50)//Si la capcité n'est pas égale à 50, on la diminue
            {
                elem.second -=10;
            }
            else
            {
                continuer = false;// Si la capa max est égale à 50 on passe au prochain type de piste
            }
            if(tempO != nullptr)
            {
                delete tempO;
            }
            tempO = new Graphe(this, m_capacite);// On créé une copie du graphe
            temp = tempO->FF(4);// On calcul le flot maximal
            if(temp != flotRef  && continuer != false)// Si le flot maximal n'est plus le même on passe au type de piste suivant et on rétablit la valeur de la capacité max
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


    for(auto& elem:m_capacite)// On affiche les nouvelles capacités
    {
        std::cout << elem.first << " : " << elem.second << std::endl;
    }

    std::cout << "Flot d'arrive " << tempO->FF(4) << std::endl; // On affiche le flot max d'arrivé pour vérifier que sa valeur n'a pas été modifiée
}

void Graphe::Kruskal(int choix, bool affichage)
{
    std::vector<std::vector<int>> tab;// tableau qui contient toutes les informations des trajets
    std::vector<std::vector<int>> numK;//tableau qui associe aux sommets plusieurs numéros
    std::vector<int> tempInfos;//variables qui permettent l'initialisation des tableaux
    std::vector<int> tempInfos2;
    int num1;//correspond à un sommet
    int num2;//correspond à un sommet
    int num3;//correspond à un numéro associé à un sommet
    int num4;//correspond à un numéro associé à un sommet
    int tempPoids;
    int dureeTot = 0;//somme de toutes les duree ou tous les interets
    int trajetSelec = 0;
    bool continuer = true;
    for(int i = 0; i < m_ordre; i ++)//initialisation de numK
    {
        tempInfos2.push_back(i);
        numK.push_back(tempInfos2);
        tempInfos2.clear();
    }
    for(unsigned int i = 0; i < m_tab_trajet.size(); i ++)//initalisation de tab qui contient toutes les informations des trajets
    {
        num1 = m_tab_trajet[i].getSommet(0);
        num2 = m_tab_trajet[i].getSommet(1);

        if(choix == 1)
        {
            tempPoids = m_tab_trajet[i].getPoids();//On récupère une durée dans ce cas
        }
        else if(choix == 2)
        {
            tempPoids = m_tab_trajet[i].getInteret();// On récupère
        }


        if( num1 > num2)
        {
            tempInfos.push_back(num2);//numéro du premier sommet
            tempInfos.push_back(num1);// numéro du deuxième sommet
            tempInfos.push_back(tempPoids);//durée ou intérêt du trajet
            tempInfos.push_back(0);//si le trajet a été sélectionné
            tempInfos.push_back(0);
        }
        else
        {
            tempInfos.push_back(num1);
            tempInfos.push_back(num2);
            tempInfos.push_back(tempPoids);
            tempInfos.push_back(0);
            tempInfos.push_back(0);
        }
        tab.push_back(tempInfos);
        tempInfos.clear();
    }
    if(choix == 1)//permet de trier le tableau de trajets
    {
        std::sort(tab.begin(),tab.end(), [](const std::vector<int> &id1, const std::vector<int> &id2){if(id1[2] == id2[2]){return id1[0] < id2[0];}else{return id1[2] < id2[2];}});
    }
    else if(choix == 2)
    {
        std::sort(tab.begin(),tab.end(), [](const std::vector<int> &id1, const std::vector<int> &id2){if(id1[2] == id2[2]){return id1[0] < id2[0];}else{return id1[2] > id2[2];}});
    }
    while(continuer)
    {
        num1  = tab[trajetSelec][0];
        num2  = tab[trajetSelec][1];
        num3 = -1;
        num4 = -1;
        for(unsigned int i = 0; i < numK.size();i++)
        {
            for(unsigned int j=0; j < numK[i].size();j++)
            {
                if(numK[i][j] == num1)
                {
                    num3 = i;// on sélectionne les numéros associé au premier sommet de notre trajet
                }
                if(numK[i][j] == num2)
                {
                    num4 = i;// on sélectionne les numéros associé au premier sommet de notre trajet
                }
            }
        }
        if(num3 != num4)
        {
            for(int i = numK[num4].size() - 1; i >= 0 ;i--)
            {
                numK[num3].push_back(numK[num4][i]);//permet d'appliaquer le numéro sélectionné aux autres sommets
                numK[num4].pop_back();
            }
            tab[trajetSelec][3] = 1 ;
        }
        else
        {
            tab[trajetSelec][3] = 0 ;
        }
        if(affichage)//affichage des différentes étapes
        {
           if(tab[trajetSelec][3] == 1)
            {
            for(unsigned int i = 0; i < numK.size();i++)//Pour chaque numéro on affiche les sommet ayant ce numéro
                {
                    if(numK[i].size() != 0)
                    {
                        std::cout << "Liste des sommets ayant pour numero : " << i+1 << " -> ";
                        for(unsigned int j=0; j< numK[i].size();j++)
                        {
                            std::cout << numK[i][j]+1 << " ";
                        }
                        std::cout << std::endl;
                    }
                }
            std::cout << std::endl;
            }
        }
        for(unsigned int i = 0; i < numK.size();i++)
        {
            if(numK[i].size() == 37)//Si tous les sommets ont le même numéro ont arrête l'algorithme
            {
                continuer = false;
            }
        }
        trajetSelec ++;
    }
    for(unsigned int i = 0; i < tab.size(); i ++)// affichage du graphe final
    {
        if(tab[i][3] == 1)
        {
             std::cout << "Trajet selectionnee numero : " << i+1 << "// Du sommet " << tab[i][0]+1 << " a " << tab[i][0]+1 << std::endl;
             dureeTot += tab[i][2];
        }
    }
    if(choix == 1)//dans le cas ou on réalise l algorithme de Kruskal à partir des durée
    {
        std::cout << "La duree totale pour parcourir l'ensemble des sommets est :" ;
        afficherTemps(dureeTot);
        std::cout << std::endl;
    }
    else if(choix == 2)//dans le cas ou on réaliser Kruskal à partir des intérêts
    {
        std::cout << "En parcourant intelligemment tous les sommets l'interet maximum que l'on peut obtenir est : " << dureeTot ;
        std::cout << std::endl;
    }
}
