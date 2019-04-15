#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

class sommet
 {
 public:
    sommet();
    int getID() const {return m_ID;};
    int getMarque() const {return m_marque;};
    ~sommet();
 protected:

 private:
    const int m_ID;
    int m_marque;
    const std::vector<const float> coords;
 };

#endif // SOMMET_H_INCLUDED
