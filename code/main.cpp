#include<iostream>
#include<string>
#include"bank.h"

using namespace std;

enum COMMAND {_LOGIN, _CREATE, _DELETE, _MERGE, _DEPOSIT,
              _WITHDRAW, _TRANSFER, _FIND, _SEARCH};

int GetCommand(string &Input)
{
    const string Command[] = 
    {"login", "create", "delete", "merge", "deposit",
        "withdraw", "transfer", "find", "search"};
    for (unsigned int i = 0; i < sizeof(Command) / sizeof(*Command); i++)
    {
        if (Input.compare(Command[i]) == 0)
            return i;
    }
    return -1;
}

int main() 
{
    string Input;
    Bank bank;
    Account* account = NULL;

    while (cin >> Input) {
        switch(GetCommand(Input)) {
            case _LOGIN:
            {
                string ID, passwd;
                cin >> ID >> passwd;
                int status = bank.login(ID, passwd, account);

                switch (status) { 
                    case SUCCESS:
                    {
                        cout << "success" << endl;
                    } break;

                    case ID_NOT_FOUND:
                    {
                        cout << "ID " << ID << " not found" << endl;
                    } break;

                    case WRONG_PASSWD:
                    {
                        cout << "wrong password" << endl;    
                    } break;

                    default:
                    {
                        cout << "something unexpected for login" << endl;
                    } break;
                }
            } break;

            case _CREATE:
            {
                string ID, passwd;
                cin >> ID >> passwd;
                int status = bank.create_account(ID, passwd);

                switch (status) {
                    case SUCCESS:
                    {
                        cout << "success" << endl;
                    } break;

                    case ID_EXIST:
                    {
                        cout << "ID " << ID << " exists, ";
                        bank.recommend_and_print_ID(false, ID, 10);
                    } break;

                    default:
                    {
                        cout << "something unexpected for create" << endl;
                    }
                }
            } break;

            case _DELETE:
            {
                string ID, passwd;
                cin >> ID >> passwd;
                int status = bank.delete_account(ID, passwd);

                switch (status){
                    case SUCCESS:
                    {
                        cout << "success" << endl;
                    } break;

                    case ID_NOT_FOUND:
                    {
                        cout << "ID " << ID << " not found" << endl;
                    } break;

                    case WRONG_PASSWD:
                    {
                        cout << "wrong password" << endl;    
                    } break;

                    default:
                    {
                        cout << "something unexpected for delete" << endl;
                    } break;
                }
            } break;

            case _MERGE:
            {
                string ID1, passwd1;
                string ID2, passwd2;

                cin >> ID1 >> passwd1;
                cin >> ID2 >> passwd2;
                int status = bank.merge(ID1, passwd1, ID2, passwd2);

                switch (status) {
                    case SUCCESS:
                    {
                        // TODO: merge method should return or fill in money for output
                        cout << "success, " << ID1 << " has " << " " << " dollars" << endl;
                    } break;

                    case ID1_NOT_FOUND:
                    {
                        cout << "ID " << ID1 << " not found" << endl;
                    } break;

                    case WRONG_PASSWD1:
                    {
                        cout << "wrong password1" << endl;    
                    } break;

                    case ID2_NOT_FOUND:
                    {
                        cout << "ID " << ID2 << " not found" << endl;
                    } break;

                    case WRONG_PASSWD2:
                    {
                        cout << "wrong password2" << endl;    
                    } break;

                    default:
                    {
                        cout << "something unexpected for merge" << endl;
                    } break;
                }
            } break;

            case _DEPOSIT:
            {
                Money money;
                cin >> money;
                account->deposit(money);
                cout << "success, " << account->get_money_amount() << " dollars in current account" << endl;
            } break;

            case _WITHDRAW:
            {
                Money money;
                cin >> money;

                int status = account->withdraw(money);

                switch(status) {
                    case SUCCESS:
                    {
                        cout << "success, " << account->get_money_amount() << " dollars left in current account" << endl;
                    } break;
                    
                    case FAIL:
                    {
                        cout << "fail, " << account->get_money_amount() << " dollars only in current account" << endl;
                    } break;

                    default:
                    {
                        cout << "something unexpected for withdraw" << endl;
                    } break;
                }    
            } break;

            case _TRANSFER:
            {
                string ID;
                Money money;

                cin >> ID >> money;
                    
                int status = bank.transfer(account, ID, money);

                switch(status) {
                    case SUCCESS:
                    {
                        cout << "success, " << account->get_money_amount() << " dollars left in current account" << endl;
                    } break;

                    case ID_NOT_FOUND:
                    {
                        cout << "ID " << ID << " not found, ";
                        bank.recommend_and_print_ID(true, ID, 10);
                    } break;

                    case FAIL:
                    {
                        cout << "fail, " << account->get_money_amount() << " dollars only in current account" << endl;
                    } break;

                    default:
                    {
                        cout << "something unexpected for transfer" << endl;
                    }
                }

            } break;

            case _FIND:
            {
                string wildcardID;

                cin >> wildcardID;
                bank.find_and_print_wildcard_ID(wildcardID);
            } break;

            case _SEARCH:
            {
                string ID;
                cin >> ID;

                int status = account->search(ID);
                switch(status) {
                    case ID_NOT_FOUND:
                    {
                        cout << "ID " << ID << " not found" << endl;
                    } break;

                    case NO_RECORD:
                    {
                        cout << "no record" << endl;
                    } break;

                    default:
                    {
                        cout << "something unexpected for search" << endl;
                    } break;
                }
            } break;

            default:
            {
                // TODO: maybe output usage.
                cout << "invalid command" << endl;
            } break;
        }
    }

    return 0;
}
