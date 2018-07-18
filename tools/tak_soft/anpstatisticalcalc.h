#ifndef ANPSTATISTICALCALC_H
#define ANPSTATISTICALCALC_H

#include "../../anp/anppdusequence.h"
#include "../../anp/anppdu.h"

class AnpStatisticalCalc
{
public:
    AnpStatisticalCalc();

    void constSearch(AnpPduSequence *pduSeq, int max_lenght);
    void countSearch(AnpPduSequence *pduSeq, int max_lenght);
    void bitConstSearch(AnpPduSequence *pduSeq, int max_lenght);
    void sizeFilter (AnpPduSequence *pduSeq);
};

#endif // ANPSTATISTICALCALC_H
