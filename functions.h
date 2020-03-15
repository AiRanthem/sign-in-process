#ifndef F
#define F
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Student.h"
using namespace std;
void SplitString(const string&, vector<string>&, const string);
bool get_students_info(vector<Student>&);
int isValid(int, int, int, int, int);
int get_attendance_data(vector<Student>&);
void show_ui();
void refresh();
bool go_back();
void show_everyone(vector<Student>&);
void er_than_percent(vector<Student>&, bool&);
void inquire(vector<Student>&, bool&);
void inquire_by_workn(vector<Student>&);
void inquire_by_stun(vector<Student>&);
void inquire_by_name(vector<Student>&);
#endif // !F

