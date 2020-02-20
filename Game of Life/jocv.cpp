#include "jocv.h"
#include <stddef.h>
#include <vector>
#include <cmath>

#include <iostream>

#define KILL 100
int fiinta::nr_fiinte = 0;
void fiinta::action()
{
    if (apara() == 0)
    {
        if (energie < energie_optima)
        {
            mananca();
        }
        else
        {
            inmulteste();
        }
    }
    else
    {
        timp_ramas--;
        energie--;
    }
    if (timp_ramas <= 0 || energie <= 0)
    {
        this->die();
    }
}
fiinta::fiinta(int x, int y, int energie_optima, int durata_vietii, int energie_initiala) : unit::unit(x, y)
{
    this->energie_optima = energie_optima;
    this->timp_ramas = durata_vietii;
    this->energie = energie_initiala;
    nr_fiinte++;
}
fiinta::~fiinta()
{
    nr_fiinte -= 1;
}

int fiinta::get_nr_fiinte()
{
    return nr_fiinte;
}
int fiinta::get_energie()
{
    return this->energie;
}

planta::planta(int x, int y) : fiinta::fiinta(x, y, 100, 100, 50) {}

unsigned char planta::nume = 177;
void *planta::get_tip()
{
    return &nume;
}
int planta::apara()
{
    return 0;
}

void planta::mananca()
{
    this->energie += 2;
}
void planta::inmulteste()
{
    int contor = 0;
    int poz_curenta_i = unit::get_x();
    int poz_curenta_j = unit::get_y();
    for (int i = poz_curenta_i - 1; i <= poz_curenta_i + 1; ++i)
    {
        for (int j = poz_curenta_j - 1; j <= poz_curenta_j + 1; ++j)
        {
            if (j == poz_curenta_j && i == poz_curenta_i)
            {
                j++;
            }
            if (this->energie >= this->energie_optima && motor.validxy(i, j) == 1 && motor.get_unit_xy(i, j) == NULL)
            {
                contor = 1;
                new planta(i, j);
                this->energie = 3 * this->energie / 4;
            }
            if (contor == 1)
            {
                break;
            }
        }
    }
}
void planta::behaviour(int pm)
{
    if (pm < 0)
    {
        this->energie += pm;
    }
    if (this->energie < 0)
    {

        this->die();
    }
}

ierbivor::ierbivor(int x, int y) : fiinta::fiinta(x, y, 100, 100, 50) {}

unsigned char ierbivor::nume = 'i';
int ierbivor::apara()
{

    std::vector<carnivor *> v;
    int numar_carnivore = 0;
    int pozitie_curenta_x = this->get_x();
    int pozitie_curenta_y = this->get_y();
    for (int i = pozitie_curenta_x - 5; i <= pozitie_curenta_x + 5; ++i)
    {
        for (int j = pozitie_curenta_y - 5; j <= pozitie_curenta_y + 5; ++j)
        {
            carnivor *u = dynamic_cast<carnivor *>(motor.get_unit_xy(i, j));
            if (u != NULL)
            {
                numar_carnivore++;
                v.push_back(u);
            }
        }
    }

    if (numar_carnivore == 0)
    {
        return 0;
    }

    double distanta[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            distanta[i][j] = 0;
        }
    }

    double dist_max = -1;
    int x_nou;
    int y_nou;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k=0;k<numar_carnivore;k++)
            {carnivor*c=v[k];
                int x_t = (pozitie_curenta_x - c->get_x() + j + 1);
                int y_t = (pozitie_curenta_y - c->get_y() + i + 1);
                distanta[i][j] += sqrt(x_t * x_t + y_t * y_t);
            }
            if (distanta[i][j] > dist_max)
            {
                dist_max = distanta[i][j];
                x_nou = j;
                y_nou = i;
            }
        }
    }
    if (x_nou != 1 || y_nou != 1)
    {
        if (motor.validxy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1))
        {
            if (motor.get_unit_xy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1) == NULL)
                move_unit(x_nou - 1, y_nou - 1);
             return 1;
        }
    }
    else
    {
        return 0;
    }
}
void ierbivor::mananca()
{
    std::vector<planta *> v;
    int numar_plante = 0;
    int pozitie_curenta_x = this->get_x();
    int pozitie_curenta_y = this->get_y();
    for (int i = pozitie_curenta_x - 5; i <= pozitie_curenta_x + 5; ++i)
    {
        for (int j = pozitie_curenta_y - 5; j <= pozitie_curenta_y + 5; ++j)
        {
            planta *u = dynamic_cast<planta *>(motor.get_unit_xy(i, j));
            if (u != NULL)
            {
                numar_plante++;
                v.push_back(u);
            }
        }
    }

    if (numar_plante == 0)
    {

        return;
    }

    double distanta[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            distanta[i][j] = 0;
        }
    }

    double dist_min = 999999;
    int x_nou;
    int y_nou;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k=0;k<numar_plante;k++)
            {planta *c=v[k];
                int x_t = (pozitie_curenta_x - c->get_x() + j);
                int y_t = (pozitie_curenta_y - c->get_y() + i);
                distanta[i][j] += sqrt(x_t * x_t + y_t * y_t);
                if (motor.validxy(pozitie_curenta_x + j - 1, pozitie_curenta_y + i - 1) == 0)
                {
                    distanta[i][j] += 999999;
                }
                if (pozitie_curenta_x + j - 1 == c->get_x() && pozitie_curenta_y + i - 1 == c->get_y())
                {
                    distanta[i][j] = -999999;
                    break;
                }
            }
            if (distanta[i][j] <= dist_min)
            {
                dist_min = distanta[i][j];
                x_nou = j;
                y_nou = i;
            }
        }
    }
    if (x_nou != 1 || y_nou != 1)
    {
        if (motor.validxy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1))
        {
            unit *u = motor.get_unit_xy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1);
            if (u != NULL)
            {
                if (this->energie < this->energie_optima)
                    this->energie += 10;
                this->send_mes(-10, u);
            }

            if (motor.get_unit_xy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1) == NULL)
                move_unit(x_nou - 1, y_nou - 1);
        }
    }
}

