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
		fout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
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
		cout << "����ʧ��,ѧ����Ϣ���������!" << endl ;
		return 1 ;
	}

	// for (int i = 0 ; i < m_count ; i ++){
	// 	if (newinfo.m_id == data[i].m_id){
	// 		return false ;
	// 	}
	// }

	if (checkMeassage[newinfo.m_id] == true){
		cout << "����ʧ��,��ѧ���Ѵ���,�������������!" << endl ;
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
���ǰ�������Ѱ��Ϣ��Ȼ��˴�����Ϊ�� ID �� name ɾ����������������������߽���ѡ��
1->��ǰ����ʽֻɾ��һ����2->ɾ������ͬ���� , 3->��ʾͬ���˵���Ϣ , 4->quit
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
		cout << "ɾ��ʧ��,ѧ����Ϣ������ѿ�!" << endl ;
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
		cout << "δ�ҵ�����Ϊ " << name << " ��ͬѧ��Ϣ,�������������(���� \"Esc\" �������˵�)" << endl ;
		return 2 ;
	}
	displayMenu(2) ;
	int selectWay ;
	while (cin >> selectWay){
		bool checkReturnPreviousMenu = false ;
		if (selectWay == 1){
			cout << "������ѧ��(���� \"Esc\" ������һ��˵�):" << endl ;
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
					cout << "��ѧ�Ų������������������(���� \"Esc\" ������һ��˵�):" << endl ;
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
					cout << "ѧ�ź�������ƥ��,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
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
			cout << "ͬ��ѧ����Ϣ����:" << endl << endl ;
			displayMenu(4) ;
			searchMeassageByName(name) ;
			cout << endl << endl ;
		}else if (selectWay == 4){
			cout << endl << "�����������˵�" << endl ;
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
			cout << "�����������������:" << endl ;
		}
	}
	return 0 ;
}

