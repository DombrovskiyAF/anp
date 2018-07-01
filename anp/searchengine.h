#ifndef SEARCHENGINE
#define SEARCHENGINE

#include "anppdusequence.h"

class SearchEngine : public AnpPduSequence
{
public:
    SearchEngine();
    ~SearchEngine();

    void constSearch(int max_lenght);
    void countSearch(int max_lenght);

};

#endif // SEARCHENGINE

