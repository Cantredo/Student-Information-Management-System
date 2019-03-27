#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <windows.h>
#include <set>

using namespace std ;

const int maxNumberOfStudent = 100005 ;

struct studentMeassage{
	string m_id ;
    string m_name ;
    string m_sex ;
    string m_age ;
    string m_profession ;
};

bool cmpByID(studentMeassage data_one , studentMeassage data_two){
	if (data_one.m_id.length() == data_two.m_id.length()){
		return data_one.m_id < data_two.m_id ;
	}
	return data_one.m_id.length() < data_two.m_id.length() ;
}

bool cmpByAge(studentMeassage data_one , studentMeassage data_two){
	if (data_one.m_age.length() == data_two.m_age.length()){
		return data_one.m_age < data_two.m_age ;
	}
	return data_one.m_age.length() < data_two.m_age.length() ;
}

bool cmpByFirstLetterOfName(studentMeassage data_one , studentMeassage data_two){
	return data_one.m_name < data_two.m_name ;
}

bool cmpByFirstLetterOfProfession(studentMeassage data_one , studentMeassage data_two){
	return data_one.m_profession < data_two.m_profession ;
}

class Student{
private:
	int m_count ;
	map<string , bool> checkMeassage ;
	map<string , int> checkProfession ;
	// set<string> checkProfession ;
	studentMeassage data[maxNumberOfStudent] ;
	// vector<studentMeassage> data;
public:
	Student();
	int enterAndInsertMeassage(studentMeassage newinfo) ;
	int deleteMeassageByName(string name) ;
	int modifyMeassageByName(string name) ;
	bool searchMeassageByProfession(string profession) ;
	void searchMeassageByName(string name) ;
	void displayMenu(int menu) ;
	void displayMeassage(int index) ;
	void displayAllMeassage() ;
	void displayAllProfession() ;
	bool displayMeassageByID(string id) ;
	void sortByID() ;
	void saveInsideTxt() ;
	bool isContinue() ;
	bool checkMcount() ;
	bool checkIsEsc(string instr) ;
	int extendedSort(int way) ;
	int extendedDelete(int way) ;
	int extendedQuery(int way) ;
	/*
	extended function
	 */
};

Student::Student(){
	m_count = 0 ;
	ifstream fin("StudentRead.txt") ;
	if (fin){
		int tot_student ;
		fin >> tot_student ;
		for (int i = 0 ; i < tot_student ; i ++){
			fin >> data[m_count].m_id >> data[m_count].m_name >> data[m_count].m_sex >> data[m_count].m_age >> data[m_count].m_profession ;
			checkMeassage[data[m_count].m_id] = true ;
			checkProfession[data[m_count].m_profession] ++ ;
			m_count ++ ;
		}
		fin.close() ;
	}else{
		cout << "failed" << endl ;
	}
}

void Student::saveInsideTxt(){
	ofstream fout("StudentWrite.txt") ;
	if (fout){
		fout << m_count << endl ;
		fout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
		for (int i = 0 ; i < m_count ; i ++){
			fout << data[i].m_id << "\t" << data[i].m_name << "\t\t" << data[i].m_sex << "\t\t" << data[i].m_age << "\t\t" << data[i].m_profession << endl ;
		}
		fout.close() ;
	}else{
		cout << "failed" << endl ;
	}
	return ;
}

bool Student::checkMcount(){
	if (m_count == 0){
		return true ;
	}
	return false ;
}

void Student::displayMeassage(int index){
	cout << data[index].m_id << "\t" << data[index].m_name << "\t\t" << data[index].m_sex << "\t\t" << data[index].m_age << "\t\t" << data[index].m_profession << endl ;
	return ;
}

