#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "poids.h"
#include "arete.h"
#include "sommet.h"
class graphe
 {
 public:
    graphe();
    poids getPoids() const {return m_p;};
    ~graphe();
 protected:

 private:
    poids m_p;
    std::vector <const arete*> m_aretes;
    std::vector <const sommet*> m_sommets;
};

#endif // GRAPHE_H_INCLUDED
