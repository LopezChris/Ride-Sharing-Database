#include <cstring>
#include "CarpoolAccount.h"

//PARAMETERIZED DEFAULT CONSTRUCTOR: SIGN UP
CarpoolAccount::CarpoolAccount(string sj_id, string e_mail, string u_name, 
	string addr, string name, string pwd, string u_type, string ans_sq_one, string ans_sq_two) {
	set_sjsu_id(sj_id);
	set_email(e_mail);
	set_username(u_name);
	set_address(addr);
	set_name(name);
	set_passwd(pwd);
	set_user_type(u_type);
	set_answer_sq_one(ans_sq_one);
	set_answer_sq_two(ans_sq_two);
}

//DESTRUCTOR
CarpoolAccount::~CarpoolAccount() {};

//Mutator Methods:
void CarpoolAccount::set_sjsu_id(string sj_id) {
	const char *sjsu_id = sj_id.data();
	int len = sj_id.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_sj_id, sjsu_id, len);
	m_sj_id[len] = '\0';
}
			
void CarpoolAccount::set_email(string e_mail) {
	const char *email = e_mail.data();
	int len = e_mail.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_email, email, len);
	m_email[len] = '\0';
}
			
void CarpoolAccount::set_username(string u_name) {
	const char *uname = u_name.data();
	int len = u_name.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_uname, uname, len);
	m_uname[len] = '\0';
}

void CarpoolAccount::set_address(string addr) {
	const char *adr = addr.data();
	int len = addr.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_addr, adr, len);
	m_addr[len] = '\0';
}
			
void CarpoolAccount::set_name(string name) {
	const char *nm = name.data();
	int len = name.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_name, nm, len);
	m_name[len] = '\0';
}
			
void CarpoolAccount::set_passwd(string pwd) {
	const char *passwd = pwd.data();
	int len = pwd.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_pwd, passwd, len);
	m_pwd[len] = '\0';
}
			
void CarpoolAccount::set_user_type(string u_type) {
	const char *utype = u_type.data();
	int len = u_type.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_utype, utype, len);
	m_utype[len] = '\0';
}
			
void CarpoolAccount::set_answer_sq_one(string ans_sq_one) {
	const char *answ_sq_one = ans_sq_one.data();
	int len = ans_sq_one.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_ans_sq_one, answ_sq_one, len);
	m_ans_sq_one[len] = '\0';
}
			
void CarpoolAccount::set_answer_sq_two(string ans_sq_two) {
	const char *answ_sq_two = ans_sq_two.data();
	int len = ans_sq_two.size();
	len = (len < MAX_LEN ? len : MAX_LEN - 1);
	strncpy(m_ans_sq_two, answ_sq_two, len);
	m_ans_sq_two[len] = '\0';
}

//Accessor Methods:
string CarpoolAccount::get_sjsu_id() const {
	return m_sj_id;
}
			
string CarpoolAccount::get_email() const {
	return m_email;
}
			
string CarpoolAccount::get_username() const {
	return m_uname;
}
			
string CarpoolAccount::get_address() const {
	return m_addr;
}
			
string CarpoolAccount::get_name() const {
	return m_name;
}
			
string CarpoolAccount::get_passwd() const {
	return m_pwd;
}
			
string CarpoolAccount::get_user_type() const {
	return m_utype;
}
			
string CarpoolAccount::get_answer_sq_one() const {
	return m_ans_sq_one;
}
			
string CarpoolAccount::get_answer_sq_two() const {
	return m_ans_sq_two;
}