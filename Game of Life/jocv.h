#ifndef JOCV_H_INCLUDED
#define JOCV_H_INCLUDED
#include "engine.h"

class fiinta : public unit
{
private:
    static int nr_fiinte;

protected:
    int energie;
    int energie_optima;
    int timp_ramas;

private:
    void action();

protected:
    fiinta(int, int, int, int, int);
    ~fiinta();
    virtual int apara() = 0;
    virtual void mananca() = 0;
    virtual void inmulteste() = 0;
    virtual void behaviour(int) = 0;

public:
    static int get_nr_fiinte();
    int get_energie();
    virtual void *get_tip() = 0;
};

class planta : public fiinta
{
private:
    static unsigned char nume;

private:
    int apara();
    void mananca();
    void inmulteste();
    void behaviour(int);

public:
    planta(int, int);
    void *get_tip();
};
class ierbivor : public fiinta
{
private:
    static unsigned char nume;

private:
    int apara();
    void mananca();
    void inmulteste();
    void behaviour(int);

public:
    ierbivor(int, int);
    void *get_tip();
};
class carnivor : public fiinta
{
private:
    static unsigned char nume;

private:
    int apara();
    void mananca();
    void inmulteste();
    void behaviour(int);

public:
    carnivor(int, int);
    void *get_tip();
};

#endif // JOCV_H_INCLUDED
