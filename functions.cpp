#include "functions.h"
//字符串分隔函数
void SplitString(const string& s, vector<string>& vec, const char splitor)
{
	string::size_type pos1, pos2; //存放子字符串起始位置的下表
	pos2 = s.find(splitor); //找到第一个分隔符
	pos1 = 0;
	while (string::npos != pos2) //find函数如果没有找到则返回npos，所以用这个来判断是否找到了所有的分隔符
	{
		vec.push_back(s.substr(pos1, pos2 - pos1)); //提取子字符串
		pos1 = pos2 + 1; 
		pos2 = s.find(splitor, pos1); //重新定向两个定位符
	}
	if (pos1 != s.length()) // 判断最后一个定位符后是否还有内容
		vec.push_back(s.substr(pos1));
}

//获取学生信息
bool get_students_info(vector<Student>& vec)
{
	ifstream csv;
	csv.open("data\\students.csv", ios::in);
	if (!csv.is_open())
		return false;
	string student;
	csv.seekg(31, ios::beg);//跳过第一行
	while (getline(csv, student))
	{
		vector<string> informations;
		SplitString(student, informations, ',');
		Student who;
		who.setNumber(atoi(informations[0].c_str()));
		who.setWorkNum(atoi(informations[1].c_str()));
		who.setMachine(atoi(informations[2].c_str()));
		who.setStuNum(informations[3]);
		who.setName(informations[4]);
		vec.push_back(who);
		Student::addOne();
	}
	csv.close();
	return true;
}

//判断签到是否有效 0:无效,1:签到,2:签退
int isValid(int day, int month, int hour, int minute, int n)
{
	if (n < 0 || n>26) return 0;//不在名单
	if (month == 6 && day < 20) return 0;//日期提前
	if (month == 7 && day > 14) return 0;//日期延后
	if (hour == 7) return 1;
	if (hour == 8 && minute <= 15) return 1;//有效签到
	if (hour == 11 && minute >= 25) return 2;//有效签退
	return 0;
}// 由于去年太多人是在8点前签到的，可能去年的规则和今年是不一样，为了数据好看我把七点也设为有效

//进行签到数据统计	
int get_attendance_data(vector<Student>& vec)
{
	fstream dat;
	dat.open("data\\1_attlog.dat", ios::in);
	string data;
	regex date_pattern("\\d{4}-\\d{2}-\\d{2}");
	regex time_pattern("\\d{2}:\\d{2}:\\d{2}");
	//提取字符串
	while (getline(dat, data))
	{
		sregex_iterator time_iter(data.begin(), data.end(), time_pattern);
		sregex_iterator date_iter(data.begin(), data.end(), date_pattern);
		int day = atoi(date_iter->str().substr(8, 2).c_str());
		int month = atoi(date_iter->str().substr(5, 2).c_str());
		int hour = atoi(time_iter->str().substr(0, 2).c_str());
		int minute = atoi(time_iter->str().substr(3, 2).c_str());
		int num;
		if (data[7] == ' ')
			num = atoi(data.substr(8, 1).c_str()) - 5;
		else
			num = atoi(data.substr(7, 2).c_str()) - 5;
		//提取数据
		int day_n = (month == 6) ? day - 20 : day + 10;//第几天
		int valid = isValid(day, month, hour, minute, num);
		if (valid == 1)
			vec[num].attend(day_n, 0);
		else if (valid == 2)
		{
			vec[num].attend(day_n, 1);
			vec[num].check(day_n);
		}
	}
	dat.close();
	return 0;
}

//简单UI
void show_ui()
{
	cout << "#########################################################################################################" << endl
		<< "#########################################################################################################" << endl
		<< "#### #####       ##       ##     ####       ###  ##### ##     ####### #####  ##### ####     ###       ###" << endl
		<< "### # ####### ######## ##### #### ### ######### # #### ## #### ##### # #### # #### ### ######## #########" << endl
		<< "## ### ###### ######## ##### ##### ##      #### ## ### ## ##### ### ### ### ## ### ## #########      ####" << endl
		<< "#       ##### ######## ##### ##### ## ######### ### ## ## ##### ##       ## ### ## ## ######### #########" << endl
		<< "# ##### ##### ######## ##### #### ### ######### #### # ## #### ### ##### ## #### # ### ######## #########" << endl
		<< "# ##### ##### ######## #####     ####       ### #####  ##     #### ##### ## #####  ####     ###       ###" << endl
		<< "#########################################################################################################" << endl
		<< "#########################################################################################################" << endl
		<< endl
		<< "                          WELCOME TO USE MY ATTENDANCE DATA ANALYSIS SYSTEM!" << endl
		<< "                                              功能列表：" << endl
		<< "                          press 1 : 查看每个同学有效出勤次数" << endl
		<< "                          press 2 : 查看出勤率高于某百分比或低于某百分比的学生" << endl
		<< "                          press 3 : 考勤情况查询" << endl
		<< "                          press 0 : 退出程序" << endl
		;
}

//刷新页面
void refresh()
{
	system("cls");
	show_ui();
}

