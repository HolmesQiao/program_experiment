#include "data.h"

int set_father[MAX_WIDTH * MAX_HIGH] = {0}, set_rank[MAX_WIDTH * MAX_HIGH] = {0};
void init_set(int width, int high){
    for (int i = 0; i < width * high; i++) set_father[i] = i;
}

int find_set(int a){
    int root = a;
    while (root != set_father[root]) root = set_father[root];
    while (set_father[a] != root){
	int tmp = set_father[a];
	set_father[a] = root;
	a = tmp;
    }

    return root;
}

void union_set(int a, int b){
    int root_a = find_set(a), root_b = find_set(b);
    if (set_rank[root_a] <= set_rank[root_b]){
	set_father[root_a] = root_b;
	if (set_rank[root_a] == set_rank[root_b]) set_rank[root_b]++;
    }else
	set_father[root_b] = root_a;
}
