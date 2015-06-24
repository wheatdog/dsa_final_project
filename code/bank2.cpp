#include "md5.h"
Acount::Acount(string initID, string initPasswd): ID(initID), money(0){
    passwd = md5(initPasswd);
}
int Bank::create_account(string ID, string password){
    if(data.count(ID) != 0)
	    return ID_EXIST;

    Account newAccount(ID, password);
    data[ID] = newAccount;
    return SUCCESS;
}

void Bank::recommend_and_print_ID(bool isExist, const string& ID, int num){
	int score = 1, numAns = 0;
	while(numAns < num){
		numAns += find_with_score_and_print(isExist, ID, score);
		score++;
	}
}
int Bank::delete_account(string ID, string password){
    map<string, Account>::iterator it = data.find(ID);
    if(it == data.end())
	    return ID_NOT_FOUNT;

    if(it->passwd != md5(password))
	    return WRONG_PASSWD;

    data.erase(it);
    return SUCCESS;
}
int Bank::login(string ID, string passwd, Account* &ptrAccount){
    map<string, Account>::iterator it = data.find(ID);
    if(it == data.end())
	    return ID_NOT_FOUNT;

    if(it->passwd != md5(passwd))
	    return WRONG_PASSWD;

    ptrAccount = &(it->second);
    return SUCCESS;
}
