#include <vector>
#include <ctime>
#include <string>

using namespace std;

class Record {
	long long int money;
	time_t time;

	public:
	Record(long long int moneyTransfer, time_t timeTransfer);
};
class History {
	string toID;
	vector<Record> list;

	public:
	History(string toID);
};
class Account {
	string ID;
	string passwd;
	long long int money;
	Tree<History> history;

	public:
	Account(string initID, string initPasswd);
	long long int get_money_amount();
	int withdraw(long long int money);
	void deposit(long long int money);
	int search(string ID);
};

class Bank {
	int numAccount;
	Tree<Account> data;

	public:
	Bank();
	int creat_account(string ID, string passwd);
	void recommend_and_print_ID(bool isExist, string ID, int num);
	int delete_account(string ID, string passwd);
	int login(string ID, string passwd, Account* &ptrAccount);
	int merge(string IDFormer, string passwdFormer, string IDLatter, string passwdLatter);
	int transfer(Account* ptrFromAccount, string toAccountID, long long int money);
	void find_and_print_wildcard_ID(string wildcardID);

};
enum result {
	SUCCESS, FAIL,
	ID_NOT_FOUNT, WRONG_PASSWD,  //for login, delete
	ID1_NOT_FOUNT, WRONG_PASSWD1, ID2_NOT_FOUNT, WRONG_PASSWD2,  //for merge
	ID_EXIST,  //for create
	NO_RECORD  //for search
};

