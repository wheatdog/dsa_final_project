#include<iostream>
#include<string>
#include<cstring>
#include"bank.h"
#include"bank.cpp"

using namespace std;

int main(){

    string input;
    int Login = 0;
    char command[9][9] = {"login", "create", "delete", "merge", 
    "deposit", "withdraw", "transfer", "find", "search"};
    
    Bank bank;

    while(getline(cin, input)){
            char *cstring;
            char *tmp;
            int i;
            cstring = new char[input.size() + 1];
            strncpy(cstring, input.c_str(), input.size() + 1);
            tmp = strtok(cstring, " ");

            for( i = 0; i < 9; i++)
               if(strcmp(tmp, command[i]) == 0)
                   break;

            if(i >= 4 && Login == 0){
                cout << "Not Log in yet or invalid command" << endl;
                break;
            }

            switch (i) {
                case 0:
                    { 
                    tmp = strtok(NULL, " ");
                    string ID(tmp);
                    tmp = strtok(NULL, " ");
                    string Password(tmp);
                    //Account* acptr;
                    switch (/*bank.login(ID, Password, acptr)*/) { 
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
                    }
                    break;

                case 1:
                    {
                    tmp = strtok(NULL, " ");
                    string ID(tmp);
                    tmp = strtok(NULL, " ");
                    string Password(tmp);
                    
                    switch (/*bank.create_account(ID, Password)*/){
                        case SUCCESS:
                            cout << "success" << endl;
                            break;
                        case ID_EXIST:
                            {
                            cout << "ID " << ID << " exists, ";
                            bank.recommend_and_print_ID;
                            }
                            break;
                        default:
                            cout << "something unexpected for create" << endl;
                    }
                    }
                    break;
                
                case 2:
                    {
                    tmp = strtok(NULL, " ");
                    string ID(tmp);
                    tmp = strtok(NULL, " ");
                    string Password(tmp);
                    
                    switch (/*bank.delete_account(ID, Password)*/){
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
                            cout << "something unexpected for delete" << endl;
                    }
                    }
                    break;

                case 3:
                    {
                    tmp = strtok(NULL, " ");
                    string ID1(tmp);
                    tmp = strtok(NULL, " ");
                    string Password1(tmp);
                    tmp = strtok(NULL, " ");
                    string ID2(tmp);
                    tmp = strtok(NULL, " ");
                    string Password2(tmp);
                    
                    switch (/*bank.merge(ID1, Password1, ID2, Password2)*/){
                        case SUCCESS:
                            cout << "success, " << ID1 << " has " << /*function call */ << " dollars" << endl;
                            break;
                        case ID1_NOT_FOUND:
                            cout << "ID " << ID1 << " not found" << endl;
                            break;
                        case WRONG_PASSWD1:
                            cout << "wrong password1" << endl;    
                            break;
                         case ID2_NOT_FOUND:
                            cout << "ID " << ID2 << " not found" << endl;
                            break;
                        case WRONG_PASSWD2:
                            cout << "wrong password2" << endl;    
                            break;
                        default:
                            cout << "something unexpected for merge" << endl;
                    }
                    }
                    break;

                case 4:
                    {
                    tmp = strtok(NULL, " ");
                    Money num = atoll(tmp);
                    // bank.Account.deposit(num);
                    cout << "success, " << /*bank.Account.get_money_amount()*/ << " dollars in current account" << endl;
                    }
                    break;

                case 5:
                    {
                    tmp = strtok(NULL, " ");
                    Money num = atoll(tmp);
                    switch(/*bank.Account.withdraw(num)*/){
                        case SUCCESS:
                            cout << "success, " << bank.Account.get_money_amount() << " dollars left in current account" << endl;
                            break;
                        case FAIL:
                            cout << "fail, " << bank.Account.get_money_amount() << " dollars only in current account" << << endl;
                            break;
                        default:
                            cout << "something unexpected for withdraw" << endl;
                    }    
                    }
                    break;

                case 6:
                    {
                    tmp = strtok(NULL, " ");
                    string ID(tmp);
                    tmp = strtok(NULL, " ");
                    Money num = atoll(tmp);
                    
                    switch(/*bank.transfer((&bank.Account), ID, num)*/){
                        case SUCCESS:
                            cout << "success, " << /*bank.Account.get_money_amount()*/ << " dollars left in current account" << endl;
                            break;
                        case ID_NOT_FOUND:
                            cout << "ID " << ID << " not found" << endl;
                            break;
                        case FAIL:
                            cout << "fail, " << /*bank.Account.get_money_amount()*/ << " dollars only in current account" << << endl;
                            break;
                        default:
                            cout << "something unexpected for transfer" << endl;
                    }
                    }
                    break;
    
                case 7:
                    {
                    tmp = strtok(NULL, " ");
                    string WildcardID(tmp);
                    //find_and_print_wildcard_ID(WildcardID);
                    }
                    break;

                case 8:
                    {
                    tmp = strtok(NULL, " ");
                    string ID(tmp);
                    switch(/*bank.Account.search(ID)*/){
                        case ID_NOT_FOUND:
                            cout << "ID " << ID << " not found" << endl;
                            break;
                        case NO_RECORD:
                            cout << "no record" << endl;
                            break;
                        default:
                            cout << "something unexpected for search" << endl;
                    }
                    }
                    break;
        
                default:
                    cout << "invalid command" << endl;
            }                    
    }  
    return 0;
}
