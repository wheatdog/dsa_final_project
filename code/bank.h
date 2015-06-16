#include <list>
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
typedef pair<list<Record>,map<string,Account>::iterator> HistoryList; 

class Record {
    // NOTE: to this account, From => true, TO => false
    bool type; 
    Money money; 
    Time time;

    public:
    bool operator< (const Record& b)
    {
        return (time < b.time);
    }
    friend class Account;
    friend class Bank;
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
};

class Bank {
    int numAccount;
    map<string, Account> data;
    Time history_counter;

    void update_record(map<string, Account>::iterator ptrToAccount,
                       map<string, Account>::iterator ptrFromAccount,
                       Money money, bool type, Time history_counter);

    void change_record(map<string, HistoryList>::iterator itLatter,
                       map<string, Account>::iterator former_pos,
                       string IDFormer, string IDLatter);
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
    int transfer(Account* ptrFromAccount,
                 string toAccountID, Money _money);

};

enum result {
    SUCCESS, FAIL,
    ID_NOT_FOUND, WRONG_PASSWD,  // for login, delete, transfer
    ID1_NOT_FOUND, WRONG_PASSWD1, ID2_NOT_FOUND, WRONG_PASSWD2,  // for merge
    ID_EXIST,  // for create
    NO_RECORD  // for search
};

