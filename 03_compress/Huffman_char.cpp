#include "main.h"

Huffman_char::Huffman_char(){
    ch = '\0';
    count = 0;
    bit_length = 0;
}
Huffman_char::Huffman_char(char ch){
    this->ch = ch;
    count = 0;
    bit_length = 0;
}
bool Huffman_char:: operator < (const Huffman_char& A)const{
    return A.count < count;
}
