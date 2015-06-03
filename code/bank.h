#include <vector>
#include <string>
#include <map>

#define FROM true
#define TO false

using namespace std;

class Record;
class Account;
class Bank;

typedef long long int Money;
typedef unsigned long long int Time;

// TODO(wheatdog): maybe a link list?
typedef vector<Record> HistoryList; 

class Record {
    // NOTE: to this account, From => true, TO => false
    bool type; 
    Money money; 
    Time time;

    friend class Account;
    friend class Bank;
    friend void update_record(Account* ptrToAccount, Account* ptrFromAccount,
                   Money money, bool type, Time history_counter);
};

class Account {
    string ID;
    string passwd;
    Money money;
    map<string, HistoryList> history;

    public:
    Account(string initID, string initPasswd);
    Money get_money_amount();
    int withdraw(Money _money);
    void deposit(Money _money);
    int search(string ID);

    friend class Bank;
    friend void update_record(Account* ptrToAccount, Account* ptrFromAccount,
                   Money money, bool type, Time history_counter);
};

class Bank {
    int numAccount;
    map<string, Account> data;
    Time history_counter;

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

};

enum result {
    SUCCESS, FAIL,
    ID_NOT_FOUND, WRONG_PASSWD,  // for login, delete, transfer
    ID1_NOT_FOUND, WRONG_PASSWD1, ID2_NOT_FOUND, WRONG_PASSWD2,  // for merge
    ID_EXIST,  // for create
    NO_RECORD  // for search
};

