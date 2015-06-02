#include <bank.h>
#include <map>
#include <iostream>

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

int Bank::merge(string IDFormer, string passwdFormer, 
            string IDLatter, string passwdLatter)
{
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
    target_pos->history.insert(newList);

    return;
}

int Bank::transfer(Account* ptrFromAccount, string toAccountID, Money _money)
{
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
