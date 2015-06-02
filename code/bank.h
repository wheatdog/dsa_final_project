#include <vector>
#include <string>

using namespace std;

class Record {
	long long int money; // NOTE: + => transfer money from this account
                             //       - => receive money from other
        unsigned long long int time;
};

class History {
	string targetID;
	vector<Record> list;
};

class Account {
	string ID;
	string passwd;
	long long int money;
	Tree<History> history;

	public:
	long long int get_money_amount();
	int withdraw(long long int money);
	void deposit(long long int money);
	int search(string ID);
};

class Bank {
	int numAccount;
	Tree<Account> data;
        unsigned long long int history_counter;

	public:
	int create_account(string ID, string password); // TODO: check if ID exist, otherwise create.
        void recommend_and_print_ID(bool isExist, string ID, int num); 
	int delete_account(string ID, string password); 
	int login(string ID, string passwd, Account* &ptrAccount); 
        void find_and_print_wildcard_ID(string wildcardID); // NOTE: maybe a more efficient way?

        int merge(string IDFormer, string passwdFormer, string IDLatter, string passwdLatter);
	int transfer(Account* ptrFromAccount, string toAccountID, long long int money);

};

enum result {
	SUCCESS, FAIL,
	ID_NOT_FOUNT, WRONG_PASSWD,  //for login, delete
	ID1_NOT_FOUNT, WRONG_PASSWD1, ID2_NOT_FOUNT, WRONG_PASSWD2,  //for merge
	ID_EXIST,  //for create
	NO_RECORD  //for search
};

