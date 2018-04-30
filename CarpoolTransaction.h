#ifndef CARPOOLTRANSACTION_H
#define	CARPOOLTRANSACTION_H

#include <mysql/mysql.h>
#include "CarpoolAccount.h"

class CarpoolTransaction;
typedef CarpoolTransaction* CarpoolTransactionPtr;

class CarpoolTransaction {
	public:
		//Parameterized Default Constructor
			CarpoolTransaction();

		//Default Destructor
			~CarpoolTransaction();

		//Transactions:
			bool MySQL_Connect(const string HOST, const string USER,
				const string PASSWORD, const string DB_NAME);

			bool Sign_Up(CarpoolAccountPtr);
			void MaskPassword(string &passwd);
			bool Is_PasswordValid(string &passwd, string temp_passwd);
			void CaesarCipher(string &passwd);
			bool Is_SJID_Valid(string sjid);
			bool Is_Utype_Valid(string utype);

			string Sign_In(string uname, string passwd, bool &SignIn);
			void GetSignInData();
			bool EditAccount(const string attribute, string sjid, const string attribute_value);
			void DeleteAccount(const string sjid);
			bool GetPasswdAttribute(const string passwd, const string sjid);
						
			bool GetDriverInfo(const string sjid);
			bool AddDriverInfo(const string lic_no, const string sjid, const string exp_date);

			void message(string);

	private:
			MYSQL *db_conn;
};

#endif	//CARPOOL TRANSACTION
