#include <cstdlib>
#include <time.h>
#include <iostream>
#include <GLUT/glut.h>
#include <cstdio>

#define MAX_WIDTH 100
#define MAX_HIGH 100
#define from_file 0
#define by_algorithm 1

/*set*/
void init_set(int width, int high);
extern int set_father[MAX_WIDTH * MAX_HIGH], set_rank[MAX_WIDTH * MAX_HIGH];
/*map*/
extern int map[MAX_WIDTH * MAX_HIGH];
extern int real_map[MAX_WIDTH][MAX_HIGH];
extern int map_began, map_end;
extern GLint position;
/*main*/
extern int width, high;
extern int real_width, real_high;
extern int _RANK_;
extern int map_rank;
extern GLfloat window_width, window_high;
extern int Map_type;
/*find_path*/
extern int path[MAX_WIDTH * MAX_HIGH];
extern int path_length;

//set
int find_set(int a);
void union_set(int a, int b);
//map
void create_rand_map(int width, int high);
void print_digital_map(void);
//draw
void init_gl(void);
void display(void);
void spinMap(void);
//void mouseMotion(int x, int y);
void reshape(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
//find road
void display_road(int began);
void find_road(int began);
//main
void new_game(void);
//init data
void init_find_road_data(void);
void init_create_map_data(void);
void init_gl_data(void);
//file
void store_to_file(void);
void read_from_file(void);
