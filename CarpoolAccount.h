#ifndef CARPOOLACCOUNT_H
#define	CARPOOLACCOUNT_H

#include <string>

using namespace std;

class CarpoolAccount;
typedef CarpoolAccount* CarpoolAccountPtr;

class CarpoolAccount {
	public:
		//Constraint on the length of a user attributes
			static const int MAX_LEN = 30;

		//Parameterized Default Constructor For Sign Up
			CarpoolAccount(string sj_id = "", string e_mail = "", string u_name = "",
				string addr = "", string name = "", string pwd = "", 
				string u_type = "", string ans_sq_one = "", string ans_sq_two = ""
			);

		//Destructor
			~CarpoolAccount();

		//Mutator Methods:
			void set_sjsu_id(string sj_id);
			void set_email(string e_mail);
			void set_username(string u_name);
			void set_address(string addr);
			void set_name(string name);
			void set_passwd(string pwd);
			void set_user_type(string u_type);
			void set_answer_sq_one(string ans_sq_one);
			void set_answer_sq_two(string ans_sq_two);

		//Accessor Methods:
			string get_sjsu_id() const;
			string get_email() const;
			string get_username() const;
			string get_address() const;
			string get_name() const;
			string get_passwd() const;
			string get_user_type() const;
			string get_answer_sq_one() const;
			string get_answer_sq_two() const;

	private:
			char m_sj_id[MAX_LEN];  		//User SJSU ID
			char m_email[MAX_LEN];			//User EMAIL
			char m_uname[MAX_LEN];			//User USERNAME
			char m_addr[MAX_LEN];			//User ADDRESS
			char m_name[MAX_LEN];			//User LEGAL NAME
			char m_pwd[MAX_LEN];			//User PASSWORD
			char m_utype[MAX_LEN];			//User TYPE: FACULTY, STAFF, OR STUDENT
			char m_ans_sq_one[MAX_LEN];		//User ANSWER TO SECURITY QUESTION ONE
			char m_ans_sq_two[MAX_LEN];		//User ANSWER TO SECURITY QUESTION TWO
};

#endif	//CARPOOLACCOUNT_H