int Student::modifyMeassageByName(string cur_name){

	/*
	consider the same name -> OK
	*/
	if (checkMcount() == true){
		cout << "�޸�ʧ��,ѧ����Ϣ������ѿ�" << endl ;
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
		cout << "δ�ҵ�����Ϊ " << cur_name << " ��ͬѧ��Ϣ,�������������" << endl ;
		return 2 ;
	}
	cout << endl ;
	cout << "�ҵ�����Ϊ" << cur_name << "����Ϣ" << endl << endl ;
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
				cout << "�������޸ĺ��ѧ��(���� \"Esc\" ������һ��˵�):" << endl ;
				while (cin >> id){
					if (checkIsEsc(id) == true){
						checkReturnPreviousMenu = true ;
						cout << endl ;
						break ;
					}
					if (checkMeassage[id] == true){
						cout << "��ѧ���Ѵ��ڣ�����������:" << endl ;
						continue ;
					}
					break ;
				}
				checkMeassage[data[index].m_id] = false ;
				data[index].m_id = id ;
				checkMeassage[data[index].m_id] = true ;
				break ;
			case 2:
				cout << "�������޸ĺ������(���� \"Esc\" ������һ��˵�):" << endl ;
				cin >> name ;
				if (checkIsEsc(name) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_name = name ;
				break ;
			case 3:
				cout << "�������޸ĺ���Ա�(���� \"Esc\" ������һ��˵�):" << endl ;
				cin >> sex ;
				if (checkIsEsc(sex) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_sex = sex ;
				break ;
			case 4:
				cout << "�������޸ĺ������(���� \"Esc\" ������һ��˵�):" << endl ;
				cin >> age ;
				if (checkIsEsc(age) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_age = age ;
				break ;
			case 5:
				cout << "�������޸ĺ��רҵ(���� \"Esc\" ������һ��˵�):" << endl ;
				cin >> profession ;
				if (checkIsEsc(profession) == true){
					checkReturnPreviousMenu = true ;
					cout << endl ;
					break ;
				}
				data[index].m_profession = profession ;
				break ;
			case 6:
				cout << "�밴ѧ�š��������Ա����䡢רҵ��˳��������룬�Կո�ָ�(���� \"Esc\" ������һ��˵�):" << endl ;
				while (cin >> id){
					cin >> name >> sex >> age >> profession ;
					if (checkIsEsc(id) == true){
						checkReturnPreviousMenu = true ;
						cout << endl ;
						break ;
					}
					if (checkMeassage[id] == true){
						cout << "ѧ���Ѵ��ڣ�����������:" << endl ;
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
				// cout << "�����������˵�" << endl ;
				// Sleep(1000) ;
				// system("cls") ;
				// displayMenu(1) ;
				// break ;
				return 1 ;
			default:
				cout << "�����������������" << endl ;
		}
		if (checkReturnPreviousMenu == true){
			displayMenu(3) ;
			continue ;
		}
		cout << "�޸ĳɹ�,�޸ĺ����ϢΪ:" << endl << endl ;
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
			cout << endl << "��⵽ͬ������ϢΪ:" << endl ;
			displayMeassage(index) ;
			cout << endl << "�Ƿ�������Ĵ�ͬѧ����Ϣ��(Yes/No)" << endl ;
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
					cout << "�����������������" << endl ;
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
			cout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 2:{
			sort(data , data + m_count , cmpByAge) ;
			cout << endl ;
			cout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 3:{
			sort(data , data + m_count , cmpByFirstLetterOfName) ;
			cout << endl ;
			cout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
			displayAllMeassage() ;
			cout << endl ;
			system("pause") ;
			break ;
		}
		case 4:{
			sort(data , data + m_count , cmpByFirstLetterOfProfession) ;
			cout << endl ;
			cout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
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
			cout << "������רҵ(���� \"Esc\" ������һ��˵�)" << endl ;
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
					cout << "�����ڴ�רҵ,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
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
			cout << "����������(���� \"Esc\" ������һ��˵�)" << endl ;
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
					cout << "�����ڴ������ͬѧ,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
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
			cout << "�������Ա�(���� \"Esc\" ������һ��˵�)" << endl ;
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
					cout << "�����ڴ��Ա��ͬѧ,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
					continue ;
				}
				cout << endl << "�������:" << endl ;
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
			cout << "����������(���� \"Esc\" ������һ��˵�)" << endl ;
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
					cout << "�����ڴ������ͬѧ,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
					continue ;
				}
				cout << endl << "�������:" << endl ;
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
			cout << "����������(���� \"Esc\" ������һ��˵�)" << endl ;
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
					cout << "�����ڴ����ϵ�ͬѧ,�������������(���� \"Esc\" ������һ��˵�):" << endl ;
					continue ;
				}
				cout << endl << "�������:" << endl ;
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
			cout << "�������,����������(Yes/No):" << endl ;
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
		cout << "\t\t\t\t\t��Ϣ�ѱ�����\"StudentWrite.txt\"�ļ�,������!" << endl ;
		Sleep(1000) ;
		cout << "\t\t\t\t\tϵͳ���ڹرա���" << endl ;
		Sleep(1700) ;
		system("cls") ;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t��лʹ��ѧ����Ϣ����ϵͳ,�ټ�!" << endl ;
		Sleep(1000) ;
		system("cls") ;
	}
	if (menu == 0){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t\t�״μ���,���Ժ򡭡�����" << endl ;
		Sleep(1700) ;
		system("cls") ;
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "\t\t\t\t\t\t���سɹ���" << endl ;
		Sleep(1000) ;
		system("cls") ;
	}else if (menu == 1){
		cout << "\t\t\t-------- ��\t��ӭ����ѧ����Ϣ����ϵͳ!\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t��ǰѧ����Ϣ����⹲��" << m_count << "��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.����ѧ��������Ϣ\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.ɾ��ָ��ѧ������Ϣ(������)\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.�޸�ָ��ѧ������Ϣ(������)\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.��ѯ����������ѧ��(��רҵ)\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t5.��ʾѧ��������е�������Ϣ\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t6.��չ����\t\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t7.�˳�����\t\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 2){
		cout << "\t\t\t-------- ��\t����ѡ��\t\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.����ѧ�Ž���ɾ��\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.ɾ������ͬ��ѧ������Ϣ\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.��ʾͬ��ѧ������Ϣ\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.�������˵�\t\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 3){
		cout << "\t\t\t-------- ��\t����ѡ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.�޸�ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.�޸�����\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.�޸��Ա�\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.�޸�����\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t5.�޸�רҵ\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t6.ȫ���޸�\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t7.�������˵�\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 4){
		cout << "ѧ��\t\t����\t\t�Ա�\t\t����\t\tרҵ" << endl ;
		Sleep(500) ;
	}else if (menu == 5){
		cout << "\t\t\t-------- ��\t�¹��ܿ�����,�����ڴ�����\t�� --------" << endl ;
		Sleep(700) ;
		return ;
	}else if (menu == 6){
		cout << "\t\t\t-------- ��\t����ѡ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.��չ����\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.��չɾ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.��չ��ѯ\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.�������˵�\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 7){
		cout << "\t\t\t-------- ��\t��չ������ѡ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.��ѧ����������\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.��������������\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.����������ĸ����\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.��רҵ����ĸ����\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t5.������һ��˵�\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 8){
		cout << "\t\t\t-------- ��\t��չɾ������ѡ��\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.ɾ��ͬһרҵ������ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.ɾ��ͬһ���������ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.������һ��˵�\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}else if (menu == 9){
		cout << "\t\t\t-------- ��\t��չ��ѯ����ѡ��\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t1.��ѯĳһ�Ա������ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t2.��ѯĳһ���������ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t3.��ѯĳһ���ϵ�����ѧ��\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "\t\t\t-------- ��\t4.������һ��˵�\t\t�� --------" << endl << endl ;
		Sleep(700) ;
		cout << "========================================================================================================================" << endl ;
		Sleep(700) ;
	}
	if (menu == 4) return ;
	if (menu < 10 && menu > 0) cout << endl << "���������ֽ���ѡ��:" << endl ;
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
				cout << "�밴ѧ�š��������Ա����䡢רҵ��˳��������룬�Կո�ָ�(���� \"Esc\" �������˵�):" << endl ;
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
						cout << "����ѧ����Ϣ�ɹ�,�Ƿ��������?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << endl ;
							cout << "�밴ѧ�š��������Ա����䡢רҵ��˳��������룬�Կո�ָ�(���� \"Esc\" �������˵�):" << endl ;
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
				cout << "����������(���� \"Esc\" �������˵�):" << endl ;
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
						cout << "ɾ���ɹ�,�Ƿ����ɾ��?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << "����������(���� \"Esc\" �������˵�):" << endl ;
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
				cout << "����������(���� \"Esc\" �������˵�):" << endl ;
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
						cout << "�Ƿ�����޸������˵���Ϣ?(Yes/No)" << endl ;
						bool check_continue = stud.isContinue() ;
						if (check_continue == true){
							cout << "����������(���� \"Esc\" �������˵�):" << endl ;
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
				cout << "������רҵ(����鿴����רҵ,������ \"Display\",���� \"Esc\" �������˵�):" << endl ;
				while (cin >> stu.m_profession){
					if (stud.checkIsEsc(stu.m_profession) == true){
						checkReturnMenu = true ;
						break ;
					}else if (stu.m_profession.compare("Display") == 0){
						cout << "����רҵ��Ϣ����:" << endl << endl ;
						stud.displayAllProfession() ;
						cout << endl << "������רҵ(����鿴����רҵ,������ \"Display\",���� \"Esc\" �������˵�)" << endl ;
						continue ;
					}
					cout << endl ;
					bool check_succeed = stud.searchMeassageByProfession(stu.m_profession) ;
					if (check_succeed == false){
						cout << "δ�ҵ���רҵ����Ϣ,�������������(����鿴����רҵ,������ \"Display\",���� \"Esc\" �������˵�)" << endl ;
						continue ;
					}
					cout << endl ;
					cout << "��ѯ�ɹ�,�Ƿ������ѯ?(Yes/No)" << endl ;
					bool check_continue = stud.isContinue() ;
					if (check_continue == true){
						cout << "������רҵ(����鿴����רҵ,������ \"Display\",���� \"Esc\" �������˵�):" << endl ;
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
					cout << "ѧ����Ϣ������ѿ�!" << endl ;
					break ;
				}
				cout << "��Ϣ����:" << endl << endl ;
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
									cout << endl << "����ɹ�,�Ƿ����ѡ����������ʽ?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(7) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "�����������������(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_sortSucceed == 2){
									cout << "�����������������" << endl ;
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
									cout << endl << "ɾ���ɹ�,�Ƿ����ѡ������ɾ����ʽ?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(8) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "�����������������(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_deleteSucceed == 2){
									cout << "�����������������" << endl ;
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
									cout << endl << "��ѯ�ɹ�,�Ƿ����ѡ�������ѯ��ʽ?(Yes/No)" << endl ;
									string str_continue ;
									while (cin >> str_continue){
										if (str_continue.compare("Yes") == 0){
											stud.displayMenu(9) ;
											break ;
										}else if (str_continue.compare("No") == 0){
											checkReturnPreviousMenu = true ;
											break ;
										}else{
											cout << "�����������������(Yes/No)" << endl ;
											continue ;
										}
									}
								}else if (check_querySecceed == 2){
									cout << "�����������������" << endl ;
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
							cout << "�����������������" << endl ;
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
				cout << "�����������������" << endl ;
		}
		if (checkReturnMenu == true){
			cout << endl << endl ;
			cout << "�����������˵�" << endl << endl ;
			Sleep(1000) ;
			cout << "������,���Ժ򡭡�����" << endl << endl ;
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