#include "data.h"

void store_to_file(void){
    FILE* file;
    file = fopen("maze_data.txt", "a+");
    fprintf(file, "%d %d %d %d\n", real_width, real_high, width, high);
    for (int i = 0; i < real_high; i++){
	for (int j = 0; j < real_width; j++)
	    fprintf(file, "%d ", real_map[i][j]);
	fprintf(file, "\n");
    }
}

void read_from_file(void){
    FILE* file;
    file = fopen("maze_data.txt", "r");
    if (!file){
	fclose(file);
	std::cout << "File is not exist\n";
	exit(1);
    }
    for (int i = 0; i < map_rank; i++){
	int tmp_width, tmp_high, tmp;
	if (feof(file)) exit(1);
	fscanf(file, "%d%d", &tmp_width, &tmp_high);
	if (feof(file)) exit(1);
	for (int j = 0; j < tmp_width * tmp_high + 2; j++)
	    fscanf(file, "%d", &tmp);
	if (fgetc(file) == EOF) exit(1);
    }
    if (map_rank) fgetc(file);
    if (fscanf(file, "%d%d%d%d", &real_width, &real_high, &width, &high) == EOF) exit(1);
    int in = 0;
    for (int i = 0; i < real_high; i++){
	for (int j = 0; j < real_width; j++){
	    int tmp;
	    if (i == 0 || j == 0 || j > width || i > high){
		fscanf(file, "%d", &tmp);
		continue;
	    }else fscanf(file, "%d", &map[in++]);
	}
    }
    map_rank++;
    in = 0;
    for (int i = 0; i < real_high; i++){
	for (int j = 0; j < real_width; j++){
	    if (i == 0 || j == 0 || j > width || i > high){
		real_map[i][j] = 0;
	    }else real_map[i][j] = map[in++];
	}
    }
    fclose(file);
}
