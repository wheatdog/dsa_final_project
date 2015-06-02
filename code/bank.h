#include <vector>
#include <string>
#include <map>

#define FROM true
#define TO false

using namespace std;

typedef Money long long int;
typedef HistoryList vector<Record>;

class Record {
    // NOTE: to this account, From => true, TO => false
    bool type; 
    Money money; 
    unsigned long long int time;
};

class Account {
    string ID;
    string passwd;
    Money money;
    Map<string, HistoryList> history;

    public:
    Money get_money_amount();
    int withdraw(Money _money);
    void deposit(Money _money);
    int search(string ID);
};

class Bank {
    int numAccount;
    Map<string, Account> data;
    unsigned long long int history_counter;

    public:

    // TODO: check if ID exist, otherwise create.
    int create_account(string ID, string password);
    void recommend_and_print_ID(bool isExist, string ID, int num); 
    int delete_account(string ID, string password); 
    int login(string ID, string passwd, Account* &ptrAccount); 
   
    // NOTE: maybe a more efficient way?
    void find_and_print_wildcard_ID(string wildcardID);

    int merge(string IDFormer, string passwdFormer, string IDLatter, string passwdLatter);
    int transfer(Account* ptrFromAccount, string toAccountID, Money _money);

    friend class Account, Record;
};

enum result {
    SUCCESS, FAIL,
    ID_NOT_FOUNT, WRONG_PASSWD,  // for login, delete, transfer
    ID1_NOT_FOUNT, WRONG_PASSWD1, ID2_NOT_FOUNT, WRONG_PASSWD2,  // for merge
    ID_EXIST,  // for create
    NO_RECORD  // for search
};

