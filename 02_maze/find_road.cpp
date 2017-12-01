#include "data.h"

using namespace std;

int path[MAX_WIDTH * MAX_HIGH];
int graph[MAX_WIDTH * MAX_HIGH][MAX_WIDTH * MAX_HIGH] = {0};
int b[MAX_WIDTH * MAX_HIGH] = {0};
int ard_vzt[MAX_WIDTH * MAX_HIGH] = {0};
int queue[MAX_WIDTH * MAX_HIGH];
int front = 0, rear = 0;
int size = 1;
int path_length = 0;

void init_find_road_data(void){
    for (int i = 0; i < width * high; i++){
	for (int j = 0; j < width * high; j++) graph[i][j] = 0;
	b[i] = 0;
	ard_vzt[i] = 0;
    }
    front = 0, rear = 0;
    size = 1;
    path_length = 0;
}

void display_road(int began){
    for (int i = width * high - 1;;){
	path[path_length++] = b[i];
	i = b[i];
	if (i == began) break;
    }
}

void find_road(int began){
    //init
    front = 0, rear = 0;
    size = 1;
    b[began] = began;
    for (int i = 0; i < high; i++){
	for (int j = 0; j < width; j++){
	    if (map[i * width + j] == 0) continue;
	    if (i != high - 1 && map[i * width + j] != 0 && map[i * width + j + width] != 0)
		graph[i * width + j][i * width + j + width] = graph[i * width + j + width] [i * width + j] = 1;
	    if (j != width - 1 && map[i * width + j] != 0 && map[i * width + j + 1] != 0)
		graph[i * width + j][i * width + j + 1] = graph[i * width + j + 1][i * width + j] = 1;
	    if (i == j)
		graph[i][j] = 1;
	}
    }
    if (graph[width * high - 2] == 0){
	graph[width * high - 1][width * high - 2] = graph[width * high - 2][width * high - 1] = 1;
    }

    queue[front] = began;
    map_began = 0;
    ard_vzt[began] = 1;
    for (;;){
	if (size == 0){
	    cout << "There is no path\n";
	    break;
	}
	for (int j = 0; j < width * high; j++){
	    if (ard_vzt[j] == 1) continue;
	    if (graph[queue[front]][j] == 1){
		queue[++rear] = j;
		ard_vzt[j] = 1;
		b[j] = queue[front];
		size++;
		if (queue[rear] == width * high - 1){
		    display_road(began);
		    return;
		}
	    }
	}
	front++;
	size--;
    }
}
