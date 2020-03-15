#include "functions.h"
#include "Student.h"
using namespace std;
int main()
{
	vector<Student> students;//按照编号顺序存储学生信息的向量
	get_students_info(students);
	get_attendance_data(students);
	show_ui();
	char cmd;
	cmd = _getch();
	bool again = 0;
	while (cmd != '0')
	{
		switch (cmd)
		{
			case '1': {show_everyone(students); break; }
			case '2': {er_than_percent(students, again); break; }
			case '3': {inquire(students, again); break; }
		}
		refresh();
		cmd = _getch();
		if (!again) again = true;
	}
	cout << "Bye!!" << endl;
	_getch();
	_getch();
	return 0;
}


