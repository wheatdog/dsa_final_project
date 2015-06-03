#include <vector>
#include <string>
#include <map>

#define FROM true
#define TO false

using namespace std;

typedef long long int Money;

class Record {
    // NOTE: to this account, From => true, TO => false
    bool type; 
    Money money; 
    unsigned long long int time;
};

typedef vector<Record> HistoryList;

class Account {
    string ID;
    string passwd;
    Money money;
    map<string, HistoryList> history;

    public:
    Acount(string initID, string initPasswd);
    Money get_money_amount();
    int withdraw(Money _money);
    void deposit(Money _money);
    int search(string ID);
};

class Bank {
    int numAccount;
    map<string, Account> data;
    unsigned long long int history_counter;

    public:

    Bank();

    // TODO: check if ID exist, otherwise create.
    int create_account(string ID, string password);
    void recommend_and_print_ID(bool isExist, string ID, int num); 
    int delete_account(string ID, string password); 
    int login(string ID, string passwd, Account* &ptrAccount); 
   
    // NOTE: maybe a more efficient way?
    void find_and_print_wildcard_ID(string wildcardID);

    int merge(string IDFormer, string passwdFormer, string IDLatter, string passwdLatter);
    int transfer(Account* ptrFromAccount, string toAccountID, Money _money);

    friend class Account; 
    friend class Record;
};

enum result {
    SUCCESS, FAIL,
    ID_NOT_FOUNT, WRONG_PASSWD,  // for login, delete, transfer
    ID1_NOT_FOUNT, WRONG_PASSWD1, ID2_NOT_FOUNT, WRONG_PASSWD2,  // for merge
    ID_EXIST,  // for create
    NO_RECORD  // for search
};

