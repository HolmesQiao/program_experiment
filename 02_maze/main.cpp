#include "data.h"
#include <SFML/Audio.hpp>

using namespace std;

int _RANK_ = 7;
int map_rank = 0;
int width, high;
int real_width, real_high;
int Map_type;
sf::SoundBuffer buffer;
sf::Sound sound;

void draw_map(void);
void draw_cmd(void);

int main(int argc, char** argv){
    draw_cmd();
    buffer.loadFromFile("music.wav");
    sound.setBuffer(buffer);
    sound.play();
    new_game();
    
    glutInit(&argc, argv);
    draw_map();
    return 0;
}

void draw_map(void){
    init_gl();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(spinMap);
    //glutMouseFunc(mouseMotion);
    
    glutMainLoop();
}

void new_game(void){
    if (Map_type == by_algorithm){
	srand((unsigned) time(NULL));
	width = high = rand() % _RANK_ + 5;
	width += _RANK_ - 3;
	high += _RANK_ - 3;
	_RANK_ += 3;
	real_width = width, real_high = high;
	if (real_width % 2 == 1) width -= 2;
	else width -= 3;
	if (real_high % 2 == 1) high -= 2;
	else high -= 3;
    }else read_from_file();

    init_set(width, high);
    init_find_road_data();
    init_gl_data();

    if (Map_type == by_algorithm){
	init_create_map_data();
	create_rand_map(width, high);
	store_to_file();
    }
    find_road(0);
}

void draw_cmd(void){
    string cmd;
    system("clear");
    cout << "*****************迷宫游戏***************\n";
    cout << "*                功能列表              *\n";
    cout << "****************************************\n";
    cout << "*1.随机生成三维迷宫                    *\n";
    cout << "*2.自动存储迷宫数据                    *\n";
    cout << "*3.支持从文件导入迷宫                  *\n";
    cout << "*4.按键'w''s''a''d'控制玩家移动        *\n";
    cout << "*5.迷宫自动旋转                        *\n";
    cout << "*6.按键'x' 'y' 'z' 可以控制迷宫旋转    *\n";
    cout << "*7.按键'r'显示迷宫通路                 *\n";
    cout << "*8.按键'q'退出程序                     *\n";
    cout << "*9.文件导入的迷宫可支持无限关卡        *\n";
    cout << "*10.算法生成的迷宫有无限关卡           *\n";
    cout << "*11.拖动窗口迷宫不变形                 *\n";
    cout << "*12.增加光效                           *\n";
    cout << "****************************************\n";
    cout << "请输入迷宫来源(file/ algorithm/ quit)  *\n";
    while(1){
	cin >> cmd; cin.ignore(1000, '\n');
	if (cmd == "file"){
	    Map_type = from_file;
	    break;
	}
	else if (cmd == "algorithm"){
	    Map_type = by_algorithm;
	    break;
	}else if (cmd == "quit"){
	    exit(1);
	}else cout <<"Illegal input, try again!\n";
    }
}
