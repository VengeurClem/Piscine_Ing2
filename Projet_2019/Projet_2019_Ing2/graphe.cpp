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



void graphe::afficher() const
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
}

std::vector<graphe> graphe::SolAd()
{
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
        /*for(unsigned int i=0; i<c_choisi.size();i++)
        {
            for(unsigned int j=0; j<c_choisi[i].size();j++)
            {
                std::cout<<c_choisi[i][j];
            }
            std::cout<<std::endl;
        }*/

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
        std::cout<< c_choisi.size()<<std::endl;

        return AReturn;
}

std::vector<graphe> graphe::Solutions()
{
    std::vector<arete> a= m_aretes;
    std::vector<graphe> g;
    //int ValeurMagique = m_aretes.size() - m_sommets.size() + 1;
    int JeSaisPas=0;
    while(JeSaisPas==0)
    {

    }

    return g;
}

graphe::~graphe()
{

}
