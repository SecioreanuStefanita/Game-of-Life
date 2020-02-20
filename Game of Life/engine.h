#ifndef ENIGNE_H_INCLUDED
#define ENIGNE_H_INCLUDED
#define MAXNC 100
#define MAXNL 100
#define MAXNU 100 * 100
#define MAXNM 100

class unit;
class engine
{
    friend class unit;
    unit *unittab[MAXNC][MAXNL];
    unit *unitvect[MAXNU];
    int nc, nl, nu;

public:
    void init(int, int);
    int get_nl();
    int get_nc();
    int get_nu();
    int validxy(int, int);
    int validpoz(int);
    unit *get_unit_xy(int, int);
    unit *get_unit_poz(int);
    void next();
};

class unit
{
    friend class engine;

public:
    static engine motor;

private:
    int alive;
    int x, y, poz;
    int message[MAXNM];
    int nm;

private:
    void react();

protected:
    unit(int, int);
    virtual ~unit(){};
    void die();
    void move_unit(int, int);
    void send_mes(int, unit *);
    virtual void action() = 0;
    virtual void behaviour(int) = 0;

public:
    int get_x();
    int get_y();
    virtual void *get_tip() = 0;
};

#endif // ENIGNE_H_INCLUDED
