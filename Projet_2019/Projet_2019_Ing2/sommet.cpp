#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"

sommet::sommet(int id,int M,std::vector<float>coords):m_ID{id},m_marque{M},m_coords{coords}
{

}

void sommet::ajouterVoisin(sommet voisin){
    m_voisins.push_back(voisin);
}
void sommet::setMarque(int a)
{
    m_marque=a;
}

sommet::~sommet()
{

}
