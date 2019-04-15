#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include<unordered_map>
#include<unordered_set>
#include "arete.h"

arete::arete(sommet S1, sommet S2, poids p)
    :  m_p(p), m_used(0)
{
    m_ext.push_back(S1);
    m_ext.push_back(S2);
}

arete::~arete()
{

}
