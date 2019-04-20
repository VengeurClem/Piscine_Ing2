#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "graphe.h"
#include <allegro.h>


int main()
{
    allegro_init();
    int a=0;
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    BITMAP* Screen_buffer = create_bitmap(800,600);
    graphe g1{"../files/broadway.txt" , "../files/broadway_weights_0.txt"};
    graphe g2{"../files/manhattan.txt" , "../files/manhattan_weights_0.txt"};
    graphe g3{"../files/triville.txt" , "../files/triville_weights_0.txt"};
    graphe g4{"../files/cubetown.txt" , "../files/cubetown_weights_0.txt"};
    std::cout<<"Les deux Prim pour Broadway:"<<std::endl;
    g1.Prim(0);
    g1.Prim(1);
    std::cout<<"Les deux Prim pour Cubetown:"<<std::endl;
    g4.Prim(0);
    g4.Prim(1);
    std::cout<<"Les deux Prim pour Triville:"<<std::endl;
    g3.Prim(0);
    g3.Prim(1);
    std::cout<<"Les deux Prim pour Manhattan:"<<std::endl;
    g2.Prim(0);
    g2.Prim(1);
    while(a<=5)
    {
        clear_bitmap(Screen_buffer);
        std::cout<< std::endl
                 << "entrez votre choix" <<std::endl
                 << "1 pour Broadway" <<std::endl
                 << "2 pour Manhattan" <<std::endl
                 << "3 pour Triville" <<std::endl
                 << "4 pour Cubetown" <<std::endl;
        std::cin >> a;
        if(a==1)
        {
            g1.afficher(Screen_buffer);
        }
        if(a==2)
        {
            g2.afficher(Screen_buffer);
        }
        if(a==3)
        {
            g3.afficher(Screen_buffer);
        }
        if(a==4)
        {
            g4.afficher(Screen_buffer);
        }
        if(a==-1)
        {
            g1.SolAd(Screen_buffer);
            g1.Solutions();
        }
        if(a==-2)
        {
            g2.SolAd(Screen_buffer);
            g2.Solutions();
        }
        if(a==-3)
        {
            g3.SolAd(Screen_buffer);
        }
        if(a==-13)
        {

            g3.Solutions();
        }
        if(a==-4)
        {
            g4.SolAd(Screen_buffer);
        }
        if(a==-14)
        {

            g4.Solutions();
        }
    }
    return 0;
}END_OF_MAIN();
