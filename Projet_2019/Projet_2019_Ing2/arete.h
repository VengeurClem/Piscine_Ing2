#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "poids.h"
#include "sommet.h"

class arete
 {
 public:
    arete(sommet,sommet,poids);
    poids getPoids() const {return m_p;};
    std::vector<sommet> getSommets() const {return m_ext;};
    ~arete();
 protected:

 private:
    std::vector<sommet> m_ext;
    poids m_p;
    bool m_used;
 };

#endif // ARETE_H_INCLUDED