int Student::enterAndInsertMeassage(studentMeassage newinfo){

	/*
	if (m_count >  maxNumberOfStudent){ -> OK
		cout << "enter failure,error: full!" << endl ;
		return ;
	}
	check if the ID is duplicated -> OK
	*/

	if (m_count > maxNumberOfStudent){
		cout << "输入失败,学生信息管理库已满!" << endl ;
		return 1 ;
	}

	// for (int i = 0 ; i < m_count ; i ++){
	// 	if (newinfo.m_id == data[i].m_id){
	// 		return false ;
	// 	}
	// }

	if (checkMeassage[newinfo.m_id] == true){
		cout << "输入失败,此学号已存在,请检查后重新输入!" << endl ;
		return 2 ;
	}
	checkMeassage[newinfo.m_id] = true ;
	checkProfession[newinfo.m_profession] ++ ;
	data[m_count ++] = newinfo ;

	// vector
	// data.push_back(newinfo) ;

	return 0 ;
}

void Student::searchMeassageByName(string name){
	for (int i = 0 ; i < m_count ; i ++){
		if (data[i].m_name.compare(name) == 0){
			displayMeassage(i) ;
		}
	}
	return ;
}

bool Student::checkIsEsc(string instr){
	transform(instr.begin() , instr.end() , instr.begin() , ::toupper) ;
	if (instr.compare("ESC") == 0){
		return true ;
	}
	return false ;
}

/*
考虑按名字搜寻信息，然后此处更改为按 ID 和 name 删除，避免重名的情况，或者进行选择
1->以前述方式只删掉一个，2->删掉所有同名的 , 3->显示同名人的信息 , 4->quit
 */
int Student::deleteMeassageByName(string name){

	/*
	if (m_count == 0){
		cout << "deleteMeassage failure,error: empty!" << endl ;
		return ;
	}

	consider the same name
	*/

	if (checkMcount() == true){
		cout << "删除失败,学生信息管理库已空!" << endl ;
		return 1 ;
	}
	bool check_name = false ;
	for (int i = 0 ; i < m_count ; i ++){
		if (data[i].m_name == name){
			check_name = true ;
			break ;
		}
	}
	if (check_name == false){
		cout << "未找到姓名为 " << name << " 的同学信息,请检查后重新输入(输入 \"Esc\" 返回主菜单)" << endl ;
		return 2 ;
	}
	displayMenu(2) ;
	int selectWay ;
	while (cin >> selectWay){
		bool checkReturnPreviousMenu = false ;
		if (selectWay == 1){
			cout << "请输入学号(输入 \"Esc\" 返回上一层菜单):" << endl ;
			string id ;
			while (cin >> id){
				if (checkIsEsc(id) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				bool check_id = false ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_id.compare(id) == 0){
						check_id = true ;
						break ;
					}
				}
				if (check_id == false){
					cout << "此学号不存在请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				bool check_idIsMatch = false ;
				int index = -1 ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_id.compare(id) == 0 && data[i].m_name.compare(name) == 0){
						index = i ;
						check_idIsMatch = true ;
						break ;
					}
				}
				if (check_idIsMatch == true){
					checkProfession[data[index].m_profession] -- ;
					for (int i = index ; i < m_count - 1 ; i ++){
						data[i] = data[i + 1] ;
					}
					m_count -- ;
					break ;
				}else{
					cout << "学号和姓名不匹配,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
			}
		}else if (selectWay == 2){
			int index = -1 ;
			int index_pre = 0 ;
			while (m_count > 0){
				bool end_while = true ;
				for (int i = index_pre ; i < m_count ; i ++){
					if (data[i].m_name == name){
						index = i ;
						end_while = false ;
						break ;
					}
				}
				if (end_while == true){
					break ;
				}
				index_pre = index - 1 ;
				checkProfession[data[index].m_profession] -- ;
				for (int i = index ; i < m_count - 1 ; i ++){
					data[i] = data[i + 1] ;
				}
				m_count -- ;
			}
		}else if (selectWay == 3){
			cout << "同名学生信息如下:" << endl << endl ;
			displayMenu(4) ;
			searchMeassageByName(name) ;
			cout << endl << endl ;
		}else if (selectWay == 4){
			cout << endl << "即将返回主菜单" << endl ;
			Sleep(1000) ;
			// system("cls") ;
			displayMenu(1) ;
			return 1 ;
		}
		if (checkReturnPreviousMenu == true){
			displayMenu(2) ;
			continue ;
		}
		if (selectWay == 3){
			cout << endl ;
			system("pause") ;
			cout << endl ;
			displayMenu(2) ;
		}else if (selectWay == 1 || selectWay == 2){
			break ;
		}else{
			cout << "输入错误，请重新输入:" << endl ;
		}
	}
	return 0 ;
}

