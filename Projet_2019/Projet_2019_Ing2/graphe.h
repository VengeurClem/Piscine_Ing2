#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <string>
#include "poids.h"
#include "arete.h"
#include "sommet.h"
#include "allegro.h"
#include <time.h>
class graphe
 {
 public:
    graphe(std::string, std::string);
    graphe(std::vector<float>, std::vector <arete>, std::vector <sommet>);
    void afficher(BITMAP*) const;
    void Prim(int z) const;
    ~graphe();
    std::vector<float> getPoids() const {return m_p;};
    std::vector<graphe> SolAd(BITMAP*);
    std::vector<graphe> Solutions();
    std::vector <sommet> getSommets() const {return m_sommets;};
 protected:

 private:
    std::vector<float> m_p;
    std::vector <arete> m_aretes;
    std::vector <sommet> m_sommets;
};

#endif // GRAPHE_H_INCLUDED
