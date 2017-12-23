#include "main.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc == 3){
	//string file_name = "file/main.txt";
	string file_name = argv[1];
	const char* File_name = file_name.c_str();
	string tmp = "";

	if (!strcmp("compress", argv[2])){
	    read_ori_file(File_name);
	    build_huffman_tree();
	    get_huffman_code(2 * char_num - 2, tmp);
	    /*for (int i = 0; i < char_num; i++){
		cout << huffman_char[i].ch; 
		for (int j = 0; j < huffman_char[i].bit_length; j++)
		    cout << huffman_char[i].bit[j];
		cout << endl;
	    }*/
	    store_to_file(file_name);
	}else if (!strcmp("unzip", argv[2])){
	    unzip(file_name);
	}else{
	    cout << "Illegal command\n";
	}
    }

    return 0;
}
