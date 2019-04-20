#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class sommet
 {
 public:
    sommet(int,int,std::vector<float>);
    int getID() const {return m_ID;};
    std::vector<sommet> getSuccesseur() const {return m_voisins;};
    int getMarque() const {return m_marque;};
    void setMarque(int);
    float getX() const {return m_coords[0];};
    float getY() const {return m_coords[1];};
    float getZ() const {return m_coords[2];};
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
