#include "Student.h"
#include <string>
using namespace std;
void Student::setNumber(int n) { number = n; }
void Student::setWorkNum(int n) { work_num = n; }
void Student::setMachine(int n) { machine = n; }
void Student::setStuNum(string& n) { stu_num = n; }
void Student::setName(string& n) { name = n; }
int Student::getNumber() const { return number; }
int Student::getWorkNum() const { return work_num; }
int Student::getMachine() const { return machine; }
int Student::getSolidAttd() const { return solid_attendance; }
string Student::getStuNum() const { return stu_num; }
string Student::getName() const { return name; }
int Student::howMany() { return how_many; }
void Student::addOne() { ++how_many; }
Student::Student(const Student &o)
{
	number = o.number;
	work_num = o.work_num;
	machine = o.machine;
	stu_num = o.stu_num;
	name = o.name;
	solid_attendance = o.solid_attendance;
	for (int i = 0; i < 30; ++i)
	{
		attr_book[i][0] = o.attr_book[i][0];
		attr_book[i][1] = o.attr_book[i][1];
	}
}
Student::Student()
{
	number = 0;
	work_num = 0;
	machine = 0;
	stu_num = "0000";
	name = "YouKnowWho";
	solid_attendance = 0;
	for (int i = 0; i < 30; ++i)
	{
		attr_book[i][0] = 0;
		attr_book[i][1] = 0;
	}
}
bool Student::check(int when)
{
	if (attr_book[when][0] == 1 && attr_book[when][1] == 1)
	{
		solid_attendance += 1;
		return true;
	}
	return false;
}

void Student::attend(int which_day, int which_time)
{
	attr_book[which_day][which_time] = 1;
}

int Student::how_many = 0;