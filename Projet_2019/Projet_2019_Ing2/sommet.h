#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class sommet
 {
 public:
    sommet(int,int,std::vector<float>);
    int getID() const {return m_ID;};
    int getMarque() const {return m_marque;};
    void ajouterVoisin(sommet);
    ~sommet();
 protected:

 private:
    int m_ID;
    int m_marque;
    std::vector<sommet> m_voisins;
    const std::vector<float> m_coords;
 };

#endif // SOMMET_H_INCLUDED
