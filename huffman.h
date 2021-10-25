// Nome: Sirlenon de Araujo Macedo

// This constant can be avoided by explicitly calculating height of Huffman Tree
#define MAX_TREE_HT 100

typedef unsigned char byte;

// A Huffman tree node
struct MinHeapNode
{
    unsigned char data;  // One of the input characters
    unsigned freq;  // Frequency of the character
    struct MinHeapNode *left, *right; // Left and right child of this node
};

// A Min Heap:  Collection of min heap (or Hufmman tree) nodes
struct MinHeap
{
    unsigned size;    // Current size of min heap
    unsigned capacity;   // capacity of min heap
    struct MinHeapNode **array;  // Attay of minheap node pointers
};

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