int Student::modifyMeassageByName(string cur_name){

	/*
	consider the same name -> OK
	*/
	if (checkMcount() == true){
		cout << "修改失败,学生信息管理库已空" << endl ;
		return 1 ;
	}
	int index = -1 ;
	bool check_name = false ;
	for (int i = 0 ; i < m_count ; i ++){
		if (data[i].m_name.compare(cur_name) == 0){
			check_name = true ;
			index = i ;
			break ;
		}
	}
	if (check_name == false){
		cout << "未找到姓名为 " << cur_name << " 的同学信息,请检查后重新输入" << endl ;
		return 2 ;
	}
	cout << endl ;
	cout << "找到姓名为" << cur_name << "的信息" << endl << endl ;
	displayMenu(4) ;
	displayMeassage(index) ;
	system("pause") ;
	displayMenu(3) ;
	int choice ;
	while (cin >> choice){
		bool checkReturnPreviousMenu = false ;
		string id , name , sex , profession , age ;
		switch (choice){
			case 1:
				cout << "请输入修改后的学号(输入 \"Esc\" 返回上一层菜单):" << endl ;
				while (cin >> id){
					if (checkIsEsc(id) == true){
						checkReturnPreviousMenu = true ;
						cout << endl ;
						break ;
					}
					if (checkMeassage[id] == true){
						cout << "此学号已存在，请重新输入:" << endl ;
						continue ;
					}
					break ;
				}
				checkMeassage[data[index].m_id] = false ;
				data[index].m_id = id ;
				checkMeassage[data[index].m_id] = true ;
				break ;
			case 2:
				cout << "请输入修改后的姓名(输入 \"Esc\" 返回上一层菜单):" << endl ;
				cin >> name ;
				if (checkIsEsc(name) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_name = name ;
				break ;
			case 3:
				cout << "请输入修改后的性别(输入 \"Esc\" 返回上一层菜单):" << endl ;
				cin >> sex ;
				if (checkIsEsc(sex) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_sex = sex ;
				break ;
			case 4:
				cout << "请输入修改后的年龄(输入 \"Esc\" 返回上一层菜单):" << endl ;
				cin >> age ;
				if (checkIsEsc(age) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_age = age ;
				break ;
			case 5:
				cout << "请输入修改后的专业(输入 \"Esc\" 返回上一层菜单):" << endl ;
				cin >> profession ;
				if (checkIsEsc(profession) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_profession = profession ;
				break ;
			case 6:
				cout << "请按学号、姓名、性别、年龄、专业的顺序进行输入，以空格分隔(输入 \"Esc\" 返回上一层菜单):" << endl ;
				while (cin >> id){
					cin >> name >> sex >> age >> profession ;
					if (checkIsEsc(id) == true){
						checkReturnPreviousMenu = true ;
						cout << endl ;
						break ;
					}
					if (checkMeassage[id] == true){
						cout << "学号已存在，请重新输入:" << endl ;
						continue ;
					}
					break ;
				}
				data[index].m_id = id ;
				data[index].m_name = name ;
				data[index].m_sex = sex ;
				data[index].m_age = age ;
				data[index].m_profession = profession ;
				break ;
			case 7:
				// cout << "即将返回主菜单" << endl ;
				// Sleep(1000) ;
				// system("cls") ;
				// displayMenu(1) ;
				// break ;
				return 1 ;
			default:
				cout << "输入错误，请重新输入" << endl ;
		}
		if (checkReturnPreviousMenu == true){
			displayMenu(3) ;
			continue ;
		}
		cout << "修改成功,修改后的信息为:" << endl << endl ;
		displayMeassage(index) ;
		cout << endl ;
		system("pause") ;
		bool check_samename = false ;
		for (int i = index + 1 ; i < m_count ; i ++){
			if (data[i].m_name.compare(cur_name) == 0){
				index = i ;
				check_samename = true ;
				break ;
			}
		}
		int select = 0 ;
		if (check_samename == true){
			cout << endl << "检测到同名，信息为:" << endl ;
			displayMeassage(index) ;
			cout << endl << "是否继续更改此同学的信息？(Yes/No)" << endl ;
			string selectAnwser ;
			while (cin >> selectAnwser){
				if (selectAnwser.compare("Yes") == 0){
					displayMenu(3) ;
					select = 1 ;
					break ;
				}else if (selectAnwser.compare("No") == 0){
					select = 2 ;
					break ;
				}else{
					cout << "输入错误，请重新输入" << endl ;
					continue ;
				}
			}
		}
		if (select == 1){
			continue ;
		}else if (select == 2){
			break ;
		}
		if (choice >= 1 && choice <= 7){
			break ;
		}
	}
	return 0 ;
}

bool Student::displayMeassageByID(string id){

	/*
    check id
    id is unique
	*/

	for (int i = 0 ; i < m_count ; i ++){
		if (data[i].m_id == id){
			displayMeassage(i) ;
			return true ;
		}
	}
	return false ;
}

void Student::displayAllProfession(){
	map<string , int>::iterator it ;
	for (it = checkProfession.begin() ; it != checkProfession.end() ; it ++){
		if (it->second > 0){
			cout << it->first << endl ;
		}
	}
	return ;
}

bool Student::searchMeassageByProfession(string profession){

	/*
	check profession
	 */
	bool first = true ;
	bool check_profession = false ;
	for (int i = 0 ; i < m_count ; i ++){
		if (data[i].m_profession == profession){
			if (first == true){
				displayMenu(4) ;
				first = false ;
			}
			displayMeassage(i) ;
			check_profession = true ;
		}
	}
	if (check_profession == false){
		return false ;
	}

	/*
	return menu
	 */

	return true ;
}

void Student::displayAllMeassage(){
	for (int i = 0 ; i < m_count ; i ++){
		displayMeassage(i) ;
	}
	return ;
}

void Student::sortByID(){
	sort(data , data + m_count , cmpByID) ;
	return ;
}

int Student::extendedSort(int way){
	switch (way){
		case 1:{
			sort(data , data + m_count , cmpByID) ;
			cout << endl ;
			cout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 2:{
			sort(data , data + m_count , cmpByAge) ;
			cout << endl ;
			cout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 3:{
			sort(data , data + m_count , cmpByFirstLetterOfName) ;
			cout << endl ;
			cout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 4:{
			sort(data , data + m_count , cmpByFirstLetterOfProfession) ;
			cout << endl ;
			cout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 5:{
			return 1 ;
		}
		default:{
			return 2 ;
		}
	}
	return 0 ;
}

int Student::extendedDelete(int way){
	switch (way){
		case 1:{
			cout << "请输入专业(输入 \"Esc\" 返回上一层菜单)" << endl ;
			string delete_profession ;
			while (cin >> delete_profession){
				if (checkIsEsc(delete_profession) == true){
					return 1 ;
				}
				bool check_profession_exist = false ;
				for (int i = 0 ; i < m_count ; i ++){
					if (delete_profession.compare(data[i].m_profession) == 0){
						check_profession_exist = true ;
						break ;
					}
				}
				if (check_profession_exist == false){
					cout << "不存在此专业,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				int index = -1 ;
				bool end_out_while = false ;
				while (m_count > 0){
					bool end_while = true ;
					for (int i = 0 ; i < m_count ; i ++){
						if (data[i].m_profession.compare(delete_profession) == 0){
							index = i ;
							end_while = false ;
							break ;
						}
					}
					if (end_while == true){
						end_out_while = true ;
						break ;
					}
					checkProfession[data[index].m_profession] -- ;
					for (int i = index ; i < m_count - 1 ; i ++){
						data[i] = data[i + 1] ;
					}
					m_count -- ;
				}
				if (end_out_while == true){
					break ;
				}
			}
			break ;
		}
		case 2:{
			cout << "请输入年龄(输入 \"Esc\" 返回上一层菜单)" << endl ;
			string delete_age ;
			while (cin >> delete_age){
				if (checkIsEsc(delete_age) == true){
					return 1 ;
				}
				bool check_age_exist = false ;
				for (int i = 0 ; i < m_count ; i ++){
					if (delete_age.compare(data[i].m_age) == 0){
						check_age_exist = true ;
						break ;
					}
				}
				if (check_age_exist == false){
					cout << "不存在此年龄的同学,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				int index = -1 ;
				bool end_out_while = false ;
				while (m_count > 0){
					bool end_while = true ;
					for (int i = 0 ; i < m_count ; i ++){
						if (data[i].m_age.compare(delete_age) == 0){
							index = i ;
							end_while = false ;
							break ;
						}
					}
					if (end_while == true){
						end_out_while = true ;
						break ;
					}
					checkProfession[data[index].m_age] -- ;
					for (int i = index ; i < m_count - 1 ; i ++){
						data[i] = data[i + 1] ;
					}
					m_count -- ;
				}
				if (end_out_while == true){
					break ;
				}
			}
			break ;
		}
		case 3:{
			return 1 ;
		}
		default:{
			return 2 ;
		}
	}
	return 0 ;
}

int Student::extendedQuery(int way){
	switch (way){
		case 1:{
			cout << "请输入性别(输入 \"Esc\" 返回上一层菜单)" << endl ;
			string query_sex ;
			while (cin >> query_sex){
				if (checkIsEsc(query_sex) == true){
					return 1 ;
				}
				bool check_sex_exist = false ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_sex.compare(query_sex) == 0){
						check_sex_exist = true ;
						break ;
					}
				}
				if (check_sex_exist == false){
					cout << "不存在此性别的同学,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				cout << endl << "结果如下:" << endl ;
				displayMenu(4) ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_sex.compare(query_sex) == 0){
						displayMeassage(i) ;
					}
				}
				break ;
			}
			break ;
		}
		case 2:{
			cout << "请输入年龄(输入 \"Esc\" 返回上一层菜单)" << endl ;
			string query_age ;
			while (cin >> query_age){
				if (checkIsEsc(query_age) == true){
					return 1 ;
				}
				bool check_age_exist = false ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_age.compare(query_age) == 0){
						check_age_exist = true ;
						break ;
					}
				}
				if (check_age_exist == false){
					cout << "不存在此年龄的同学,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				cout << endl << "结果如下:" << endl ;
				displayMenu(4) ;
				for (int i = 0 ; i < m_count ; i ++){
					if (data[i].m_age.compare(query_age) == 0){
						displayMeassage(i) ;
					}
				}
				break ;
			}
			break ;
		}
		case 3:{
			cout << "请输入姓氏(输入 \"Esc\" 返回上一层菜单)" << endl ;
			string query_firstName ;
			while (cin >> query_firstName){
				if (checkIsEsc(query_firstName) == true){
					return 1 ;
				}
				string str_first_name ;
				bool check_first_name_exist = false ;
				for (int i = 0 ; i < m_count ; i ++){
					str_first_name = data[i].m_name.substr(0 , 2) ;
					if (str_first_name.compare(query_firstName) == 0){
						check_first_name_exist = true ;
						break ;
					}
				}
				if (check_first_name_exist == false){
					cout << "不存在此姓氏的同学,请检查后重新输入(输入 \"Esc\" 返回上一层菜单):" << endl ;
					continue ;
				}
				cout << endl << "结果如下:" << endl ;
				displayMenu(4) ;
				for (int i = 0 ; i < m_count ; i ++){
					str_first_name = data[i].m_name.substr(0 , 2) ;
					if (str_first_name.compare(query_firstName) == 0){
						displayMeassage(i) ;
					}
				}
				break ;
			}
			break ;
		}
		case 4:{
			return 1 ;
		}
		default:{
			return 2 ;
		}
	}
	return 0 ;
}

bool Student::isContinue(){
	string str_select ;
	while (cin >> str_select){
		if (str_select.compare("Yes") == 0){
			return true ;
		}else if (str_select.compare("No") == 0){
			return false ;
		}else{
			cout << "输入错误,请重新输入(Yes/No):" << endl ;
			continue ;
		}
	}
	return false ;
}

void Student::displayMenu(int menu){
	if (menu == -1){
		sortByID() ;
		saveInsideTxt() ;
		system("cls") ;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t信息已保存至\"StudentWrite.txt\"文件,请留意!" << endl ;
		Sleep(1000) ;
		cout << "\t\t\t\t\t系统正在关闭……" << endl ;
		Sleep(1700) ;
		system("cls") ;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t感谢使用学生信息管理系统,再见!" << endl ;
		Sleep(1000) ;
		system("cls") ;
	}
	if (menu == 0){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t\t首次加载,请稍候…………" << endl ;
		Sleep(1700) ;
		system("cls") ;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t\t加载成功！" << endl ;
		Sleep(1000) ;
		system("cls") ;
	}else if (menu == 1){
		cout << "\t\t\t-------- ★\t欢迎来到学生信息管理系统!\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ★\t当前学生信息管理库共有" << m_count << "人\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.输入学生基本信息\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.删除指定学生的信息(按姓名)\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.修改指定学生的信息(按姓名)\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.查询符合条件的学生(按专业)\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t5.显示学生管理库中的所有信息\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t6.拓展功能\t\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t7.退出程序\t\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 2){
		cout << "\t\t\t-------- ★\t功能选项\t\t\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.输入学号进行删除\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.删除所有同名学生的信息\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.显示同名学生的信息\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.返回主菜单\t\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 3){
		cout << "\t\t\t-------- ★\t功能选项\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.修改学号\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.修改姓名\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.修改性别\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.修改年龄\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t5.修改专业\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t6.全部修改\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t7.返回主菜单\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 4){
		cout << "学号\t\t姓名\t\t性别\t\t年龄\t\t专业" << endl ;
		Sleep(500) ;
	}else if (menu == 5){
		cout << "\t\t\t-------- ☆\t新功能开发中,敬请期待……\t☆ --------" << endl ;
		Sleep(700) ;
		return ;
	}else if (menu == 6){
		cout << "\t\t\t-------- ★\t功能选项\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.拓展排序\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.拓展删除\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.拓展查询\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.返回主菜单\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 7){
		cout << "\t\t\t-------- ★\t拓展排序功能选项\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.按学号升序排序\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.按年龄升序排序\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.按姓名首字母排序\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.按专业首字母排序\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t5.返回上一层菜单\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 8){
		cout << "\t\t\t-------- ★\t拓展删除功能选项\t\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.删除同一专业的所有学生\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.删除同一年龄的所有学生\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.返回上一层菜单\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 9){
		cout << "\t\t\t-------- ★\t拓展查询功能选项\t\t★ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t1.查询某一性别的所有学生\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t2.查询某一年龄的所有学生\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t3.查询某一姓氏的所有学生\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ☆\t4.返回上一层菜单\t\t☆ --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}
	if (menu == 4) return ;
	if (menu < 10 && menu > 0) cout << endl << "请输入数字进行选择:" << endl ;
	return ;
}

int main(){
	class Student stud ;
	struct studentMeassage stu ;

	// stud.searchMeassageByProfession("5") ;
	// stud.displayAllMeassage() ;
	// stud.modifyMeassageByName("2") ;
	// stud.displayAllMeassage() ;
	// stud.saveInsideTxt() ;
	stud.displayMenu(0) ;
	stud.displayMenu(1) ;

	/*
	1->enter , 2->delete , 3->modify , 4->search ,
 	5->display , 6->etc(extended function) , 7->quit program
	 */

	int choice ;
	while (cin >> choice){
		bool checkReturnMenu = false ;
		switch (choice){
			case 1:{
				cout << endl ;
				cout << "请按学号、姓名、性别、年龄、专业的顺序进行输入，以空格分隔(输入 \"Esc\" 返回主菜单):" << endl ;
				while (cin >> stu.m_id){
					if (stud.checkIsEsc(stu.m_id) == true){
						checkReturnMenu = true ;
						break ;
					}
					cin >> stu.m_name >> stu.m_sex >> stu.m_age >> stu.m_profession ;
					int check_succeed = stud.enterAndInsertMeassage(stu) ;
					if (check_succeed == 1){
						break ;
					}else if (check_succeed == 2){
						continue ;
					}else if (check_succeed == 0){
						cout << endl ;
						cout << "插入学生信息成功,是否继续输入?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << endl ;
							cout << "请按学号、姓名、性别、年龄、专业的顺序进行输入，以空格分隔(输入 \"Esc\" 返回主菜单):" << endl ;
							continue ;
						}else{
							checkReturnMenu = true ;
							break ;
						}
					}
				}
				break ;
			}
			case 2:{
				cout << endl ;
				cout << "请输入姓名(输入 \"Esc\" 返回主菜单):" << endl ;
				while (cin >> stu.m_name){
					if (stud.checkIsEsc(stu.m_name) == true){
						checkReturnMenu = true ;
						break ;
					}
					cout << endl ;
					int check_succeed = stud.deleteMeassageByName(stu.m_name) ;
					if (check_succeed == 1){
						break ;
					}else if (check_succeed == 2){
						continue ;
					}else if (check_succeed == 0){
						cout << endl ;
						cout << "删除成功,是否继续删除?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << "请输入姓名(输入 \"Esc\" 返回主菜单):" << endl ;
							continue ;
						}else{
							checkReturnMenu = true ;
							break ;
						}
					}
				}
				break ;
			}
			case 3:{
				cout << endl ;
				cout << "请输入姓名(输入 \"Esc\" 返回主菜单):" << endl ;
				while (cin >> stu.m_name){
					if (stud.checkIsEsc(stu.m_name) == true){
						checkReturnMenu = true ;
						break ;
					}
					cout << endl ;
					int check_succeed = stud.modifyMeassageByName(stu.m_name) ;
					if (check_succeed == 1){
						checkReturnMenu = true ;
						break ;
					}else if (check_succeed == 2){
						continue ;
					}else if (check_succeed == 0){
						cout << endl ;
						cout << "是否继续修改其余人的信息?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << "请输入姓名(输入 \"Esc\" 返回主菜单):" << endl ;
							continue ;
						}else{
							checkReturnMenu = true ;
							break ;
						}
					}
				}
				break ;
			}
			case 4:{
				cout << endl ;
				cout << "请输入专业(若想查看已有专业,请输入 \"Display\",输入 \"Esc\" 返回主菜单):" << endl ;
				while (cin >> stu.m_profession){
					if (stud.checkIsEsc(stu.m_profession) == true){
						checkReturnMenu = true ;
						break ;
					}else if (stu.m_profession.compare("Display") == 0){
						cout << "已有专业信息如下:" << endl << endl ;
						stud.displayAllProfession() ;
						cout << endl << "请输入专业(若想查看已有专业,请输入 \"Display\",输入 \"Esc\" 返回主菜单)" << endl ;
						continue ;
					}
					cout << endl ;
					bool check_succeed = stud.searchMeassageByProfession(stu.m_profession) ;
					if (check_succeed == false){
						cout << "未找到此专业的信息,请检查后重新输入(若想查看已有专业,请输入 \"Display\",输入 \"Esc\" 返回主菜单)" << endl ;
						continue ;
					}
					cout << endl ;
					cout << "查询成功,是否继续查询?(Yes/No)" << endl ;
					bool check_continue = stud.isContinue() ;
					if (check_continue == true){
						cout << "请输入专业(若想查看已有专业,请输入 \"Display\",输入 \"Esc\" 返回主菜单):" << endl ;
						continue ;
					}else{
						checkReturnMenu = true ;
						break ;
					}
				}
				break ;
			}
			case 5:{
				if (stud.checkMcount() == true){
					cout << "学生信息管理库已空!" << endl ;
					break ;
				}
				cout << "信息如下:" << endl << endl ;
				stud.displayMenu(4) ;
				stud.sortByID() ;
				stud.displayAllMeassage() ;
				cout << endl << endl ;
				system("pause") ;
				checkReturnMenu = true ;
				break ;
			}
			case 6:{
				stud.displayMenu(6) ;
				int select ;
				while (cin >> select){
					bool checkReturnPreviousMenu = false ;
					switch (select){
						case 1:{
							stud.displayMenu(7) ;
							int way ;
							while (cin >> way){
								int check_sortSucceed = stud.extendedSort(way) ;
								if (check_sortSucceed == 0){
									cout << endl << "排序成功,是否继续选择其余排序方式?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(7) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "输入错误，请重新输入(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_sortSucceed == 2){
									cout << "输入错误，请重新输入" << endl ;
									continue ;
								}else if (check_sortSucceed == 1){
									checkReturnPreviousMenu = true ;
									break ;
								}
								if (checkReturnPreviousMenu == true){
									break ;
								}
							}
							stud.sortByID() ;
							break ;
						}
						case 2:{
							stud.displayMenu(8) ;
							int way ;
							while (cin >> way){
								int check_deleteSucceed = stud.extendedDelete(way) ;
								if (check_deleteSucceed == 0){
									cout << endl << "删除成功,是否继续选择其余删除方式?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(8) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "输入错误，请重新输入(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_deleteSucceed == 2){
									cout << "输入错误，请重新输入" << endl ;
									continue ;
								}else if (check_deleteSucceed == 1){
									checkReturnPreviousMenu =  true ;
									break ;
								}
								if (checkReturnPreviousMenu == true){
									break ;
								}
							}
							break ;
						}
						case 3:{
							stud.displayMenu(9) ;
							int way ;
							while (cin >> way){
								int check_querySecceed = stud.extendedQuery(way) ;
								if (check_querySecceed == 0){
									cout << endl << "查询成功,是否继续选择其余查询方式?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(9) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "输入错误，请重新输入(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_querySecceed == 2){
									cout << "输入错误，请重新输入" << endl ;
									continue ;
								}else if (check_querySecceed == 1){
									checkReturnPreviousMenu =  true ;
									break ;
								}
								if (checkReturnPreviousMenu == true){
									break ;
								}
							}
							break ;
						}
						case 4:{
							checkReturnMenu = true ;
							break ;
						}
						default:
							cout << "输入错误，请重新输入" << endl ;
					}
					if (checkReturnPreviousMenu == true){
						stud.displayMenu(6) ;
					}
					if (checkReturnMenu == true){
						break ;
					}
				}
				checkReturnMenu = true ;
				break ;
			}
			case 7:{
				stud.displayMenu(-1) ;
				return 0 ;
			}
			default :
				cout << "输入错误，请重新输入" << endl ;
		}
		if (checkReturnMenu == true){
			cout << endl << endl ;
			cout << "即将返回主菜单" << endl << endl ;
			Sleep(1000) ;
			cout << "加载中,请稍候…………" << endl << endl ;
			Sleep(1500) ;
			stud.saveInsideTxt() ;
			stud.displayMenu(1) ;
		}
	}
	return 0 ;
}

/*
map<string , int> -> duplicated profession
string -> profession
int -> time
 */