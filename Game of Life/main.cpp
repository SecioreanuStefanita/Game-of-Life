#include <iostream>

#include "outputjv.h"
#include "jocv.h"
#include <Windows.h>

using namespace std;

int main()
{
    fiinta::motor.init(80, 50);
    new planta(3, 0);
    new planta(1, 1);
    new planta(2, 2);
    new ierbivor(10, 10);
    new ierbivor(5, 5);
    new ierbivor(8, 3);
    new carnivor(12,10);
    new planta(19, 1);
     new planta(9, 9);
    new planta(8, 11);
     new ierbivor(19, 19);
     new ierbivor(1, 3);
    new carnivor(28,30);
    new planta(25,25);
    new carnivor(70,30);
    output iesire(&fiinta::motor);
    iesire.init();
    do

    {
        fiinta::motor.next();
        iesire.afisare();
        Sleep(1);
    }
    while (fiinta::get_nr_fiinte() > 0);
    iesire.close();
    return 0;
}
