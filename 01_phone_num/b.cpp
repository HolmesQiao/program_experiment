#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "myconio_mac.h"

#define Null()\
case FIND: \
std::cout << "Sorry, we didn't find this person, do you wanna store it?(y/n) ";\
char cmd;\
std::cin >> cmd;\
if (cmd == 'y'){\
hash_table[key].new_person(name);\
add_phone(hash_table[key]);}\
else if (cmd == 'n') ; \
else cout << "Illegal input\n";\
break;\
case INSERT:\
hash_table[key].new_person(name);\
add_phone(hash_table[key]);\
break;\
case CHANGE: std::cout << "Sorry, we didn't find this person, do you wanna store it?(y/n) ";\
std::cin >> cmd;\
if (cmd == 'y'){\
hash_table[key].new_person(name);\
add_phone(hash_table[key]);}\
else if (cmd == 'n');\
else cout << "Illegal input\n"; break;\
case DELETE:\
std::cout << "Sorry, this person is not exist" << std::endl; break;

#define Exist()\
case FIND: hash_table[key].display(); break;\
case INSERT:\
std::cout << "The person is already exist, do you still wanna store?(y/n)";\
char cmd;\
std :: cin >> cmd;\
if (cmd == 'y'){\
delete_phone(hash_table[key]);\
hash_table[key].new_person(name);\
add_phone(hash_table[key]);}\
else if(cmd == 'n') ;\
else cout << "Illegal command\n";\
break;\
case CHANGE:\
char command;\
std::cout << "What do you wanna change?(P/A)";\
std::cin >> command;\
command = toupper(command);\
if (command == 'P'){\
delete_phone(hash_table[key]);\
std::cout << "Inter the new phone number: ";\
add_phone(hash_table[key]);\
long long phone_num;\
std::cin >> phone_num;\
hash_table[key].change_phone_num(phone_num);\
}\
else if (command == 'A'){\
std::cout << "Inter the new adress: ";\
std::string adress;\
std::cin >> adress;\
hash_table[key].change_adress(adress);\
}\
else cout << "Illegal commmand.\n";\
break;\
case DELETE: hash_table[key].change_name("\0");\
delete_phone(hash_table[key]);


using namespace std;

const int MAX_DATA_NUM = 1000;
const int FIND = 0;
const int INSERT = 1;
const int CHANGE = 2;
const int DELETE = 3;
const int hash_time = 40;
char collsion_type;
class person_data{
    public:
	person_data(person_data *next = NULL, long long phone_num = 0, std::string name = "\0"){
	    this->phone_num = phone_num;
	    this->name = name;
	    this->next = next;
	}
	void change_phone_num(long long phone_num){this->phone_num = phone_num;}
	void change_name(std::string name){this->name = name;}
	void change_adress(std::string adress){this->adress = adress;}
	void display();
	void new_person(std::string name);
	long long get_phone_num(){return phone_num;}
	std::string get_name(){return name;}
	std::string get_adress(){return adress;}
	person_data *next;
    private:
	long long phone_num;
	std::string name;
	std::string adress;
}hash_table[MAX_DATA_NUM], phone_table[MAX_DATA_NUM];

void person_data::display(){
    std::cout << std::endl << "========================" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Phone_num: " << phone_num << std::endl; 
    std::cout << "Adress: " << adress;
    std::cout << std::endl << "========================" << std::endl << std::endl;
}

void person_data::new_person(std::string name){
    this->name = name;
    std::cout << "Phone number: ";
    std::cin >> this->phone_num; 
    cin.ignore(1023, '\n');
    std::cout << "Adress: ";
    std::cin >> this->adress;
    cin.ignore(1023, '\n');
}

inline std::string input_name(){
    std::string name;
    std::cout << "Input the person's name: ";
    std::cin >> name;
    cin.ignore(1023, '\n');

    return name;
}
int search_phone(long long phone_num){
    int i = 0, key = phone_num % 997;
    for (; phone_table[key].get_phone_num() != phone_num && (i++) < 996; key++){}
    if (phone_table[key].get_phone_num() != phone_num) return -1;
    return key;
}
void add_phone(person_data person){
    int i = 0, key = person.get_phone_num() % 997;
    for (; phone_table[key].get_phone_num() != 0 && (i++) < 996; key = (key + 1) % 997){}
    phone_table[key] = person;
}
void delete_phone(person_data person){
    int key = search_phone(person.get_phone_num());
    phone_table[key].change_phone_num(0);
}
void display_phone(){
    long long phone_num;
    cout << "Input phone num: ";
    cin >> phone_num;
    cin.ignore(1023, '\n');
    int key = search_phone(phone_num);
    if (key == -1) cout << "We did not find a person use this phone num\n";
    else phone_table[key].display();
}

void display_all_person();
void search_hash(std::string name, int ope, char collsion_type);
void search(string name, char collsion_type, int ope);
void collsion_key_1(int key, std::string name, int ope);
int collsion_key_2(int key, string name); 
int collsion_key_3(int key, string name);
int get_string_key(std::string name);
void draw_api();
void seach(string name);
inline void display_person(){ search_hash(input_name(), FIND, collsion_type); }
inline void insert_person(){ search_hash(input_name(), INSERT, collsion_type); }
inline void change_data(){ search_hash(input_name(), CHANGE, collsion_type); }
inline void delete_person(){ search_hash(input_name(), DELETE, collsion_type); }

