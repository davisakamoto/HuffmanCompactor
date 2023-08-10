#ifndef LISTA_H
#define LISTA_H

#include "no.hpp"

class Lista
{
    public:
        Lista();
        ~Lista();

        int getTamanho();
        int getItem(int pos);
        int getFreq(int pos);
        bool vazia();

        void insere(int item, int freq);
        void insereNo(No* n);
        No* removeInicio();
        void limpa();


    protected:
        int tamanho;
        No* first;
        No* end;
        No* posiciona(int pos, bool antes);
};

#endif