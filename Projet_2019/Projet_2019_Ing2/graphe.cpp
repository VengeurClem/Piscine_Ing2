#include <fstream>
#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "math.h"
#include "graphe.h"
#include <algorithm>
#include <vector>
#include <bitset>
#include <queue>

graphe::graphe(std::string nomFichier1, std::string nomFichier2)
{
    std::ifstream ifs1{nomFichier1};
    std::ifstream ifs2{nomFichier2};
    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier1 );
    int ordre;
    ifs1 >> ordre;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;
    int id_bis;
    float x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        std::vector<float> coords;
        ifs1>>id; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>x; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        coords.push_back(x);
        ifs1>>y; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        coords.push_back(y);
        //ifs1>>y; if(ifs1.fail()) throw std::runtime_error("Probleme lecture données sommet");
        coords.push_back(0);
        m_sommets.push_back(sommet(id, i, coords));
    }
    int taille;
    int nb_crit;
    int p_poids;
    float C1;
    ifs1 >> taille;
    ifs2 >> taille;
    ifs2 >> nb_crit;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i)
    {
        //lecture des aretes
        ifs1>>p_poids; if(ifs1.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs2>>p_poids; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs1>>id; if(ifs1.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs1>>id_bis  ; if(ifs1.fail()) throw std::runtime_error("Probleme lecture arete");
        std::vector<float> p_p_poids;
        float p=0;
        for (int i=0; i< nb_crit; i++)
        {
            ifs2>>C1; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete");
            p_p_poids.push_back(C1);
            p=p+C1;
        }
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        m_sommets[id].ajouterVoisin(m_sommets[id_bis]);
        m_sommets[id_bis].ajouterVoisin(m_sommets[id]);
        m_aretes.push_back(arete(m_sommets[id],m_sommets[id_bis],poids(p_p_poids)));
        m_p=p_p_poids;

    }
}

graphe::graphe(std::vector<float> p, std::vector <arete> ar, std::vector <sommet> so) : m_p(p), m_aretes(ar), m_sommets(so)
{

}



void graphe::afficher(BITMAP* buffer) const
{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"  ordre : " << m_sommets.size()<<std::endl;
    for(auto s : m_sommets)
    {
        std::cout << "  sommet :    "<< s.getID() <<"  -  "
                                     << s.getX() <<"  -  "
                                     << s.getY() <<"  -  "
                                     << s.getZ() ;
        std::cout << std::endl;
    }
    rectfill(buffer,0,0,SCREEN_W,SCREEN_H,makecol(0,0,0));
    for(unsigned int i=0; i<m_sommets.size();i++)
    {
        circlefill(buffer,m_sommets[i].getX(),m_sommets[i].getY(),10,makecol(255,0,0));
    }
    for(unsigned int i=0; i<m_aretes.size();i++)
    {
        line(buffer, m_sommets[m_aretes[i].getSommets()[0].getID()].getX(),m_sommets[m_aretes[i].getSommets()[0].getID()].getY(),m_sommets[m_aretes[i].getSommets()[1].getID()].getX(),m_sommets[m_aretes[i].getSommets()[1].getID()].getY(),makecol(0,255,0));
    }
    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}

std::vector<graphe> graphe::SolAd(BITMAP* buffer)
{
        //initialisation 1
        std::vector<graphe> AReturn;
        std::vector<arete> Aretes_choisies;
        std::vector<std::vector<arete>> a_a;
        unsigned int n = pow(2,m_aretes.size());
        std::cout << "n est  "<< n << std::endl;
        std::vector<short> choisi;
        std::vector<std::vector<short>> c_choisi;
        int mem;
        unsigned int test=0;
        std::vector<sommet> s=m_sommets;
        std::vector<sommet> p;
        std::vector<sommet>::iterator Vide;
        //création de vecteur de int pour simuler du binaire
        for(float i=pow(2,m_sommets.size()-1)-1;i<n;i++)
        {
            mem=i;
            while(mem>0)
            {
                if(mem%2==1)
                {
                    test++;
                }
                choisi.push_back(mem%2);
                mem=mem/2;
            }
            if(test==(m_sommets.size()-1))
            {
                while(choisi.size()<m_aretes.size())
                {
                    choisi.push_back(0);
                }
                std::reverse(choisi.begin(), choisi.end());
                c_choisi.push_back(choisi);
            }
            choisi.clear();
            test=0;

        }
        std::cout << c_choisi.size()<<std::endl;

        //initialisation 2
        std::vector<std::pair<int,int >> Choix_Arete;
        std::pair<int,int> buff;
        std::queue<int> Oh_BFS;
        std::vector<int> tableau;
        std::vector<int>::iterator it;

        for(int i=0; i<c_choisi.size();i++)
        {
            //on prends les arêtes corespondantes au binaire
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                if(c_choisi[i][j]==1)
                {
                    buff.first=m_aretes[j].getSommets()[0].getID();
                    buff.second=m_aretes[j].getSommets()[1].getID();
                    Choix_Arete.push_back(buff);
                }
            }
                Oh_BFS.push(0);//on met le premier sommet pour lancer le BFS

            while(Oh_BFS.empty()==false)
            {
                int p_pred=Oh_BFS.front();
                it=std::find(tableau.begin(),tableau.end(),p_pred);
                if(it==tableau.end())
                {
                    tableau.push_back(p_pred);
                }


                for(unsigned int j=0; j<Choix_Arete.size();j++)
                {
                    if(Choix_Arete[j].first==p_pred && std::find(tableau.begin(),tableau.end(),Choix_Arete[j].second)==tableau.end())
                    {
                        Oh_BFS.push(Choix_Arete[j].second);
                        tableau.push_back(Choix_Arete[j].second);
                    }
                    if(Choix_Arete[j].second==p_pred && std::find(tableau.begin(),tableau.end(),Choix_Arete[j].first)==tableau.end())
                    {
                        Oh_BFS.push(Choix_Arete[j].first);
                        tableau.push_back(Choix_Arete[j].first);
                    }
                }
                Oh_BFS.pop();
            }
            //on vérifie qu'il y a tout les sommets
            if(tableau.size()!=m_sommets.size())
            {
                c_choisi.erase(c_choisi.begin()+i);
                i--;
            }

            Choix_Arete.clear();
            tableau.clear();
        }
        //initialisation 3
        std::cout<< c_choisi.size()<<std::endl;
        std::vector<std::pair<float,float>>tri_poids;
        std::vector<std::pair<float,float>>tri_poids2;

        //récupération des poids pour déterminer la frontière de Pareto
        for(unsigned i=0; i<c_choisi.size();i++)
        {
            std::pair<float,float> buffer_p{0,0};
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                if(c_choisi[i][j]==1)
                {
                    buffer_p.first += m_aretes[j].getPoids().getPoids()[0];
                    buffer_p.second += m_aretes[j].getPoids().getPoids()[1];
                }
            }
            tri_poids.push_back(buffer_p);
        }
        //tri des poids 1
        std::vector<std::pair<float,float>> Sol_Pareto;
        tri_poids2=tri_poids;
        std::sort(tri_poids.begin(),tri_poids.end(), [](std::pair<float,float> a, std::pair <float,float> b){
                    return a.first < b.first;
                  });
        double MaxY= 10000000000;
        //tri des poids 2
        for(unsigned int i=0;i<tri_poids.size();i++)
        {
           if(tri_poids[i].second<MaxY)
               {
                   MaxY=tri_poids[i].second;
                   Sol_Pareto.push_back(tri_poids[i]);
               }
        }
        // vu que le sort ne regarde pas le deuxième poids on vérifie bien qu'on ne prends pas des intrus
        for(unsigned int i=1;i<Sol_Pareto.size();i++)
        {
           if(Sol_Pareto[i-1].first == Sol_Pareto[i].first)
               {
                   i--;
                   Sol_Pareto.erase(Sol_Pareto.begin()+i);
               }
        }
        //affichage de Pareto mais il est tard
        for(unsigned int i=0; i<Sol_Pareto.size();i++)
        {
            std::cout<< i+1 <<") Solution de Pareto   "
                     <<Sol_Pareto[i].first<<"  -  "
                     <<Sol_Pareto[i].second
                     <<std::endl;
        }
        srand(time(NULL));
        int alea=rand()%c_choisi.size();
        for(unsigned int j=0; j<c_choisi[alea].size();j++)
        {
            if(c_choisi[alea][j]==1)
            {
                circlefill(buffer,m_aretes[j].getSommets()[0].getX(),m_aretes[j].getSommets()[0].getY(),10,makecol(255,0,0));
                circlefill(buffer,m_aretes[j].getSommets()[1].getX(),m_aretes[j].getSommets()[1].getY(),10,makecol(255,0,0));
                line(buffer, m_sommets[m_aretes[j].getSommets()[0].getID()].getX(),m_sommets[m_aretes[j].getSommets()[0].getID()].getY(),
                     m_sommets[m_aretes[j].getSommets()[1].getID()].getX(),m_sommets[m_aretes[j].getSommets()[1].getID()].getY(),makecol(0,255,0));
            }
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        return AReturn;
}

