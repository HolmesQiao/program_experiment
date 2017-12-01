#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "myconio_mac.h"

using namespace std;

const int MAX_DATA_NUM = 1000;
const int FIND = 0; const int INSERT = 1;
const int CHANGE = 2;
const int DELETE = 3;
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
}hash_table[MAX_DATA_NUM];

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
void display_all_person();
void search_hash(std::string name, int ope);
void collsion_key(int key, std::string name, int ope);
int get_string_key(std::string name);
void draw_api();
inline void display_person(){ search_hash(input_name(), FIND); }
inline void insert_person(){ search_hash(input_name(), INSERT); }
inline void change_data(){ search_hash(input_name(), CHANGE); }
inline void delete_person(){ search_hash(input_name(), DELETE); }

int main(void){
    system("clear");
    cout << "===================Welcom==================" << endl;
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
	    case '6': return 0;
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
    //system("clear");
    cout << endl << "------------Command list-------------" << endl;
    cout << "1 :find person" << endl;
    cout << "2 :new person" << endl;
    cout << "3 :change data" << endl;
    cout << "4 :delete person" << endl;
    cout << "5 :display all data" << endl;
    cout << "6 :exit" << endl;
    cout << "-----------------------------------" << endl;
}

int get_string_key(std::string name){
    int key = 0;
    for (int i = 0; i < name.size(); i++){
	key += name[i] - 'a';
    }
    key %= MAX_DATA_NUM;

    return key;
}

void search_hash(std::string name, int ope){
    int key = get_string_key(name);

    if (hash_table[key].get_name() == "\0"){
	switch(ope){
	    case FIND: 
		std::cout << "Sorry, we didn't find this person, do you wanna store it?(y/n) ";
		char cmd;
		std::cin >> cmd;
		if (cmd == 'y')
		    hash_table[key].new_person(name); 
		else if (cmd == 'n') ;
		else cout << "Illegal input\n";
		break;
	    case INSERT: 
		   hash_table[key].new_person(name);
		   break;
	    case CHANGE:
		std::cout << "Sorry, we didn't find this person, do you wanna store it?(y/n) ";
		std::cin >> cmd;
		if (cmd == 'y')
		    hash_table[key].new_person(name); 
		else if (cmd == 'n') ;
		else cout << "Illegal input\n";
		break;
	    case DELETE:
		std::cout << "Sorry, this person is not exist" << std::endl;
	}
    }
    else if (hash_table[key].get_name() == name){
	switch(ope){
	    case FIND: hash_table[key].display(); break;
	    case INSERT: 
		       std::cout << "The person is already exist, do you still wanna store?(y/n)";
		       char cmd;
		       std :: cin >> cmd;
		   if (cmd == 'y')
		       hash_table[key].new_person(name);
		   else if (cmd == 'n') ;
		   else cout << "Illegal command\n";
		   break;
	    case CHANGE:
		   char command;
		   std::cout << "What do you wanna change?(P/A)";
		   std::cin >> command;
		   command = toupper(command);
		   if (command == 'P'){
		       std::cout << "Inter the new phone number: ";
		       long long phone_num;
		       std::cin >> phone_num;
		       hash_table[key].change_phone_num(phone_num);
		   }
		   else if (command == 'A'){
		       std::cout << "Inter the new adress: ";
		       std::string adress;
		       std::cin >> adress;
		       hash_table[key].change_adress(adress);
		   }
		   else cout << "Illegal commmand.\n";
		   break;
	    case DELETE:
		   hash_table[key].change_name("\0");
	}
    }
    else collsion_key(key, name, ope);
}

void collsion_key(int key, std::string name, int ope){
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