int main(void){
    system("clear");
    cout << "===================Welcom==================" << endl;
    while(1){ 
	cout << "请选择一种处理冲突的方法:(1:拉链法, 2:线性探测再散列, 3:二次探测再散列): ";
	cin >> collsion_type;
	cin.ignore(1023, '\n');
	if (collsion_type > '3' || collsion_type < '1'){
	    cout << "1";
	    cout << "Illegal command, input again!\n";
	    continue;
	}
	else break;
    }
    for(;;){
	char command;

	cout << "===========================================" << endl; cout << "Please input command:(Input '0' for help): ";
	cin >> command;
	cin.ignore(1023, '\n');
	switch(command){
	    case '0': draw_api(); break;
	    case '1': display_person(); break;
	    case '2': insert_person(); break;
	    case '3': change_data(); break;
	    case '4': delete_person(); break;
	    case '5': display_all_person(); break;
	    case '6': if (collsion_type != '1') display_phone(); else cout << "当前冲突处理不能使用此功能\n"; break;
	    case '7': return 0;
	    default: cout << "Illegal input, input again.\n"; break;
	}
	if (command > '6' || command < '0')	continue;
	cout << "Enter any key to continue.";
	getch();
	system("clear");
    }

    return 0;
}

void draw_api(){
    cout << endl << "------------Command list-------------" << endl;
    cout << "1 :查询联系人" << endl;
    cout << "2 :新建联系人" << endl;
    cout << "3 :改变信息" << endl;
    cout << "4 :删除联系人" << endl;
    cout << "5 :显示所有人" << endl;
    cout << "6 :通过电话号码查询人(仅在后两种冲突处理时可用)" << endl;
    cout << "7 :退出" << endl;
    cout << "-----------------------------------" << endl;
}

int get_string_key(string name) {
    int key = 0;
    for (int i = 0; i < name.size(); i++)
	key += name[i] - 'a';
    key %= MAX_DATA_NUM;
    return key;
}


void search_hash(std::string name, int ope, char collsion_type){
    int key = get_string_key(name);

    if (hash_table[key].get_name() == "\0"){
	switch(ope){
	    Null()
	}
    }
    else if (hash_table[key].get_name() == name){
	switch(ope){
	    Exist()
	}
    }
    else{
	if (collsion_type == '1') collsion_key_1(key, name, ope);
	else search(name, collsion_type, ope);
    }
}

void collsion_key_1(int key, std::string name, int ope){
    person_data *p = &hash_table[key];
    for (;;){
	if (p->next != NULL){
	    if (p->next->get_name() == name){
		switch(ope){
		    case FIND:  p->next->display(); break;
		    case INSERT: 
			std::cout << "The person is already exist, do you still wanna store?(y/n)";
		       char cmd;
		       std :: cin >> cmd;
			cin.ignore(1023, '\n');
		       if (cmd == 'y')
			   p->next->new_person(name);
		       else if (cmd == 'n') ;
		       else cout << "Illegal command\n";
		       break;
		    case CHANGE: 
			char command;
			std::cout << "what do you wanna change?(P/A)";
			std::cin >> command;
			cin.ignore(1023, '\n');
			command = toupper(command);
			if (command == 'P'){
			   std::cout << "Inter the new phone number: ";
			   long long phone_num;
			   std::cin >> phone_num;
			    cin.ignore(1023, '\n');
			   p->next->change_phone_num(phone_num);
			}
			if (command == 'A'){
			   std::cout << "Inter the new adress: ";
			   std::string adress;
			   std::cin >> adress;
			    cin.ignore(1023, '\n');
			   p->next->change_adress(adress);
			}
		    case DELETE: p->next = p->next->next; break;
		}
		break;
	    }
	}
	else {
	    person_data new_person;

	    if (ope == FIND){
		std::cout << "Sorry, we didn't find this person, do you wanna store it?(y/n) ";
		char cmd;
		std::cin >> cmd;
		cin.ignore(1023, '\n');
		if (cmd != 'y')
		    return;
	    }
	    if (ope == FIND || ope == INSERT){
		new_person.new_person(name);
		p->next = &new_person;
		return;
	    }
	    std::cout << "Sorry, we didn't find this person" <<std::endl;
	}
	p = p->next;
    }
}

void search(string name, char collsion_type, int ope){
    int key = get_string_key(name);
    switch(collsion_type){
	case '2': key = collsion_key_2(key, name); break;
	case '3': key = collsion_key_3(key, name); break;
    }
    
    if (hash_table[key].get_name() == "\0"){
	switch(ope){
	    Null()
	}
    }
    else {
	switch(ope){
	    Exist()
	}
    }
}

int collsion_key_2(int key, string name){
    for (;hash_table[key].get_name() != name; key = (key + 1) % 1000){
	if (hash_table[key].get_name() == "\0") break;
    }
    return key;
}
int collsion_key_3(int key, string name){
    int m = hash_time * hash_time;
    int k = key;
    for (int i = 1; hash_table[key].get_name() != name; k = (key + i) % 1000){
	k = key;
	if (hash_table[k].get_name() == "\0") break;
    }
    return k;
}

void display_all_person(){
    for (int i = 0; i < MAX_DATA_NUM; i++){
	if (hash_table[i].get_name() != "\0"){
	    hash_table[i].display();
	    person_data *p = hash_table[i].next;
	    while(p != NULL){
		p->display();
		p = p->next;
	    }
	}
    }
}
