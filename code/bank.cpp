#include <bank.h>
#include <map>
#include <iostream>
#include <assert>

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

int Account::deposit(Money _money)
{
    money += _money;
    return SUCCESS;
}

int Account::search(string ID)
{
    Map<string, HistoryList>::iterator position = history.find(ID);

    if (position == data.end())
        return FAIL;

    if (history.empty())
        return NO_RECORD;

    for (vector<Record>::iterator it = position->begin(),
         it != history.end(),
         ++it) {
        cout << (it->type == FROM)? "From " : "To " << ID << it->money << endl;
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
    Map<string, Account>::iterator former_pos = data.find(IDFormer);

    if (former_pos == data.end())
        return ID1_NOT_FOUNT;

    Map<string, Account>::iterator latter_pos = data.find(IDFormer);

    if (latter_pos == data.end())
        return ID2_NOT_FOUNT;

    // TODO(wheatdog): MD5
    if (SOMETHING_MD5(passwdFormer) != former_pos->passwd)
        return WRONG_PASSWD1;
    
    // TODO(wheatdog): MD5
    if (SOMETHING_MD5(passwdLatter) != latter_pos->passwd)
        return WRONG_PASSWD2;
    
    former_pos->money += latter_pos->money;

    for (Map<string, HistoryList>::iterator 
            itLatter = latter_pos->history.begin();
         itLatter != latter_pos->history.end();
         ++itLatter)
    {
        Map<string, HistoryList>::iterator itFormer = 
            former_pos->history.find(itLatter->first);

        if (itFormer == former_pos->history.end()) {
            former_pos->history.insert(itLatter, next(itLatter));
            continue;
        }

        HistoryList old(itTarget->begin(), itTarget->end());

        HistoryList::iterator itHLFormer = itFormer->begin();
        HistoryList::iterator itHLLatter = itLatter->begin();

        while ((itHLFormer != itFormer->end()) &&
                (itHLLatter != itLatter->end())) {
            if ()
        }


    }

    // TODO(wheatdog): may use a iterator one instead
    delete_account(IDLatter, passwdLatter); 

    return SUCCESS;
}

void update_record(Map<string, Account>::iterator target_pos, 
                   Account* ptrFromAccount,
                   Money money, bool type, long long int history_counter)
{
    Map<string, HistoryList>::iterator source_pos =
        target_pos->history.find(ptrFromAccount->ID);

    Record out;
    out.type = type;
    out.money = _money;
    out.time = history_counter;

    if (source_pos != target_pos->history.end()) {
        source_pos->push_back(out);
        return;
    }

    HistoryList newList(1, out);
    target_pos->history.insert(
            pair<string, HistoryList>(ptrFromAccount->ID, newList);

    return;
}

int Bank::transfer(Account* ptrFromAccount, string toAccountID, Money _money)
{
    assert(_money >= 0);

    if (_money > ptrFromAccount->money)
        return FAIL;

    Map<string, Account>::iterator target_pos = data.find(ID);

    if (position == data.end()) {
        recommend_and_print_ID(0, toAccountID, 10);
        return ID_NOT_FOUNT;
    }

    target_pos->money += _money;
    ptrFromAccount->money -= _money;

    update_record(target_pos, ptrFromAccount, _money, TO, history_counter++);
    update_record(ptrFromAccount, target_pos, _money, FROM, history_counter++);

    return SUCCESS;
}