//功能结束
bool go_back()
{
	cout << endl << "是否回到主界面？（Y/N）" << endl;
	char cmd;
	while(true)
	{
		cin >> cmd;
		if (cmd == 'y' || cmd == 'Y') return true;
		else if (cmd == 'n' || cmd == 'N')
		{
			cout << "Bye!!" << endl;
			_getch();
			_getch();
			return false;
		}
	}
}

//功能1：显示每个人的有效出勤次数
void show_everyone(vector<Student>& stu)
{
	system("cls");
	for (auto iter = stu.begin(); iter != stu.end(); ++iter)
		cout << iter->getName() << " :" << iter->getSolidAttd() << endl;
	if (go_back())
		return;
	else
		exit(0);
}

//功能2：出勤率高于或低于某百分比
void er_than_percent(vector<Student>& stu, bool &came)
{
	system("cls");
	string cmd;
	double all = 25;
	cout << "请输入指令，格式如 \"<10%\" \">20%\"，支持一行输入多个条件，系统会分别列举查询结果。" << endl;
	if (came)
	{
		getline(cin, cmd);
	}
	getline(cin, cmd);
	regex td_pat("[<>]\\d{1,2}%");
	for (sregex_iterator td_it(cmd.begin(), cmd.end(), td_pat), end; td_it != end; ++td_it)
	{
		double ti = atof(td_it->str().substr(1, td_it->str().length() - 2).c_str());
		cout << "满足出勤率 " << td_it->str() << " 的学生如下：" << endl;
		if (td_it->str()[0] == '<')
		{
			for (auto iter = stu.begin(); iter != stu.end(); ++iter)
				if (double(iter->getSolidAttd()) / all < ti / 100.)
					cout << iter->getName() << ':' << 100 * double(iter->getSolidAttd()) / all << '%' << endl;
			cout << endl;
		}
		else
		{
			for (auto iter = stu.begin(); iter != stu.end(); ++iter)
				if (double(iter->getSolidAttd()) / all > ti / 100.)
					cout << iter->getName() << ':' << 100 * double(iter->getSolidAttd()) / all << '%' << endl;
			cout << endl;
		}
	}
	if (go_back())
		return;
	else
		exit(0);
}

//功能3：考勤情况查询
void inquire(vector<Student>& stu, bool &came)
{
	system("cls");
	cout << "请选择查询方式:" << endl
		<< "press 1 : 考勤号" << endl
		<< "press 2 : 学号" << endl
		<< "press 3 : 姓名" << endl;
	char cmd;
	while (true)
	{
		cmd = _getch();
		switch (cmd)
		{
			case '1': {inquire_by_workn(stu); break; }
			case '2': {inquire_by_stun(stu); break; }
			case '3': {inquire_by_name(stu); break; }
		}
		if (cmd == '1' || cmd == '2' || cmd == '3')
			break;
	}
	if (go_back())
		return;
	else
		exit(0);
}

//按工号查询
void inquire_by_workn(vector<Student>& stu)
{
	system("cls");
	cout << "请输入考勤号/工号" << endl;
	int n;
	cin >> n;
	n -= 5;
	if (n >= 0 && n <= 26)
		cout << "查询结果：" << endl
		<< "姓名:    " << stu[n].getName() << endl
		<< "考勤号:  " << stu[n].getWorkNum() << endl
		<< "学号:    " << stu[n].getStuNum() << endl
		<< "机号:    " << stu[n].getMachine() << endl
		<< "考勤次数: " << stu[n].getSolidAttd() << endl << endl;
	else
		cout << "抱歉，没有这个学生" << endl;
}
//按学号查询
void inquire_by_stun(vector<Student>& stu)
{
	system("cls");
	bool found = false;
	cout << "请输入学号" << endl;
	string stn;
	int n;
	cin >> stn;
	for (auto iter = stu.begin(); iter != stu.end(); ++iter)
		if (iter->getStuNum() == stn)
		{
			found = true;
			n = iter->getNumber() - 1;
		}
	if(found)
		cout << "查询结果：" << endl
		<< "姓名:    " << stu[n].getName() << endl
		<< "考勤号:  " << stu[n].getWorkNum() << endl
		<< "学号:    " << stu[n].getStuNum() << endl
		<< "机号:    " << stu[n].getMachine() << endl
		<< "考勤次数: " << stu[n].getSolidAttd() << endl << endl;
	else
		cout << "抱歉，没有这个学生" << endl;
}
//按姓名查询
void inquire_by_name(vector<Student>& stu)
{
	system("cls");
	bool found = false;
	cout << "请输入姓名" << endl;
	string stn;
	int n;
	cin >> stn;
	for (auto iter = stu.begin(); iter != stu.end(); ++iter)
		if (iter->getName() == stn)
		{
			found = true;
			n = iter->getNumber() - 1;
		}
	if (found)
		cout << "查询结果：" << endl
		<< "姓名:    " << stu[n].getName() << endl
		<< "考勤号:  " << stu[n].getWorkNum() << endl
		<< "学号:    " << stu[n].getStuNum() << endl
		<< "机号:    " << stu[n].getMachine() << endl
		<< "考勤次数: " << stu[n].getSolidAttd() << endl << endl;
	else
		cout << "抱歉，没有这个学生" << endl;
}