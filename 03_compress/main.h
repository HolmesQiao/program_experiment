#include <fstream>
#include <iostream>

//store ASCII char data
struct Huffman_char{
    char ch;
    int count;
    int bit[20];
    int bit_length;
};

struct Node{
    Node();
    float p;
    char data;
    int parent, lchild, rchild;
};

//file_operation
void read_ori_file(const char* file_name);
