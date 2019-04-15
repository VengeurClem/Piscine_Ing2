#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <string>
#include "poids.h"
#include "arete.h"
#include "sommet.h"
class graphe
 {
 public:
    graphe(std::string, std::string);
    void afficher() const;
    ~graphe();
    float getPoids() const {return m_p;};
 protected:

 private:
    float m_p;
    std::vector <arete> m_aretes;
    std::vector <sommet> m_sommets;
};

#endif // GRAPHE_H_INCLUDED
