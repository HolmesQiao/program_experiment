#include "main.h"

Node::Node(){
    p = 0;
    data = '\0';
    parent = lchild = rchild = -1;
}

struct Huffman_char huffman_char[256];
struct Node *huffman_tree;
