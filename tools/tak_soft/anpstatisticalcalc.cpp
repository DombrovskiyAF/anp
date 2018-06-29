#include "anpstatisticalcalc.h"

AnpStatisticalCalc::AnpStatisticalCalc()
{
}

int AnpStatisticalCalc::doSomething(AnpPduSequence *pduSeq)
{
    pduSeq->printAttr();
}
