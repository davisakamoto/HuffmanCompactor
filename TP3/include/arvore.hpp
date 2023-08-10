#ifndef ARVORE_H
#define ARVORE_H

#include <fstream>
#include "lista.hpp"

class Arvore
{
    public:
        Arvore();
        ~Arvore();

        void limpa();
        void constroiHuffman(int* caracteres);
        void constroiTabela(std::string* dict);
        void atualizaTabela(std::string* dict);
        void descompacta(std::ofstream* arquivo, std::string zip, int nCaracteres);

    private:
        //void dump(No* p, int altura);
        void insereRecursivo(No* p, int caractere, std::string caminho, int nivel);
        void apagaRecursivo(No* p);
        void caminhoRecursivo(No* p, std::string caminho, std::string* dict);
        
        No *raiz;
};

#endif
