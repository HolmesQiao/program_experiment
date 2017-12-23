#include <iostream>
#include <cstdlib>

using namespace std;

int main(void){
    FILE *f_1, *f_2;
    f_1 = fopen("main.txt", "r");
    f_2 = fopen("main.txt.unzip", "r");
    if (f_1 == NULL || f_2 == NULL)
	return 0;

    while(!feof(f_1)){
	char c_1 = fgetc(f_1);
	char c_2 = fgetc(f_2);
	if (c_1 != c_2){
	    cout << "Different" << c_1 << c_2 << endl;
	    return 0;
	}
    }
    if (feof(f_2)) cout << "Same\n";
    else cout << "Different_end\n";

    return 0;
}
