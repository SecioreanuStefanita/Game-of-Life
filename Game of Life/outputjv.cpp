#include "outputjv.h"
#include "jocv.h"
#include <Windows.h>
#include<iostream>
static int contor=0;
void scrie_caracter_la_poz(char *buff, int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
    DWORD dwCount = 0;
    WriteConsoleA(hConsole, buff, 1, &dwCount, NULL);
}

output::output(engine *pm) : motor(pm) {};

void output::init()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
    system("cls");


    for (int x = 0; x < motor->get_nc(); x++)
    {
        for (int y = 0; y < motor->get_nl(); y++)
        {
            unit *u = motor->get_unit_xy(x, y);
            if (u == NULL)
            {
                scrie_caracter_la_poz(const_cast<char *>(" "), x, y);
            }
            else
            {
                scrie_caracter_la_poz(static_cast<char *>(u->get_tip()), x, y);
            }
        }
    }
    contor=0;
}

void output::close()
{
}

void output::afisare()
{


    for (int x = 0; x < motor->get_nc(); x++)
    {
        for (int y = 0; y < motor->get_nl(); y++)
        {
            unit *u = motor->get_unit_xy(x, y);
            if (u == NULL)
            {
                scrie_caracter_la_poz(const_cast<char *>(" "), x, y);
            }
            else
            {
                scrie_caracter_la_poz(static_cast<char *>(u->get_tip()), x, y);
            }
        }
    }
    contor++;
    std::cout<<"Generatia curenta: "<<contor<<" .";
}
