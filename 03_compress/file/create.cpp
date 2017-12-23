#include <iostream>
#include <time.h>
#include <cstdio>
#include <math.h>

using namespace std;

int main(int argc, char* argv[]){
    if (argc == 1) return 0;

    int num(0);
    FILE *f;
    f = fopen("main.txt", "w");
    for (int i = strlen(argv[1]) - 1; i + 1; i--)
	num += pow(10, strlen(argv[1]) - (i + 1));
    srand((unsigned) time(NULL));
    for (int i = 0; i < num * 100; i++)
	fprintf(f, "%c", (char)rand() % 127);

    return 0;
}
