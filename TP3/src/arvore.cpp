#include "arvore.hpp"
#include <string>

Arvore::Arvore()
{
    raiz = NULL;
}

Arvore::~Arvore()
{
    limpa();
}

void Arvore::constroiHuffman(int* caracteres)
{
    Lista* nos = new Lista();

    for(int i = 0; i < 255; i++)
        if(caracteres[i] > 0)
            nos->insere(i, caracteres[i]);

    //VERIFICA SE HÁ APENAS UM OU NENHUM NÓ NA FILA E JÁ TERMINA A FUNÇÃO
    if(nos->getTamanho() == 1)
    {
        raiz = new No(-1, 0);
        raiz->esq = nos->removeInicio();
    }
    if(nos->getTamanho() == 0)
    {
        delete nos;
        return;
    }

    //EXECUTA O ALGORITMO DE HUFFMAN
    while(nos->getTamanho() > 1)
    {
        No* esquerda = nos->removeInicio();
        No* direita = nos->removeInicio();

        int freqAcumulada = esquerda->getFreq() + direita->getFreq();

        No* novoNo = new No(-1, freqAcumulada);

        novoNo->esq = esquerda;
        novoNo->dir = direita;

        nos->insereNo(novoNo);
    }

    raiz = nos->removeInicio();

    delete nos;
}

void Arvore::atualizaTabela(std::string* dict)
{
    std::string caminho = "";
    caminhoRecursivo(raiz, caminho, dict);
}

void Arvore::constroiTabela(std::string* dict)
{
    raiz = new No(-1, 0);

    for(int i = 0; i < 255; i++)
    {
        if(dict[i] != "")
        {
            insereRecursivo(raiz, i, dict[i], 0);
        }
    }
}

void Arvore::insereRecursivo(No* p, int caractere, std::string caminho, int nivel)
{
    if(caminho.size() > nivel)
    {
        if(caminho[nivel] == '0')
        {
            if(p->esq == NULL)
            {
                No* novoNo;
                if(caminho.size() > nivel + 1)
                    novoNo = new No(-1, 0);  
                else 
                    novoNo = new No(caractere, 0);
                p->esq = novoNo;
            }
            insereRecursivo(p->esq, caractere, caminho, nivel + 1);
        }
        else if(caminho[nivel] == '1')
        {
            if(p->dir == NULL)
            {
                No* novoNo;
                if(caminho.size() > nivel + 1)
                    novoNo = new No(-1, 0);  
                else 
                    novoNo = new No(caractere, 0);
                p->dir = novoNo;
            }
            insereRecursivo(p->dir, caractere, caminho, nivel + 1);
        }
    }
}

void Arvore::caminhoRecursivo(No *p, std::string caminho, std::string* dict)
{
    if(p!=NULL)
    {
        caminhoRecursivo(p->esq, caminho + "0", dict);

        if(p->caractere >= 0)
        {
            dict[p->caractere] = caminho;
        }

        caminhoRecursivo(p->dir, caminho + "1", dict);
    }
}

void Arvore::descompacta(std::ofstream *arquivo, std::string zip, int nCaracteres)
{
    int i = 0, size = zip.size();
    while(i < size && nCaracteres > 0)
    {
        No* p = raiz;
        while(p->getItem() < 0)
        {
            if(zip[i] == '0')
                p = p->esq;
            else if(zip[i] == '1')
                p = p->dir;
            i++;
        }
        *arquivo << char(p->getItem());
        nCaracteres--;
    }
}

void Arvore::limpa()
{
    apagaRecursivo(raiz);
    raiz = NULL;
}


void Arvore::apagaRecursivo(No *p)
{
    if(p!=NULL){
        apagaRecursivo(p->esq);
        apagaRecursivo(p->dir);
        delete p;
    }
}