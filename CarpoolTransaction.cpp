#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <cctype>
#include "CarpoolTransaction.h"

//Parameterized Default Constructor
CarpoolTransaction::CarpoolTransaction() {
	db_conn = NULL;
}

//Default Destructor
CarpoolTransaction::~CarpoolTransaction() {
	mysql_close(db_conn);
}

bool CarpoolTransaction::MySQL_Connect(const string HOST, const string USER,
	const string PASSWORD, const string DB_NAME) {
	//Connection Handle Initialization Structure
		this->db_conn = mysql_init(NULL);
		if(!(this->db_conn)) { message("MySQL Initialization Failed!"); return false; }
		else {
			message("MySQL Initialization Succeeded!");
			//Initialization Succeeded: Instantiate Connection
			this->db_conn = mysql_real_connect(this->db_conn, HOST.c_str(), 
				USER.c_str(), PASSWORD.c_str(), DB_NAME.c_str(), 0, NULL, 0);
			if(!(this->db_conn)) { message("MySQL Connection Instatiation Failed!"); return false; }
			else { message("MySQL Connection Instatiation Succeeded!"); return true; }
		}
}

bool CarpoolTransaction::Sign_Up(CarpoolAccountPtr cpa) {
	stringstream ss;

	ss << "INSERT INTO user(SJSU_ID, EMAIL, USER_NAME, ADDRESS, NAME, PASSWORD, USER_TYPE, ANSWER_SQ1, ANSWER_SQ2)"
	   << "values ('" << cpa->get_sjsu_id() << "', '"
	   << cpa->get_email() << "', '" << cpa->get_username() << "', '"
	   << cpa->get_address() << "', '" << cpa->get_name() << "', '"
	   << cpa->get_passwd() << "', '" << cpa->get_user_type() << "', '"
	   << cpa->get_answer_sq_one() << "', '" << cpa->get_answer_sq_two() << "')";

	if(mysql_query(db_conn, ss.str().c_str())) { message("Sign Up Failed!"); return false; }
	else { message("Sign Up Succeeded!"); return true; }
}

