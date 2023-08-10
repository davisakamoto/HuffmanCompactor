#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>

#include "arvore.hpp"

std::string bin(char caractere) {
    return std::bitset<8>(caractere).to_string();
}

int main(int argc, char* argv[])
{
    //-------------------- DEFINE OS PARAMETROS PASSADOS NA LINHA DE COMANDO -----------------------------------
    std::string arqEntrada = argv[1];
    std::string arqSaida = argv[2];
    std::string comando = argv[3];

    //------------ CONFERE SE A QUANTIDADE DE ARGUMENTOS NA LINHA DE COMANDO É VÁLIDA --------------------------------------------
    if (argc < 4 || (comando != "-c" && comando != "-d")) 
    {
        std::cerr << "Usage: " << argv[0] << " <file1>" << " <file2>" << " -<flag>\n";
        std::cerr << "\tfile1: Arquivo de entrada, para compactar/descompactar\n";
        std::cerr << "\tfile2: Arquivo de saída, já compactado/descompactado\n";
        std::cerr << "\tflag: 'c' para compactar, 'd' para descompactar\n";
        return 1;
    }

    //----------------- ABRE ARQUIVO DE ENTRADA (ENCERRA O PROGRAMA CASO FALHE) -----------------------------------------------------
    std::ifstream arquivo1;
    arquivo1.open(arqEntrada);
    if(arquivo1.fail()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo de entrada\n";
        return -1;
    }

    //----------------- ABRE ARQUIVO DE SAÍDA (ENCERRA O PROGRAMA CASO FALHE) ------------------------------------------------------
    std::ofstream arquivo2;
    arquivo2.open(arqSaida, std::ios::binary);
    if(arquivo2.fail()) {
        std::cerr << "ERRO: Não foi possível abrir o arquivo de saída\n";
        return -1;
    }

    //---------------- DECLARAÇÕES QUE SÃO NECESSÁRIAS PARA OS DOIS CASOS --------------------------------------------------------
    int nCaracteres;
    std::string dict[256];
    std::string linha;
    std::string linhazip;
    Arvore* huff = new Arvore();
    
    //------------------------------- OPÇÃO DE COMPACTAÇÃO ----------------------------------------------------------------------------------------
    if(comando == "-c")
    {
        //CRIA UM VETOR PARA CONTAR AS OCORRÊNCIAS DE CADA CARACTERE E INICIALIZA SEUS VALORES COMO 0
        int caracteres[256];
        for (int i = 0; i < 256; i++)
            caracteres[i] = 0;

        //LÊ CADA CARACTERE DO ARQUIVO E AUMENTA SUA CONTAGEM NO VETOR  
        char caractere;
        try
        {
            while(arquivo1.get(caractere))
            {
                caracteres[caractere]++;
                if(caracteres[0] > 0) 
                    break;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "ERRO: Erro na leitura do arquivo\n";
            arquivo1.close();
            arquivo2.close();
            return -3;
        }

        //CONSTROI A ÁRVORE A PARTIR DAS FREQUÊNCIAS E GERA A SUA TABELA DICIONÁRIO
        huff->constroiHuffman(caracteres);
        huff->atualizaTabela(dict);

        //MOVE O PONTEIRO PARA O COMEÇO DO ARQUIVO PARA PERCORRÊ-LO NOVAMENTE
        arquivo1.clear();
        arquivo1.seekg(0);

        //PERCORRE O ARQUIVO CONSTRUINDO UMA STRING DE 0's e 1's BASEADO NO DICIONÁRIO
        try
        {
            while(arquivo1.get(caractere))
            {
                linhazip = linhazip + dict[caractere];
                nCaracteres++;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "ERRO: Erro na leitura do arquivo\n";
            arquivo1.close();
            arquivo2.close();
            return -3;
        }
        

        //MONTA O CABEÇALHO COM TAMANHO E TABELA (DICIONÁRIO)
        arquivo2 << nCaracteres << " ";
        for(int i = 0; i < 255; i++)
        {
            if(dict[i] != "")
                arquivo2 << i << " "  << dict[i] << " ";
        }
        arquivo2 << std::endl;

        //REESCREVE O TEXTO DE FORMA COMPACTADA
        for(int i = 0; i < linhazip.size(); i += 8)
        {
            char byte = 0;
            for(int j = 0; j < 8; j++)
            {
                if(i+j < linhazip.size())
                {
                    byte <<= 1;
                    byte |= linhazip[i+j] - '0';
                }
                else
                    byte <<= 1;
            }
            arquivo2 << byte;
        }
    }
    //---------------------------- OPÇÃO DE DESCOMPACTAÇÃO ------------------------------------------------------
    else if(comando == "-d")
    {
        //LÊ O CABEÇALHO E CONSTROI O DICIONÁRIO PARA OS CARACTERES
        std::getline(arquivo1, linha);
        std::istringstream fluxoString(linha);
        fluxoString >> nCaracteres;

        int letra;
        try
        {
            while(fluxoString >> letra)
            {
                fluxoString >> dict[letra];
            }
        }
        catch(const std::invalid_argument& ia)
        {
            std::cerr << "ERRO: Erro na leitura do arquivo\n";
            arquivo1.close();
            arquivo2.close();
            return -3;
        }

        //CONSTROI A ARVORE A PARTIR DA TABELA(DICIONÁRIO)
        huff->constroiTabela(dict);

        //LÊ O TEXTO RESTANTE (ARQUIVO COMPACTADO) E DESCOMPACTA UTILIZANDO A ARVORE DE HUFFMAN
        while(std::getline(arquivo1, linha))
        {
            linhazip += linha;
            linhazip += '\n';
        }

        //TRANSFORMA O TEXTO COMPACTADO EM UMA STRING DE BITS
        std::string linhabin = "";
        for(int i = 0; i < linhazip.size(); i ++)
        {
            linhabin += bin(linhazip[i]);
        }

        //REESCREVE O TEXTO ORIGINAL NO ARQUIVO DE SAÍDA
        huff->descompacta(&arquivo2, linhabin, nCaracteres);
        
    }

    //DESALOCA MEMÓRIA DOS OBJETOS
    delete huff;

    //FECHA OS ARQUIVOS
    arquivo1.close();
    arquivo2.close();

    return 0;
}