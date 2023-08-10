#ifndef NO_H
#define NO_H

#include <iostream>

class No
{
    public:
        No(int c, int f);
        int getFreq();
        int getItem();
        void setFreq(int f);

    private:
        int caractere;
        int freq;
        No *esq;
        No *dir;
        No *prox;

    friend class Arvore;
    friend class Lista;
};

#endif