void ierbivor::inmulteste()
{
    {
        int contor = 0;
        int poz_curenta_i = unit::get_x();
        int poz_curenta_j = unit::get_y();
        for (int i = poz_curenta_i - 1; i <= poz_curenta_i + 1; ++i)
        {
            for (int j = poz_curenta_j - 1; j <= poz_curenta_j + 1; ++j)
            {
                if (j == poz_curenta_j && i == poz_curenta_i)
                {
                    continue;
                }
                if (contor == 1)
                {
                    break;
                }
                if (this->energie >= this->energie_optima && motor.validxy(i, j) == 1 && motor.get_unit_xy(i, j) == NULL)
                {
                    contor = 1;
                    new ierbivor(i, j);
                    this->energie = 4*this->energie/5;
                }

            }
        }
    }
}
void ierbivor::behaviour(int pm)
{
    if (pm == 100)
    {
        this->die();
    }
}
void *ierbivor::get_tip()
{
    return &nume;
}

carnivor::carnivor(int x, int y) : fiinta::fiinta(x, y, 100, 200, 50) {}

unsigned char carnivor::nume = 'c';

int carnivor::apara()
{
    return 0;
}
void carnivor::mananca()
{
    std::vector<ierbivor *> v;
    int numar_ierbivori = 0;
    int pozitie_curenta_x = this->get_x();
    int pozitie_curenta_y = this->get_y();
    for (int i = pozitie_curenta_x - 5; i <= pozitie_curenta_x + 5; ++i)
    {
        for (int j = pozitie_curenta_y - 5; j <= pozitie_curenta_y + 5; ++j)
        {
            ierbivor *u = dynamic_cast<ierbivor *>(motor.get_unit_xy(i, j));
            if (u != NULL)
            {
                numar_ierbivori++;
                v.push_back(u);
            }
        }
    }

    if (numar_ierbivori == 0)
    {

        return;
    }

    double distanta[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            distanta[i][j] = 0;
        }
    }

    double dist_min = 999999;
    int x_nou;
    int y_nou;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k=0;k<numar_ierbivori;k++)
            {   ierbivor* c=v[k];
                int x_t = (pozitie_curenta_x - c->get_x() + j);
                int y_t = (pozitie_curenta_y - c->get_y() + i);
                distanta[i][j] += sqrt(x_t * x_t + y_t * y_t);
                if (motor.validxy(pozitie_curenta_x + j - 1, pozitie_curenta_y + i - 1) == 0)
                {
                    distanta[i][j] += 999999;
                }
                if (pozitie_curenta_x + j - 1 == c->get_x() && pozitie_curenta_y + i - 1 == c->get_y())
                {
                    distanta[i][j] = -999999;
                    break;
                }
            }
            if (distanta[i][j] <= dist_min)
            {
                dist_min = distanta[i][j];
                x_nou = j;
                y_nou = i;
            }
        }
    }
    if (x_nou != 1 || y_nou != 1)
    {
        if (motor.validxy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1))
        {
            unit *u = motor.get_unit_xy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1);
            if (u != NULL)
            {
                if (this->energie < this->energie_optima)
                    this->energie += 10;
                this->send_mes(100, u);
            }

            if (motor.get_unit_xy(pozitie_curenta_x + x_nou - 1, pozitie_curenta_y + y_nou - 1) == NULL)
                move_unit(x_nou - 1, y_nou - 1);
        }
    }
}

void carnivor::inmulteste()
{
    int contor = 0;
        int poz_curenta_i = unit::get_x();
        int poz_curenta_j = unit::get_y();
        for (int i = poz_curenta_i - 1; i <= poz_curenta_i + 1; ++i)
        {
            for (int j = poz_curenta_j - 1; j <= poz_curenta_j + 1; ++j)
            {
                if (j == poz_curenta_j && i == poz_curenta_i)
                {
                    continue;
                }
                if (contor == 1)
                {
                    break;
                }
                if (this->energie >= this->energie_optima - 10 && motor.validxy(i, j) == 1 && motor.get_unit_xy(i, j) == NULL)
                {
                    contor = 1;
                    new carnivor(i, j);
                    this->energie -= 20;
                }

            }
        }
    }


void carnivor::behaviour(int pm) {}

void *carnivor::get_tip()
{
    return &nume;
}
