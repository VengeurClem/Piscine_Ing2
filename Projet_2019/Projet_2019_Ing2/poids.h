#ifndef POIDS_H_INCLUDED
#define POIDS_H_INCLUDED

class poids
 {
 public:
    poids(std::vector<float>);
    int getNombrePoids() const {return m_valeurs.size();};
    std::vector<float> getPoids() const {return m_valeurs;};
    ~poids();
 protected:

 private:
    std::vector<float> m_valeurs;
 };
#endif // POIDS_H_INCLUDED
