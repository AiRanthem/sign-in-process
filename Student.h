#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;
class Student
{
private:
	int number;//编号
	int work_num;//工号
	int machine;//机号
	string stu_num;//学号
	string name;//姓名
	static int how_many;//学生人数
	int solid_attendance;//有效出勤次数
	bool attr_book[30][2];//签到表
public:
	Student();
	Student(const Student&);
	void setNumber(int);
	void setWorkNum(int);
	void setMachine(int);
	void setStuNum(string&);
	void setName(string&);
	int getNumber() const;
	int getWorkNum() const;
	int getMachine() const;
	int getSolidAttd() const;
	string getStuNum() const;
	string getName() const;
	static int howMany(); //获得人数
	static void addOne();//增加学生人数
	void attend(int,int);//签到
	bool check(int);//检查是否有效签到
};
#endif // !STUDENT_H
