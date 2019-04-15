#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include "poids.h"
#include "sommet.h"

class arete
 {
 public:
    arete();
    poids getPoids() const {return m_p;};
    std::vector<const sommet*> const {return m_ext;};
    ~arete();
 protected:

 private:
     std::vector<const sommet*> m_ext;
    poids m_p;
 };

#endif // ARETE_H_INCLUDED
