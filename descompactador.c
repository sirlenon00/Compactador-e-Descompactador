// Nome: Sirlenon de Araujo Macedo

#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"



int geraBit(FILE *entrada, int posicao, byte *aux )
{
    (posicao % 8 == 0) ? fread(aux, 1, 1, entrada) : NULL == NULL ;

    return !!((*aux) & (1 << (posicao % 8)));
}

void descomprimir(const char *arquivoEntrada, const char *arquivoSaida){
    unsigned listaBytes[256] = {0};
    unsigned char data[256] = {0};
    FILE *entrada = fopen(arquivoEntrada, "rb");
    FILE *saida = fopen(arquivoSaida, "wb");

    for (int i = 0; i < 256; i++){
        data[i] = (byte) i;
    }

    if(entrada == NULL || saida==NULL){
        printf("Erro na abertura de um ou mais arquivos");
        exit(-1);
    }

    fread(listaBytes, 256, sizeof(listaBytes[0]), entrada);

    struct MinHeapNode* raiz = buildHuffmanTree(data, listaBytes, 256);

    unsigned tamanho;
    fread(&tamanho, 1, sizeof(tamanho), entrada);

    unsigned posicao = 0;
    byte aux = 0;

    // Enquanto a posicao for menor que tamanho
    while (posicao < tamanho)
    {
        // Salvando o nodeArvore que encontramos
        struct MinHeapNode *nodeAtual = raiz;

        // Enquanto nodeAtual não for folha
        while ( nodeAtual->left || nodeAtual->right )
        {
            nodeAtual = geraBit(entrada, posicao++, &aux) ? nodeAtual->right : nodeAtual->left;
        }

        fwrite(&(nodeAtual->data), 1, 1, saida);
    }

    fclose(entrada);
    fclose(saida);
}

int main(int argc, char* argv[])
{
    descomprimir(argv[1],"saida_descompactada.txt");
    return 0;
}
