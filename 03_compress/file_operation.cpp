#include "main.h"
#include <math.h>
#include <cstdio>

using namespace std;

int char_num(0); //出现不同字符数
int total_num(0); //总字符数
char artical[MAX_NUM], cmp_char[MAX_NUM];
struct Huffman_char huffman_char[256];
int buffer_num(0), buffer(0);

void read_ori_file(const char* file_name){
    //ifstream fin(file_name, ios::binary);
    //fin.read(artical, sizeof(char) * MAX_NUM);
    FILE *f;
    f = fopen(file_name, "r");
    for (int i(0), j(0); !feof(f); i++){
	fscanf(f, "%c", &artical[i]);
	for (j = 0; j < char_num; j++)
	    if (huffman_char[j].ch == artical[i]) break;
	huffman_char[j].count++;
	huffman_char[j].ch = artical[i];
	if (j == char_num) char_num++;
	total_num++;
    }
    struct Node tmp;
    for (int i = 0; i < char_num; i++){
	tmp.change_Node(huffman_char[i].count, huffman_char[i].ch);
	tmp.index = i;
	huffman_node.push(tmp); //将tmp压入Node类型优先队列中
    }
}

void store_to_file(string file_name){
    file_name += ".compress";
    const char* cmp_name = file_name.c_str();
    ofstream fout(cmp_name, ios::binary);

    fout.write((char*)&total_num, sizeof(int));
    fout.write((char*)&char_num, sizeof(int));
    for (int i(0); i < 2 * char_num - 1; i++){
	fout.write((char*)&huffman_tree[i].count, sizeof(int));
	fout.write((char*)&huffman_tree[i].index, sizeof(int));
	fout.write((char*)&huffman_tree[i].parent, sizeof(int));
	fout.write((char*)&huffman_tree[i].lchild, sizeof(int));
	fout.write((char*)&huffman_tree[i].rchild, sizeof(int));
	fout.write((char*)&huffman_tree[i].ch, sizeof(char));
    }
    buffer = 0;
    for (int i(0), j(0), k(0); i < total_num; i++){
	for (j = 0; j < char_num; j++)
	    if (artical[i] == huffman_char[j].ch) break;
	for (k = 0; k < huffman_char[j].bit_length; k++){
	    if (buffer_num == 7 || (i == total_num - 1 && huffman_char[j].bit_length - 1 == k)){
		char tmp = (char)buffer;
		fout.write((char*)&tmp, sizeof(char));
		//cout << buffer << endl;
		buffer_num = buffer = 0;
	    }
	    //cout << huffman_char[j].bit[k];
	    if (buffer_num == 0 && huffman_char[j].bit[k] == '0') buffer--;
	    buffer += pow((huffman_char[j].bit[k] - '0')* 2, buffer_num++);
	}
    }
}

void unzip(string file_name){
    const char* unzip_name = (file_name + ".unzip").c_str();
    const char* cmp_name = (file_name + ".compress").c_str();
    ofstream f_unzip(unzip_name, ios::binary);
    ifstream f_cmp(cmp_name, ios::binary);

    f_cmp.read((char*)&total_num, sizeof(int));
    f_cmp.read((char*)&char_num, sizeof(int));
    huffman_tree = (struct Node*)malloc((2 * char_num - 1) * sizeof(struct Node));
    for (int i(0); i < 2 * char_num - 1; i++){
	f_cmp.read((char*)&huffman_tree[i].count, sizeof(int));
	f_cmp.read((char*)&huffman_tree[i].index, sizeof(int));
	f_cmp.read((char*)&huffman_tree[i].parent, sizeof(int));
	f_cmp.read((char*)&huffman_tree[i].lchild, sizeof(int));
	f_cmp.read((char*)&huffman_tree[i].rchild, sizeof(int));
	f_cmp.read((char*)&huffman_tree[i].ch, sizeof(char));
    }
    char tmp_char;
    f_cmp.read((char*)&tmp_char, sizeof(char));
    int y = (int)tmp_char, m = (int)tmp_char;
    for (int i(0), idx(2 * char_num - 2), j(0); i < total_num; ){
	if (y != 0){
	    m = y % 2;
	    y /= 2;
	    j++;
	    if (m == 0){
		idx = huffman_tree[idx].lchild;
		//cout << "0";
	    }else{
		idx = huffman_tree[idx].rchild;
		//cout << "1";
	    }
	}else if (y == 0 && j < 7){
	    idx = huffman_tree[idx].lchild;
	    j++;
	    //cout << "0";
	}
	if (j == 7){
	    //cout << endl;
	    f_cmp.read((char*)&tmp_char, sizeof(char));
	    y = m = (int)tmp_char;
	    j = 0;
	}
	if (huffman_tree[idx].lchild == -1 && huffman_tree[idx].rchild == -1){
	    if (i >= total_num - 1) return;
	    f_unzip.write((char*)&huffman_tree[idx].ch, sizeof(char));
	    idx = 2 * char_num - 2;
	    i++;
	}
    }
}
