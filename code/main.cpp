#include<iostream>
#include<string>
#include<cstring>
#include"bank.h"

using namespace std;

int main(){

    string input;
    int Login = 0;
    int ID;
    int Password; 
    char command[9][9] = {"login", "create", "delete", "merge", 
    "deposit", "withdraw", "transfer", "find", "search"};
    while(getline(cin, input)){
            char *cstring;
            char *tmp;
            cstring = new char[input.size() + 1];
            strncpy(cstring, input.c_str(), input.size() + 1);
            tmp = strtok(cstring, " ");
            
            for(int i = 0; i < 9; i++)
               if(strcmp(tmp, command[i]) == 0)
                   break;

           /* if(strncmp(tmp, "login", 5) == 0){
                tmp = strtok(NULL, " ");
                ID = atoi(tmp);
                tmp = strtok(NULL, " ");
                Password = atoi(tmp);
            
                if(ID.found){
                    if(passwordcorrect){
                        cout << "success" << endl;
                    }
                    else
                        cout << "wrong password" << endl;
                }
                else{
                    cout << "ID [" << ID << "] not found" << endl;
                }
            }

            else if(strncmp(tmp, "create", 6) == 0){
                tmp = strtok(NULL, " ");
                ID = atoi(tmp);
                tmp = strtok(NULL, " ");
                Password = atoi(tmp);
                if(ID.exist){
                    cout << "ID [" << ID << "] exists, ";
                    //suggest IDs
                }
                else{
                    cout << "success" << endl;
                }
            }

            *else if(strncmp(tmp, "delete", 6) == 0){
                cp1 = atoi(tmp);
                tmp = strtok(NULL, " ");
                cp2 = atoi(tmp);
                if(comsys[cp2].size >= merarg){
                    comsys[cp1].merge(comsys[cp2]);
                    cout << "The largest priority number is now " << comsys[cp1].top().pri << " on " << cp1 <<"." << endl;
                }
                else
                    cout << "Merging request failed." << endl;
            }
            */
    }
    return 0;
}