std::vector<graphe> graphe::Solutions()
{
        //Initialisation
        std::vector<graphe> AReturn;
        std::vector<arete> Aretes_choisies;
        std::vector<std::vector<arete>> a_a;
        unsigned int n = pow(2,m_aretes.size());
        std::cout << "n est  "<< n << std::endl;
        std::vector<short> choisi;
        std::vector<std::vector<short>> c_choisi;
        int mem;
        unsigned int test=0;
        std::vector<sommet> s=m_sommets;
        std::vector<sommet> p;
        std::vector<sommet>::iterator Vide;
        //Graphes connexes uniquement
        for(float i=pow(2,m_sommets.size()-1)-1;i<n;i++)
        {
            mem=i;
            while(mem>0)
            {
                if(mem%2==1)
                {
                    test++;
                }
                choisi.push_back(mem%2);
                mem=mem/2;
            }
            if(test>=(m_sommets.size()-1))
            {
                while(choisi.size()<m_aretes.size())
                {
                    choisi.push_back(0);
                }
                std::reverse(choisi.begin(), choisi.end());
                c_choisi.push_back(choisi);
            }
            choisi.clear();
            test=0;

        }
        std::cout << c_choisi.size()<<std::endl;
        for(int i=0; i<c_choisi.size();i++)
        {
            int tableau[m_sommets.size()]={0};
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                if(c_choisi[i][j]==1)
                {
                    tableau[m_aretes[j].getSommets()[0].getID()]=1;
                    tableau[m_aretes[j].getSommets()[1].getID()]=1;
                }
            }
            for(unsigned int j=0;j<m_sommets.size();j++)
            {
                if(tableau[j]==0)
                {
                    c_choisi.erase(c_choisi.begin()+i);
                    i--;
                    j=m_sommets.size();
                }
            }
        }
        std::cout<< c_choisi.size()<<std::endl;


        /*
        for(unsigned int i=0; i<c_choisi.size();i++)
        {
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                std::cout<<c_choisi[i][j];
            }
            std::cout<<std::endl;
        }
        */
        return AReturn;
}

