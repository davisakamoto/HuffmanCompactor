#include "no.hpp"

No::No(int c, int f)
{
    caractere = c;
    freq = f;
    esq = NULL;
    dir = NULL;
}

int No::getItem()
{
    return caractere;
}

int No::getFreq()
{
    return freq;
}

void No::setFreq(int f)
{
    freq = f;
}