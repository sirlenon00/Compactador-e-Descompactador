// Nome: Sirlenon de Araujo Macedo 

#include <stdio.h>
#include <stdlib.h>

#include "huffman.h"

void LeFrequenciaBytes(FILE *entrada, unsigned int *listaBytes)
{

    byte c;

    while (fread(&c, 1, 1, entrada) >= 1)
    {
        listaBytes[(byte)c]++;
    }

    rewind(entrada); // "rebobina o arquivo"

}

int pegaCodigo(struct MinHeapNode *n, byte c, char *buffer, int tamanho)
{

    // Caso base da recursão:
    // Se o nó for folha e o seu valor for o buscado, colocar o caractere terminal no buffer e encerrar

    if (!(n->left || n->right) && n->data == c)
    {
        buffer[tamanho] = '\0';
        return 1;
    }
    else
    {
        int encontrado = 0;

        // Se existir um nó à esquerda
        if (n->left)
        {
            // Adicione '0' no bucket do buffer correspondente ao 'tamanho' nodeAtual
            buffer[tamanho] = '0';

            // fazer recursão no nó esquerdo
            encontrado = pegaCodigo(n->left, c, buffer, tamanho + 1);
        }

        if (!encontrado && n->right)
        {
            buffer[tamanho] = '1';
            encontrado = pegaCodigo(n->right, c, buffer, tamanho + 1);
        }
        if (!encontrado)
        {
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }

}

void comprime(const char *arquivoEntrada, const char *arquivoSaida){
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

    LeFrequenciaBytes(entrada, listaBytes);

    struct MinHeapNode* raiz = buildHuffmanTree(data, listaBytes, 256);

    fwrite(listaBytes, 256, sizeof(listaBytes[0]), saida);
    fseek(saida, sizeof(unsigned int), SEEK_CUR);

    byte c;
    unsigned tamanho = 0;
    byte aux = 0;

    while (fread(&c, 1, 1, entrada) >= 1)
    {

        // Cria um buffer vazio
        char buffer[1024] = {0};

        // Busca o código começando no nó 'raiz', utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket deste último
        pegaCodigo(raiz, c, buffer, 0);

        // Laço que percorre o buffer
        for (char *i = buffer; *i; i++)
        {
            // Se o caractere na posição nodeAtual for '1'
            if (*i == '1')
            {
                // 2 elevado ao resto da divisão de 'tamanho' por 8
                // que é o mesmo que jogar um '1' na posição denotada por 'tamanho % 8'
                //aux = aux + pow(2, tamanho % 8);
                aux = aux | (1 << (tamanho % 8));
            }

            tamanho++;

            // Já formou um byte, é hora de escrevê-lo no arquivo
            if (tamanho % 8 == 0)
            {
                fwrite(&aux, 1, 1, saida);
                // Zera a variável auxiliar
                aux = 0;
            }
        }
    }

    fwrite(&aux, 1, 1, saida);

    // Move o ponteiro do stream para 256 vezes o tamanho de um unsigned int, a partir do início dele (SEEK_SET)
    fseek(saida, 256 * sizeof(unsigned int), SEEK_SET);

    // Salva o valor da variável 'tamanho' no arquivo saida
    fwrite(&tamanho, 1, sizeof(unsigned), saida);

    fclose(entrada);
    fclose(saida);
}


int main(int argc, char* argv[])
{
    comprime(argv[1],"saida_compactada.txt");
    return 0;
}
