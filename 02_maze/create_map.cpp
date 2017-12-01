#include "data.h"

#define Rand(a, b) do{\
    do{\
	a = rand() % width * high;\
	b = rand() % width * high;\
    }while(a == b || a % 2 != 0 || b % 2 != 0);\
}while(0)
#define get_edge(edge) do{\
    do{\
	edge = rand() % (width * high);\
    }while(edge % 2 != 1 || map[edge] != 0);\
}while(0)
#define dig_point() do{\
	int p = edge / width % 2;\
	switch(p){\
	    case 0:\
		if (edge % width != 0 && edge % width != width - 1 && \
			(find_set(edge - 1) != find_set(edge + 1))){\
		    union_set(edge, edge - 1);\
		    union_set(edge, edge + 1);\
		    map[edge] = map[edge - 1] = map[edge + 1] = 1;\
		}\
		break;\
	    case 1:\
		if (edge / width != 0 && edge / width != high - 1 && \
			(find_set(edge - width) != find_set(edge + width))){\
		    union_set(edge, edge - width);\
		    union_set(edge, edge + width);\
		    map[edge] = map[edge - width] = map[edge + width] = 1;\
		}\
		break;\
	}\
}while(0)

using namespace std;

int map_began, map_end;
int map[MAX_WIDTH * MAX_HIGH] = {0};
int real_map[MAX_WIDTH][MAX_HIGH] = {0};

void init_create_map_data(void){
    for (int i = 0; i < width * high; i++){
	for (int j = 0; j < width * high; j++) real_map[i][j] = 0;
	map[i] = 0;
    }
}

void create_rand_map(int width, int high){
    srand((unsigned) time(NULL));
    Rand(map_began, map_end);
    map_began = 0, map_end = width * high - 1;
    int a = find_set(map_began);
    while(find_set(map_began) != find_set(map_end)){
	int edge;
	get_edge(edge);
	dig_point();
    }
    for (int i = 0; i < width * high * 0.1; i++){
	int edge;
	get_edge(edge);
	dig_point();
    }
    map[map_began] = 2;
    map[map_end] = 3;

    for (int i = 1; i <= high; i++)
	for (int j = 1; j <= width; j++)
	    real_map[i][j] = map[(i - 1) * width + (j - 1)];
}

void print_digital_map(void){
    for (int i = 0; i < real_high; i++){
	for (int j = 0; j < real_width; j++){
	    if (real_map[i][j] == 0) cout << "■";
	    else if (real_map[i][j] == 2) cout << "@";
	    else if (real_map[i][j] == 3) cout << "!";
	    else cout << " ";
	}
	cout << endl;
    }
}
