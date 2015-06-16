#include <map>
#include <iostream>
#include <cassert>
#include <iterator>
#include "bank.h"
#include "md5.h"

using namespace std;


Account::Account(string initID, string initPasswd): ID(initID), money(0){
    passwd = md5(initPasswd);
}

Money Account::get_money_amount()
{
    return money;
}

int Account::withdraw(Money _money)
{
    if (_money > money)
        return FAIL;

    money -= _money;
    return SUCCESS;
}

void Account::deposit(Money _money)
{
    money += _money;
    return;
}

int Account::search(string ID)
{
    map<string, HistoryList>::iterator position = history.find(ID);

    if (position == history.end())
        return FAIL;

    if (history.empty())
        return NO_RECORD;

    list<Record> curlist = position->second.first;
    for (list<Record>::iterator it = curlist.begin(); it != curlist.end(); ++it) {
        if (it->type == FROM)
            cout << "From ";
        else
            cout << "To "; 
        cout << ID << it->money << endl;
    }

    return SUCCESS;
}

Bank::Bank()
{
   numAccount = 0;
   history_counter = 0;
}

int Bank::create_account(string ID, string password) {
    if(data.count(ID) != 0)
	    return ID_EXIST;

    Account newAccount(ID, password);
    data.insert(pair<string, Account>(ID, newAccount));
    
    // NOTE(wheatdog): can this work?
    // data[ID] = newAccount;
    return SUCCESS;
}

int Bank::delete_account(string ID, string password) {
    map<string, Account>::iterator it = data.find(ID);
    if(it == data.end())
	    return ID_NOT_FOUND;

    if(it->second.passwd != md5(password))
	    return WRONG_PASSWD;

    data.erase(it);
    return SUCCESS;
}

int Bank::login(string ID, string passwd, Account* &ptrAccount){
    map<string, Account>::iterator it = data.find(ID);
    if(it == data.end())
	    return ID_NOT_FOUND;

    if(it->second.passwd != md5(passwd))
	    return WRONG_PASSWD;

    ptrAccount = &(it->second);
    return SUCCESS;
}

void Bank::change_record(map<string, HistoryList>::iterator itLatter,
                         map<string, Account>::iterator former_pos,
                         string IDFormer, string IDLatter)
{
        Account* tofixAccount = &(itLatter->second.second->second);
        map<string, HistoryList>::iterator tar_history_it = 
            tofixAccount->history.find(IDLatter);
        map<string, HistoryList>::iterator fin_history_it = 
            tofixAccount->history.find(IDFormer);

        if (fin_history_it != tofixAccount->history.end()) {
            fin_history_it->second.first.merge(tar_history_it->second.first);
        }
        else {
            HistoryList tmp; 
            tmp.second = former_pos;

            pair<map<string, HistoryList>::iterator,bool> ret = 
                tofixAccount->history.insert(
                    pair<string, HistoryList>(IDFormer, tmp));

            // NOTE(wheatdog): swap list
            swap(tmp.first, ret.first->second.first);
        }

        tofixAccount->history.erase(tar_history_it);
       
}

int Bank::merge(string IDFormer, string passwdFormer, 
                string IDLatter, string passwdLatter)
{
    map<string, Account>::iterator former_pos = data.find(IDFormer);
    if (former_pos == data.end())
        return ID1_NOT_FOUND;
    map<string, Account>::iterator latter_pos = data.find(IDFormer);
    if (latter_pos == data.end())
        return ID2_NOT_FOUND;
    if (md5(passwdFormer) != former_pos->second.passwd)
        return WRONG_PASSWD1;
    if (md5(passwdLatter) != latter_pos->second.passwd)
        return WRONG_PASSWD2;
    
    former_pos->second.money += latter_pos->second.money;

    // NOTE(wheatdog): merge histories
    for (map<string, HistoryList>::iterator itLatter =
            latter_pos->second.history.begin();
         itLatter != latter_pos->second.history.end();
         ++itLatter)
    {

        // NOTE(wheatdog): change transfer history...
        change_record(itLatter, former_pos, IDFormer, IDLatter);

        // NOTE(wheatdog): merge history
        map<string, HistoryList>::iterator itFormer = 
            former_pos->second.history.find(itLatter->first);

        if (itFormer == former_pos->second.history.end()) {
            map<string, HistoryList>::iterator itLatterUp = itLatter;
            ++itLatterUp;
            former_pos->second.history.insert(itLatter, itLatterUp);
            continue;
        }

        itFormer->second.first.merge(itLatter->second.first);
    }

    // NOTE(wheatdog): delete account here
    data.erase(latter_pos);

    return SUCCESS;
}

void Bank::update_record(map<string, Account>::iterator ptrToAccount,
                         map<string, Account>::iterator ptrFromAccount,
                         Money _money, bool type, Time history_counter)
{
    map<string, HistoryList>::iterator target_pos =
        ptrToAccount->second.history.find(ptrFromAccount->second.ID);

    Record out;
    out.type = type;
    out.money = _money;
    out.time = history_counter;

    // NOTE(wheatdog): if name is found in history list
    if (target_pos != ptrToAccount->second.history.end()) {
            target_pos->second.first.push_back(out);
        return;
           
    }

    // NOTE(wheatdog): if not found, insert one in the list
    list<Record> tmp(1, out);
    HistoryList newList =  make_pair(tmp, ptrFromAccount);
    ptrToAccount->second.history.insert(
            pair<string, HistoryList>(ptrFromAccount->second.ID, newList));

    return;
       
}

int Bank::transfer(map<string, Account>::iterator ptrFromAccount,
                   string toAccountID, Money _money)
{

    if (_money > ptrFromAccount->second.money)
        return FAIL;

    map<string, Account>::iterator ptrToAccount = data.find(toAccountID);

    if (ptrToAccount == data.end())
        return ID_NOT_FOUND;

    ptrToAccount->second.money += _money;
    ptrFromAccount->second.money -= _money;

    update_record(ptrToAccount, ptrFromAccount, _money, TO, history_counter++);
    update_record(ptrFromAccount, ptrToAccount, _money, FROM, history_counter++);

    return SUCCESS;
}
