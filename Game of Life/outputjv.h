#ifndef OUTPUTJV_H_INCLUDED
#define OUTPUTJV_H_INCLUDED
#include "engine.h"
#include "jocv.h"

class output
{
private:
    engine *motor;

public:
    output(engine *pm);
    void init();
    void close();
    void afisare();
};

#endif // OUTPUTJV_H_INCLUDED
