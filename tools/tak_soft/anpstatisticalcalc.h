#ifndef ANPSTATISTICALCALC_H
#define ANPSTATISTICALCALC_H

#include "../../anp/anppdusequence.h"
#include "../../anp/anppdu.h"

class AnpStatisticalCalc
{
public:
    AnpStatisticalCalc();

    int doSomething(AnpPduSequence *pduSeq);
};

#endif // ANPSTATISTICALCALC_H
