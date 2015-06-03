#include <map>
#include <iostream>
#include <cassert>
#include <iterator>
#include "bank.h"
#include "md5.h"

using namespace std;

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

    for (vector<Record>::iterator it = position->second.begin();
         it != position->second.end();
         ++it) {
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

int Bank::merge(string IDFormer, string passwdFormer, 
                string IDLatter, string passwdLatter)
{
    map<string, Account>::iterator former_pos = data.find(IDFormer);

    if (former_pos == data.end())
        return ID1_NOT_FOUND;

    map<string, Account>::iterator latter_pos = data.find(IDFormer);

    if (latter_pos == data.end())
        return ID2_NOT_FOUND;

    // TODO(wheatdog): MD5
    if (md5(passwdFormer) != former_pos->second.passwd)
        return WRONG_PASSWD1;
    
    // TODO(wheatdog): MD5
    if (md5(passwdLatter) != latter_pos->second.passwd)
        return WRONG_PASSWD2;
    
    former_pos->second.money += latter_pos->second.money;

    // NOTE(wheatdog): merge histories
    for (map<string, HistoryList>::iterator 
            itLatter = latter_pos->second.history.begin();
         itLatter != latter_pos->second.history.end();
         ++itLatter)
    {
        map<string, HistoryList>::iterator itFormer = 
            former_pos->second.history.find(itLatter->first);

        if (itFormer == former_pos->second.history.end()) {
            map<string, HistoryList>::iterator itUp = itLatter;
            ++itUp;
            former_pos->second.history.insert(itLatter, itUp);
            continue;
        }

        HistoryList old(itFormer->second.begin(), itFormer->second.end());
        HistoryList out;
        HistoryList::iterator itHLFormer = itFormer->second.begin();
        HistoryList::iterator itHLLatter = itLatter->second.begin();

        out.reserve(itFormer->second.size() + itLatter->second.size());

        while ((itHLFormer != itFormer->second.end()) &&
                (itHLLatter != itLatter->second.end())) {
            if (itHLFormer->time < itHLLatter->time) {
                out.push_back(*itHLFormer);
                ++itHLFormer;
            }
            else {
                out.push_back(*itHLLatter);
                ++itHLLatter;
            }
        }

        while (itHLFormer != itFormer->second.end()) {
                out.push_back(*itHLFormer);
                ++itHLFormer;
        }

        while (itHLLatter != itLatter->second.end()) {
                out.push_back(*itHLLatter);
                ++itHLLatter;
        }
    }

    // NOTE(wheatdog): change transfer history...



    // NOTE(wheatdog): delete account here
    // TODO(wheatdog): seach id again... maybe use a iterator one instead
    // uncomment this after implement this function!!
    //delete_account(IDLatter, passwdLatter); 

    return SUCCESS;
}

// TODO(wheatdog): maybe change this to a privite method of class Bank?
void update_record(Account* ptrToAccount, Account* ptrFromAccount,
                   Money _money, bool type, long long int history_counter)
{
    map<string, HistoryList>::iterator source_pos =
        ptrToAccount->history.find(ptrFromAccount->ID);

    Record out;
    out.type = type;
    out.money = _money;
    out.time = history_counter;

    // NOTE(wheatdog): if name is found in history list
    if (source_pos != ptrToAccount->history.end()) {
        source_pos->second.push_back(out);
        return;
    }

    // NOTE(wheatdog): if not found, insert one in the list
    HistoryList newList(1, out);
    ptrToAccount->history.insert(
            pair<string, HistoryList>(ptrFromAccount->ID, newList));

    return;
}

int Bank::transfer(Account* ptrFromAccount, string toAccountID, Money _money)
{
    // TODO(wheatdog): check if necessary?
    assert(_money >= 0);

    if (_money > ptrFromAccount->money)
        return FAIL;

    map<string, Account>::iterator target_pos = data.find(toAccountID);
    Account* ptrToAccount = &(target_pos->second);

    if (target_pos == data.end())
        return ID_NOT_FOUND;

    ptrToAccount->money += _money;
    ptrFromAccount->money -= _money;

    update_record(ptrToAccount, ptrFromAccount, _money, TO, history_counter++);
    update_record(ptrFromAccount, ptrToAccount, _money, FROM, history_counter++);

    return SUCCESS;
}
