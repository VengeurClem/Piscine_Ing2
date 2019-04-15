#ifndef POIDS_H_INCLUDED
#define POIDS_H_INCLUDED

class poids
 {
 public:
    poids(const int);
    int getNombrePoids() const {return valeurs.size();};
    ~poids();
 protected:

 private:
    std::vector<const float> valeurs;
 };
#endif // POIDS_H_INCLUDED
