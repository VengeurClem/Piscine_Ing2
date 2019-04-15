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
    //graphe g{"../files/broadway.txt" , "../files/broadway_weights_0.txt"};
    graphe g{"../files/triville.txt" , "../files/triville_weights_0.txt"};
    g.afficher();
    return 0;
}
