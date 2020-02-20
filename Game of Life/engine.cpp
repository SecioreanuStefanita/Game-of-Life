
#include <stddef.h>
#include "engine.h"
#include <iostream>

engine unit::motor;
void engine::init(int nc, int nl)
{
    this->nc = nc;
    this->nl = nl;
    for (int i = 0; i < nl; ++i)
    {
        for (int j = 0; j < nc; ++j)
        {
            unittab[i][j] = NULL;
        }
    }
}
int engine::get_nc()
{
    return this->nc;
}
int engine::get_nl()
{
    return this->nl;
}
int engine::get_nu()
{
    return this->nu;
}
int engine::validxy(int poz_linie, int poz_coloana)
{
    if ((poz_coloana >= 0 && poz_coloana <= nc - 1) && (poz_linie >= 0 && poz_linie <= nl - 1))
    {
        return 1;
    }
    else
        return 0;
}
int engine::validpoz(int poz)
{
    if (poz >= 0 && poz <= nu - 1)
    {
        return 1;
    }
    else
        return 0;
}
unit *engine::get_unit_xy(int poz_linie, int poz_coloana)
{
    if (validxy(poz_linie, poz_coloana) == 0)
        return NULL;
    if (unittab[poz_linie][poz_coloana] == NULL)
    {
        return NULL;
    }
    else
        return unittab[poz_linie][poz_coloana];
}
unit *engine::get_unit_poz(int poz)
{
    return unitvect[poz];
}

void engine::next()
{
    for (int i = 0; i < this->get_nu(); ++i)
    {
        unitvect[i]->action();
    }
    for (int j = 0; j < this->get_nu(); ++j)
    {
        unitvect[j]->react();
    }
    for (int i = 0; i < get_nu(); ++i)
    {
        if (unitvect[i]->alive == 0)
        {
            unittab[unitvect[i]->x][unitvect[i]->y] = NULL;
            delete unitvect[i];
            for (int j = i; j < nu - 1; j++)
            {
                unitvect[j] = unitvect[j + 1];
            }
            --nu;
            --i;
        }
    }
}

void unit::react()
{
    if (this->alive != 0)
    {
        for (int i = 0; i < nm; i++)
        {
            this->behaviour(this->message[i]);
        }
        this->nm = 0;
    }
}

unit::unit(int x, int y)
{
    if (false) //motor.unittab[x][y]!=NULL||motor.get_nu()==MAXNU)
    {
    }
    else
    {
        motor.unitvect[motor.get_nu()] = this;
        motor.unittab[x][y] = this;
        this->x = x;
        this->y = y;
        this->nm = 0;
        this->alive = 1;
        unit::motor.nu++;
    }
}

void unit::die()
{
    this->alive = 0;
}

void unit::send_mes(int pm, unit *pu)
{
    if (pu->nm == MAXNM)
    {
    }
    else
    {
        pu->message[pu->nm] = pm;
        pu->nm++;
    }
}
void unit::move_unit(int dx, int dy)
{
    motor.unittab[x + dx][y + dy] = motor.unittab[x][y];
    motor.unittab[x][y] = NULL;
    x += dx;
    y += dy;
}

int unit::get_x()
{
    return this->x;
}
int unit::get_y()
{
    return this->y;
}