void graphe::Prim(int z) const
{
    /// Initialisation
    std::vector<arete> a;
    int marque[m_sommets.size()]={0};
    marque[0]=1;
    std::vector <int> ordre_lect;
    ordre_lect.push_back(0);
    ///Algorithme
    for(unsigned int i=0; i<m_sommets.size()-1;i++)//boucle pour attendre les n-1 arêtes
    {
         int rang_Pmin=0;
        for(unsigned int j=0; j<m_aretes.size(); j++)//boucle pour ajouter les arêtes du nouveau point
        {
            if(marque[m_aretes[j].getSommets()[0].getID()]==1 && marque[m_aretes[j].getSommets()[1].getID()]!=1)
            {
                a.push_back(m_aretes[j]);
            }
            if(marque[m_aretes[j].getSommets()[1].getID()]==1 && marque[m_aretes[j].getSommets()[0].getID()]!=1)
            {
                a.push_back(m_aretes[j]);
            }
        }
        for(unsigned int j=1; j<a.size();j++)
        {
            if(a[rang_Pmin].getPoids().getPoids()[z]>a[j].getPoids().getPoids()[z])
            {
                rang_Pmin=j;
            }
        }
        if(marque[a[rang_Pmin].getSommets()[0].getID()]==1)
        {
            marque[a[rang_Pmin].getSommets()[1].getID()]=1;
            ordre_lect.push_back(a[rang_Pmin].getSommets()[1].getID());
        }
        else if(marque[a[rang_Pmin].getSommets()[1].getID()]==1)
        {
            marque[a[rang_Pmin].getSommets()[0].getID()]=1;
            ordre_lect.push_back(a[rang_Pmin].getSommets()[0].getID());
        }
        a.clear();
    }
    std::cout<<"ordre d'apparition des sommets:  ";
    for(unsigned int i=0;i<ordre_lect.size();i++)
    {
        std::cout<< ordre_lect[i] << "  ";
    }
    std::cout<<std::endl;
}

graphe::~graphe()
{

}


        /*
        Ceci est une version non optimisé du test de connexité
        std::vector<std::pair<int,int >> Choix_Arete;
        std::pair<int,int> buff;
        std::queue<int> Oh_BFS;
        for(int i=0; i<c_choisi.size();i++)
        {
            int tableau[m_sommets.size()]={0};
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                if(c_choisi[i][j]==1)
                {
                    buff.first=m_aretes[j].getSommets()[0].getID();
                    buff.second=m_aretes[j].getSommets()[1].getID();
                    Choix_Arete.push_back(buff);
                }
            }

                Oh_BFS.push(0);
            while(Oh_BFS.empty()==false)
            {
                int p_pred=Oh_BFS.front();
                tableau[p_pred]=1;
                for(unsigned int j=0; j<Choix_Arete.size();j++)
                {
                    if(Choix_Arete[j].first==p_pred && tableau[Choix_Arete[j].second]==0)
                    {
                        Oh_BFS.push(Choix_Arete[j].second);
                        tableau[Choix_Arete[j].second]=1;
                    }
                    if(Choix_Arete[j].second==p_pred && tableau[Choix_Arete[j].first]==0)
                    {
                        Oh_BFS.push(Choix_Arete[j].first);
                        tableau[Choix_Arete[j].first]=1;
                    }
                }
                Oh_BFS.pop();
            }
            for(unsigned int j=0;j<m_sommets.size();j++)
            {
                if(tableau[j]==0)
                {
                    c_choisi.erase(c_choisi.begin()+i);
                    i--;
                    j=m_sommets.size();
                }
            }
            Choix_Arete.clear();
        }
        std::cout<< c_choisi.size()<<std::endl;*/
