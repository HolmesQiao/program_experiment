#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#define MAX_NUM 50000

//store ASCII char data
struct Huffman_char{
    Huffman_char();
    Huffman_char(char ch);
    char ch;//字符
    int count;//频数
    char bit[1000];//存huffman编码
    int bit_length;//编码长度
    bool operator < (const Huffman_char& A)const;
};
struct Node{
    Node();
    void change_Node(int count, char ch);
    int count;
    char ch;
    int index;
    int parent, lchild, rchild;
    bool operator < (const Node &A)const;
};
extern int char_num;
extern struct Huffman_char huffman_char[256];
extern struct Node* huffman_tree;
//extern struct Node *huffman_tree;

//file_operation
void read_ori_file(const char* file_name);
void store_to_file(std::string file_name);
void unzip(std::string file_name);

//huffman_tree
extern std::priority_queue <Node>huffman_node;

void build_huffman_tree(void);
void get_huffman_code(int idx, std::string tmp);
