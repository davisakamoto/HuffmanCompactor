#include "lista.hpp"

Lista::Lista() {
    tamanho = 0;
    first = new No(-1, -1);
    end = first;
}

Lista::~Lista()
{
    limpa();
    delete first;
}

int Lista::getTamanho()
{
    return tamanho;
}

bool Lista::vazia()
{
    return tamanho == 0;
}

No* Lista::posiciona(int pos, bool antes=false){
    No *p; int i;

    if ( (pos > tamanho) || (pos <= 0) )
        throw "ERRO: Posicao Invalida!";

    // Posiciona na célula anterior a desejada
    p = first;
    for(i=1; i<pos; i++){
        p = p->prox;
    }
    // vai para a próxima 
    // se antes for false
    if(!antes)
        p = p->prox;

    return p;
}

int Lista::getItem(int pos){
    No *p;

    p = posiciona(pos);
    return p->caractere;
}

int Lista::getFreq(int pos){
    No *p;

    p = posiciona(pos);
    return p->freq;
}

void Lista::insere(int item, int freq) 
{
    No* novoNo = new No(item, freq);

    if(tamanho == 0 || end->freq <= freq)
    {
        end->prox = novoNo;
        end = novoNo;
    }
    else
    {
        No *p = first;
        while(p != end && (p->prox)->freq <= freq)
            p = p->prox;

        novoNo->prox = p->prox;
        p->prox = novoNo;

        if(novoNo->prox == NULL)
            end = novoNo;
    }

    tamanho++;
}

void Lista::insereNo(No* novoNo) 
{
    if(tamanho == 0 || end->freq <= novoNo->getFreq())
    {
        end->prox = novoNo;
        end = novoNo;
    }
    else
    {
        No *p = first;
        while(p != end && (p->prox)->freq <= novoNo->getFreq())
            p = p->prox;

        novoNo->prox = p->prox;
        p->prox = novoNo;

        if(novoNo->prox == NULL)
            end = novoNo;
    }

    tamanho++;
}

No* Lista::removeInicio() 
{
    No* p;

    if (tamanho == 0)
        throw "ERRO: Lista vazia!";

    p = first->prox;
    first->prox = p->prox;
    tamanho--;
    if(first->prox == NULL)
        end = first;

    return p;
}

void Lista::limpa() {
    No *p;

    p = first->prox;
    while (p!=NULL) {
        first->prox = p->prox;
        delete p;
        p = first->prox;
    }
    end = first;
    tamanho = 0;
}


