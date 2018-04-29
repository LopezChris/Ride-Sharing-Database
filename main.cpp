#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "CarpoolTransaction.h"

enum Menu_Options { ADMIN = 1, SIGN_UP, SIGN_IN, END, DEBUG };

int Main_Menu() {
	int choice;

	cout << "Menu Options\n"
		 << "------------\n"
		 << "1 - Connect to a MySQL Database\n"
		 << "2 - Sign Up\n"
		 << "3 - Sign In\n"
		 << "4 - End Program\n"
		 << "5 - DEBUG\n"
		 << "Choose an operation and then press return: ";
	cin  >> choice;
	cin.ignore(1000, '\n');

	return choice;
}

int main() {
	int choice;
	CarpoolTransactionPtr cpt = new CarpoolTransaction;
	CarpoolAccountPtr cpa;
	string db_host, db_username, db_passwd, db_dbname;
	string sjid, email, uname, addr, name, passwd, temp_passwd, utype, ans_sq_one, ans_sq_two;
	string u_name, t_passwd, sj_id;
	bool valid_login = false;

	while(1) {
		choice = Main_Menu();
		if(choice == END)	break;

		switch(choice) {
			case ADMIN:
				cout << "\nSpecify MySQL Host: ";
				getline(cin, db_host, '\n');
				cout << "Specify MySQL User: ";
				getline(cin, db_username, '\n');
				cout << "Specify MySQL Password: ";
				cpt->MaskPassword(db_passwd);
				cout << "\nSpecify MySQL Database Name: ";
				getline(cin, db_dbname, '\n');
				cpt->MySQL_Connect(db_host, db_username, db_passwd, db_dbname);
				cout << '\n';
				break;

			case SIGN_UP:
				cout << endl;
				do {
					cout << "Enter SJSU ID: ";
					getline(cin, sjid, '\n');
				}while(!cpt->Is_SJID_Valid(sjid)); 
				cout << "Enter email address: ";
				getline(cin, email, '\n');
				cout << "Enter username: ";
				getline(cin, uname, '\n');
				cout << "Enter address: ";
				getline(cin, addr, '\n');
				cout << "Enter name: ";
				getline(cin, name, '\n');
				do {
					cout << "Enter password: ";
					cpt->MaskPassword(passwd);
					cout << "\nRe-enter password: ";
					cpt->MaskPassword(temp_passwd);
				}while(!cpt->Is_PasswordValid(passwd, temp_passwd));
				do {
					cout << "\nEnter user type: Faculty, Staff, or Student? ";
					getline(cin, utype, '\n');
				}while(!cpt->Is_Utype_Valid(utype));
				cout << "Security Question I: What was your high school mascot? ";
				getline(cin, ans_sq_one, '\n');
				cout << "Security Question II: In which city where you born? ";
				getline(cin, ans_sq_two, '\n');
				cpa = new CarpoolAccount(sjid, email, uname, addr, name, passwd, 
							utype, ans_sq_one, ans_sq_two);
				if(cpt->Sign_Up(cpa)){
					sj_id = cpa->get_sjsu_id();	
				}
				cout << sj_id;
				cout << endl;
				break;

			case SIGN_IN:
				cout << endl;
				do {
					cout << "Enter username: ";
					getline(cin, u_name, '\n');
					cout << "Enter password: ";
					cpt->MaskPassword(t_passwd);
					cpt->CaesarCipher(t_passwd);
					sj_id =	cpt->Sign_In(u_name, t_passwd, valid_login);
				}while(!valid_login);
				cout << endl << sj_id << endl;
				break;
			case DEBUG:
				sj_id = cpt->User_SJID(u_name);
				cout << sj_id << endl;
				cout << endl;
				break; 

			default:
				cerr << "\nInvalid Operation Selected!\n\n";
				break;
		}
	}
	return 0;
}