void CarpoolTransaction::MaskPassword(string &passwd) {
	struct termios old_tio, new_tio;
	//Get the terminal settings for stdin
	tcgetattr(STDIN_FILENO, &old_tio);
	//Save the previous setting to restore later
	new_tio = old_tio;
	//Disable canonical mode, i.e., buffered I/O and local echo
	new_tio.c_lflag &= (~ICANON & ~ECHO);
	//Set the new settings immediately
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	//Read masked password
	getline(cin, passwd, '\n');
	//Restore previous settings
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

bool CarpoolTransaction::Is_PasswordValid(string &passwd, string temp_passwd) {
	if(passwd != temp_passwd) {
		message("\nError: Password Mismatch!");
		return false;
	}
	else {
		CaesarCipher(passwd);
		return true;
	}
}

void CarpoolTransaction::CaesarCipher(string &passwd) {
	unsigned int index = 0, len = passwd.length();
	while(index < len) {
		if(((passwd.at(index) >= 'A') && (passwd.at(index) <= 'M')) ||
			((passwd.at(index) >= 'a') && (passwd.at(index) <= 'm')))
				passwd.at(index) += 13;
		else if(((passwd.at(index) >= 'N') && (passwd.at(index) <= 'Z')) ||
			((passwd.at(index) >= 'n') && (passwd.at(index) <= 'z')))
				passwd.at(index) -= 13;
		else if((passwd.at(index) >= '0') && (passwd.at(index) <= '4')) 
				passwd.at(index) += 5;
		else if((passwd.at(index) >= '5') && (passwd.at(index) <= '9')) 
				passwd.at(index) -= 5;
		index++;
	}
}

bool CarpoolTransaction::Is_SJID_Valid(string sjid) {
	unsigned int index = 0, len = sjid.length();
	if(len != 9) {
		message("Error: SJSU ID must have nine characters!");
		return false;
	}
	while(index < len) {
		if(!isdigit(sjid.at(index++))) {
			message("Error: SJSU ID cannot have non-numeric character!");
			return false;
		} 
	}
	return true;
}

bool CarpoolTransaction::Is_Utype_Valid(string utype) {
	unsigned int index = 0, len = utype.length();
	while(index < len) {
		utype.at(index) = toupper(utype.at(index));
		index++;
	}
	if((utype == "FACULTY") || (utype == "STAFF") || (utype == "STUDENT")) 
		return true;
	else {
		message("Error: User type must be a Student, Falculty, or Staff!");
		return false;
	}
}

string CarpoolTransaction::Sign_In(string uname, string passwd, bool &SignIn) {
	stringstream ss;
	string sjid;
	MYSQL_ROW row;
	MYSQL_RES *rset;

	ss << "SELECT SJSU_ID, USER_NAME, PASSWORD FROM user WHERE USER_NAME = '"
	   << uname << "' AND PASSWORD = '" << passwd << "'";
	if(mysql_query(db_conn, ss.str().c_str())) {
		message("\nError: Sign In Failed! Username or Password is Invalid!");
		return "";
	}
	else {
		rset = mysql_use_result(db_conn);
		row = mysql_fetch_row(rset);
		
		if(row == NULL) {
			message("\nError: Sign In Failed! Username or Password is Invalid!");
			return "";
		}
		else {  
			SignIn = true;
			message("\nSign In Succeeded!");
			sjid = *row;
			mysql_free_result(rset);
			return sjid;
		}
	}
}

void CarpoolTransaction::GetSignInData() {
	stringstream ss;
	string sjid, ans_sq_one, ans_sq_two, passwd;
	MYSQL_RES *rset;
	MYSQL_ROW rows;

	do {
		cout << "\nEnter your SJSU ID: ";
		getline(cin, sjid, '\n');
	}while(!Is_SJID_Valid(sjid));
	cout << "Security Question I: What was your High School Mascot? ";
	getline(cin, ans_sq_one, '\n');
	cout << "Security Question II: In which city where you born? ";
	getline(cin, ans_sq_two, '\n');

	ss << "SELECT USER_NAME, PASSWORD FROM user WHERE SJSU_ID = '"
	   << sjid << "' AND ANSWER_SQ1 = '" << ans_sq_one << "' AND "
	   << "ANSWER_SQ2 = '" << ans_sq_two << "'";

	if(mysql_query(db_conn, ss.str().c_str())) {
		message("\nError: Username and Password Retrieval Failed!");
		return;
	}
	else {
		rset = mysql_use_result(db_conn);
		rows = mysql_fetch_row(rset);

		if(rows == NULL) {
			message("\nError: Username and Password Retrieval Failed!");
			return;
		}
		else {
			passwd = *(rows + 1);
			CaesarCipher(passwd);
			message("\nUsername and Password Retrieval Succeeded!");
			cout << "\nYour username is: " << *rows
				 << "\nYour password is: " << passwd
				 << "\n";
		}
	}
	mysql_free_result(rset);
}

bool CarpoolTransaction::EditAccount(const string attribute, string sjid, const string attribute_value) {
	stringstream ss;

	ss << "UPDATE user SET " << attribute << " = '" << attribute_value << "' WHERE "
	   << "SJSU_ID = '" << sjid << "'";

	 if(mysql_query(db_conn, ss.str().c_str())) {
	 	cerr << "Error " << mysql_errno(db_conn) << ": " << mysql_error(db_conn) << "!\n";
	 	cerr << attribute << " Update Failed!\n";
	 	return false;
	 }
	 else {
	 	cout << attribute << " Update Succeeded!\n";
	 	return true;
	 }
}

void CarpoolTransaction::message(string msg) {
	cout << msg << '\n';
}