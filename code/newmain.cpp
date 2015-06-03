#include<iostream>
#include<string>
#include<cstdlib>
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

    //Account* acptr = NULL;

    while (cin >> Input)
    {
        switch(GetCommand(Input))
        {

            case _LOGIN:
            {
                string ID, passwd;
                cin >> ID >> passwd;
                //bank.login(ID, passwd, acptr)
                switch (0) { 
                    case SUCCESS:
                        cout << "success" << endl;
                        break;
                    case ID_NOT_FOUND:
                        cout << "ID " << ID << " not found" << endl;
                        break;
                    case WRONG_PASSWD:
                        cout << "wrong password" << endl;    
                        break;
                    default:
                        cout << "something unexpected for login" << endl;
                }

            } break;

            case _CREATE:
            {
            } break;

            case _DELETE:
            {
            } break;

            case _MERGE:
            {
            } break;

            case _DEPOSIT:
            {
            } break;

            case _WITHDRAW:
            {
            } break;

            case _TRANSFER:
            {
            } break;

            case _FIND:
            {
            } break;

            case _SEARCH:
            {
            } break;

            default:
            {
                // TODO: maybe output usage.
                exit(-1);
            } break;
        }
    }

    return 0;
}
