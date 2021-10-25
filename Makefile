# Nome: Sirlenon de Araujo Macedo

CC =  gcc
CFLAGS = -std=c99

all:
	gcc compactador.c huffman.c -o meucompactador $(CFLAGS)
	gcc descompactador.c huffman.c -o meudescompactador $(CFLAGS)

clean:
	$(RM) meudescompactador meucompactador
