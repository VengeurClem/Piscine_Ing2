#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "graphe.h"


int main()
{
    std::cout << "Hello world!" << std::endl;
    graphe g1{"../files/broadway.txt" , "../files/broadway_weights_0.txt"};
    graphe g2{"../files/manhattan.txt" , "../files/manhattan_weights_0.txt"};
    graphe g3{"../files/triville.txt" , "../files/triville_weights_0.txt"};
    graphe g4{"../files/cubetown.txt" , "../files/cubetown_weights_0.txt"};
    g1.afficher();
    g2.afficher();
    g3.afficher();
    g4.afficher();
    g2.SolAd();
    //g1.SolAd();

    //g3.SolAd();
    //g4.SolAd();
    return 0;
}
