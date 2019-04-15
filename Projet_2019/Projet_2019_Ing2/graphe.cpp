#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "graphe.h"

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
        m_sommets.push_back(sommet(id, i, coords));
    }
    int taille;
    int nb_crit;
    int p_poids;
    float C1;
    float C2;
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
        ifs2>>C1; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs1>>id_bis  ; if(ifs1.fail()) throw std::runtime_error("Probleme lecture arete");
        ifs2>>C2; if(ifs2.fail()) throw std::runtime_error("Probleme lecture arete");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        m_sommets[id].ajouterVoisin(m_sommets[id_bis]);
        m_sommets[id_bis].ajouterVoisin(m_sommets[id]);
        float p=0;
        std::vector<float> p_p_poids;
        p_p_poids.push_back(C1);
        p_p_poids.push_back(C2);
        p=p+C1+C2;
        m_aretes.push_back(arete(m_sommets[id],m_sommets[id_bis],poids(p_p_poids)));
        m_p=p;

    }
}

void graphe::afficher() const{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<"  ordre : " << m_sommets.size()<<std::endl;
    for(auto s : m_sommets)
    {
        std::cout << "  sommet :    "<< s.getID();
        std::cout << std::endl;
    }
}

graphe::~graphe()
{

}
