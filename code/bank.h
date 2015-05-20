#include <vector>
#include <ctime>
#include <string>

using namespace std;

class History {
	long long int money;
	time_t time;
	string fromID;
	string toID;
};

class Account {
	long long int money;
	vector<History> history;

	public:
	void withdraw();
	void deposit();
	void search();
};

class Bank{
	int numAccount;
	Tree<Account> data;

	public:
	void creat_account();
	void delete_account();
	Account login();
	void transfer(Account acc, string ID);
	Account merge(Account acc, string ID);
};
