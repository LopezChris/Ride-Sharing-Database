#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "CarpoolTransaction.h"

enum Main_Menu_Options { CONNECT = 1, SIGN_UP, SIGN_IN, SIGN_OUT };
enum Menu_One_Options { EDIT_ACCOUNT = 5, DRIVE, RIDE, _SIGN_OUT };
enum Edit_Menu_Options {SJID = 1, EMAIL, UNAME, ADDR, NAME, PASSWD, UTYPE, ANS_SQ1, ANS_SQ2, DONE, _SIGN_OUT_};

int Main_Menu() {
	int choice;

	cout << "Main Menu Options\n"
		 << "-----------------\n"
		 << "1 - Connect to MySQL Database\n"
		 << "2 - Sign Up\n"
		 << "3 - Sign In\n"
		 << "4 - Sign Out\n"
		 << "Choose an operation and then press return: ";
	cin  >> choice;
	cin.ignore(1000, '\n');

	return choice;
}

int Menu_One() {
	int choice;

	cout << "Menu One Options\n"
		 << "----------------\n"
		 << "1 - Edit Account\n"
		 << "2 - Drive\n"
		 << "3 - Ride\n"
		 << "4 - Sign Out\n"
		 << "Choose an operation and then press return: ";
	cin  >> choice;
	cin.ignore(1000, '\n');

	return choice;
}

int Edit_Menu() {
	int choice;

	cout << "\nEdit Menu Options\n"
		 << "-----------------\n"
		 << "1  - Edit SJSU ID\n"
		 << "2  - Edit Email\n"
		 << "3  - Edit Username\n"
		 << "4  - Edit Address\n"
		 << "5  - Edit Name\n"
		 << "6  - Edit Password\n"
		 << "7  - Edit User Type\n"
		 << "8  - Edit Answer to Security Question One\n"
		 << "9  - Edit Answer to Security Question Two\n"
		 << "10 - Done\n"
		 << "11 - Sign Out\n"
		 << "Choose and operation and then press return: ";
	cin  >> choice;
	cin.ignore(1000, '\n');

	return choice;
}

int main() {
	int choice, count = 0;
	char ch;
	bool MainMenu = true;
	bool MenuOne = false, MenuTwo = false, EditMenu = false;
	bool SignIn = false;
	CarpoolTransactionPtr cpt = new CarpoolTransaction;
	string db_host, db_username, db_passwd, db_dbname;
	string sjid, email, uname, addr, name, passwd, temp_passwd, utype, ans_sq_one, ans_sq_two;
	string new_sjid, new_email, new_uname, new_addr, new_name, new_passwd, new_temp_passwd,
		   new_utype, new_ans_sq_one, new_ans_sq_two;

	while(1) {
		if(MainMenu) choice = Main_Menu();
		else if(MenuOne)  { choice = Menu_One(); choice += 4; }

		if((choice == SIGN_OUT) || (choice == _SIGN_OUT)) break;

		switch(choice) {
			case CONNECT:
				do {
					cout << "\nSpecify MySQL Host: ";
					getline(cin, db_host, '\n');
					cout << "Specify MySQL User: ";
					getline(cin, db_username, '\n');
					cout << "Specify MySQL Password: ";
					cpt->MaskPassword(db_passwd);
					cout << "\nSpecify MySQL Database Name: ";
					getline(cin, db_dbname, '\n');
				}while(!cpt->MySQL_Connect(db_host, db_username, db_passwd, db_dbname));
				cout << endl;
				break;

			case SIGN_UP:
				cout << endl;
				do {
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
				}while(!cpt->Sign_Up(new CarpoolAccount(sjid, email, uname, addr, name,
					passwd, utype, ans_sq_one, ans_sq_two)));
				email = uname = addr = name = passwd = temp_passwd = utype = ans_sq_one = ans_sq_two = "";
				//SJSU ID is already known: the variable sjid
				MainMenu = false; 
				MenuOne = true;
				cout << endl;
				break;

			case SIGN_IN:
				cout << endl;
				do {
					cout << "Enter username: ";
					getline(cin, uname, '\n');
					cout << "Enter password: ";
					cpt->MaskPassword(temp_passwd);
					cpt->CaesarCipher(temp_passwd);
					sjid = cpt->Sign_In(uname, temp_passwd, SignIn);
					if(++count == 3) {
						cout << "\nForgot username, password? [Y | N] ";
						cin  >> ch;
						cin.ignore(1000, '\n');
						if((ch = toupper(ch)) == 'Y') cpt->GetSignInData();
						count = 0;
						cout << endl;
					}
				}while(!SignIn);
				uname = temp_passwd = "";
				MainMenu = false;
				MenuOne = true;
				SignIn = false;
				count = 0;
				cout << endl;
				break; 

			case EDIT_ACCOUNT:
				int choice;
				bool new_sjid_flag ;

				while(1) {
					choice = Edit_Menu();
					if(choice == DONE) break;
					else if(choice == _SIGN_OUT_) return 0;

					switch(choice) {
						case SJID: 
							cout << endl;
							do {
								cout << "Enter new SJSU ID: ";
								getline(cin, new_sjid, '\n');
								new_sjid_flag = cpt->Is_SJID_Valid(new_sjid);
								if((new_sjid_flag) && (sjid == new_sjid)) { 
									cerr << "Error: New and Old SJSU ID are the same!\n";
									new_sjid_flag = false;
								}
							}while((!new_sjid_flag) || (!cpt->EditAccount("SJSU_ID", sjid, new_sjid)));
							new_sjid = "";
							cout << endl;
							break;

						case EMAIL:
							break;

						case UNAME:
							break;

						case ADDR:
							break;

						case NAME:
							break;

						case PASSWD:
							break;

						case UTYPE:
							break;

						case ANS_SQ1:
							break;

						case ANS_SQ2:
							break;

						default: cerr << "\nInvalid Operation Selected!\n\n";
							break;
					}
				}
				cout << endl;
				break;

			default:
				cerr << "\nInvalid Operation Selected!\n\n";
				break;
		}
	}
	return 0;
}