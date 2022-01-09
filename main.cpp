#include <iostream>
#include "Sculptor.h"

using namespace std;

int main(){
    Sculptor fig(70,70,70); //

    //corpo
    fig.setColor(0.77,0.07,0.07,1.0);
    fig.putSphere(28,28,40,8);
    fig.putSphere(28,28,35,8);
    fig.putEllipsoid(28,28,31,8,8,6);
    fig.cutBox(20,36,20,36,25,27);
    //pernas
    fig.putEllipsoid(24, 28, 26, 3,3,5);
    fig.putEllipsoid(32, 28, 26, 3,3,5);
    //mochila
    fig.setColor(0.49, 0.03, 0.22, 1.0);
    fig.putBox(21,35,20,24,30,41);
    //capacete
    fig.setColor(0.59, 0.78, 0.87, 0.87);
    fig.putEllipsoid(28,34,41,6,3,3);




    fig.writeOFF("AmongUs.off");
    return 0;
}
