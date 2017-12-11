#include "main.h"
#include <string>

using namespace std;

void read_ori_file(const char* file_name){
    ifstream fin(file_name);
    string artical;
    fin >> artical;
    cout << artical;
}
