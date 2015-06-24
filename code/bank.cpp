#include <map>
#include <iostream>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <cmath>
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

void Bank::change_record(Account* tofixAccount,
                         map<string, Account>::iterator former_pos,
                         string IDFormer, string IDLatter)
{
        map<string, HistoryList>::iterator tar_history_it =
            tofixAccount->history.find(IDLatter);
        map<string, HistoryList>::iterator fin_history_it =
            tofixAccount->history.find(IDFormer);

        if (fin_history_it != tofixAccount->history.end()) {
            fin_history_it->second.first.merge(tar_history_it->second.first);
            tofixAccount->history.erase(tar_history_it);
            return;
        }

        HistoryList tmp;
        tmp.second = former_pos;

        pair<map<string, HistoryList>::iterator,bool> ret =
            tofixAccount->history.insert(
                    pair<string, HistoryList>(IDFormer, tmp));

        // NOTE(wheatdog): swap list to avoid copy whole list
        // TODO(wheatdog): see if this is more efficient
        // heap? check heap order when elements are equal.
        swap(tmp.first, ret.first->second.first);

        tofixAccount->history.erase(tar_history_it);
        return;
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
        Account* tofixAccount = &(itLatter->second.second->second);
        change_record(tofixAccount, former_pos, IDFormer, IDLatter);

        // NOTE(wheatdog): merge history
        map<string, HistoryList>::iterator itFormer =
            former_pos->second.history.find(itLatter->first);

        // TODO(wheatdog): check if this work
        if (itFormer == former_pos->second.history.end()) {
            map<string, HistoryList>::iterator itLatterUp = itLatter;
            ++itLatterUp;
            former_pos->second.history.insert(itLatter, itLatterUp);
            continue;
        }

        // TODO(wheatdog): maybe do the merge when search
        itFormer->second.first.merge(itLatter->second.first);
    }

    // NOTE(wheatdog): delete account here
    // TODO(wheatdog): maybe need a robust test for list , or not...it is STL!
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

int Bank::transfer(Account* ptrFromAccount, string toAccountID, Money _money)
{

    if (_money > ptrFromAccount->money)
        return FAIL;

    map<string, Account>::iterator itToAccount = data.find(toAccountID);
    map<string, Account>::iterator itFromAccount = data.find((ptrFromAccount->ID));
    if (itToAccount == data.end())
        return ID_NOT_FOUND;

    itToAccount->second.money += _money;
    itFromAccount->second.money -= _money;

    update_record(itToAccount, itFromAccount, _money, TO, history_counter);
    update_record(itFromAccount, itToAccount, _money, FROM, history_counter);
    history_counter++;

    return SUCCESS;
}

void Bank::find_and_print_wildcard_ID(string wildcardID)
{
    for(map<string, Account>::iterator it = data.begin(); it != data.end(); it++){
                if(matchwild(wildcardID, (it->first)) == true)
            cout << it->first << endl;
    }
    return;
}

// NOTE(gary):
// http://www.drdobbs.com/architecture-and-design/matching-wildcards-an-empirical-way-to-t/240169123
bool Bank::matchwild(string wstring, string comstring)
{
    string::iterator cstr = comstring.begin();
    string::iterator wcstr = wstring.begin();
    string::iterator mark, wmark;

    while (1)
    {
        if(*wcstr == '*')
        {
            while(*(++wcstr) == '*')
            {
            }
            if(!*wcstr)
                return true;
            if(*wcstr != '?')
            {
                while(*cstr != *wcstr)
                {
                    if(!(*(++cstr)))
                        return false;
                }
            }
            mark = cstr;
            wmark = wcstr;
        }
        else if (*cstr != *wcstr && *wcstr != '?')
        {
            if(wmark != wstring.end())
            {
                if(wcstr != wmark)
                {
                    wcstr = wmark;
                    if(*cstr != *wcstr)
                    {
                        cstr = ++mark;
                        continue;
                    }
                    else
                        wcstr++;
                }
                if(*cstr)
                {
                    cstr++;
                    continue;
                }
            }
            return false;
        }
        cstr++;
        wcstr++;
        if(!*cstr)
        {
            while(*wcstr == '*')
            {
                wcstr++;
            }
            if(!*wcstr)
                return true;
            return false;
        }
    }
}

static const char startChars[] = {'0', 'A', 'a'};
static const char endChars[] = {'9', 'Z', 'z'};

static bool is_perfect_square(int num){
	assert(num >= 0);
	int tst = (int)(sqrt(num) + 0.5);
	  return (tst*tst == num);
}
static int min(int a, int b){
	return ((a < b)? a:b);
}
int Bank::extend_str_and_print(bool isExist, int num, string strExtend, int numExtended, int score, const string& str){
	assert(score >= 0);
	if(score == 0){
        if ((data.count(str + strExtend) == 1) == isExist){
            if (num == 1)
                cout << str << strExtend << endl;
            else
                cout << str << strExtend << ",";
            return 1;
        }else{
            return 0;
        }
	}

	int numPrinted = 0;
	numExtended++;
	for(unsigned int i = 0; i < sizeof(startChars)/sizeof(char) && numPrinted < num; i++){
		for(char c = startChars[i]; c <= endChars[i] && numPrinted < num; c++){
			numPrinted += extend_str_and_print(isExist, num - numPrinted, strExtend + c, numExtended, score - numExtended, str);
		}
	}
	return numPrinted;
}

int Bank::find_with_score_and_print(bool isExist, int num, string mdfyStr, int reversePos, int numChanged, int lengthRM, int score, const string& str){
	//cout << "rPos = " << reversePos << " original str = " << mdfyStr << endl;
	assert(score >= 0);
	if(reversePos == 0){
		if(score == 0){
			//cout << "rPos and score = 0    " << endl;
            if ((data.count(mdfyStr) == 1) == isExist){
                if (num == 1)
                    cout << mdfyStr << endl;
                else
                    cout << mdfyStr << ",";
                return 1;
            }else{
                return 0;
            }
		}
		if(lengthRM == 0 && mdfyStr.length() <= 100 && is_perfect_square(8*score + 1)){
			//cout << "score = " << score << " call extend\n" << endl;
			return extend_str_and_print(isExist, num, string(), 0, score, mdfyStr);
		}
		//cout << "invalid. score is still " << score << endl;
		return 0;
	}
	int numPrinted = 0;
	string strBegin(mdfyStr);
	int reversePosBegin = reversePos;
	int lengthRMBegin = lengthRM;
	int pos = mdfyStr.length() - reversePos;
	int scoreBegin = score;
	if(score + reversePos*numChanged == (1 + reversePos + 2*lengthRM)*reversePos/2 && pos > 0){
		//cout << "current pos to end can be remove:\n";
        if ((data.count(mdfyStr.substr(0, pos)) == 1) == isExist){
            if (num == 1)
                cout << mdfyStr.substr(0, pos) << endl;
            else
                cout << mdfyStr.substr(0, pos) << ",";
            numPrinted++;
        }
	}
	if(score < reversePos){
		int numCanRM = min(reversePos - 1, numChanged - lengthRM - 1);
		if(score + (2*(numChanged - lengthRM) - numCanRM -1)*numCanRM/2 >= reversePos - numCanRM){
			//cout << "score = " << score<< "remove can gain max " <<(2*(numChanged - lengthRM) - numCanRM -1)*numCanRM/2<<" scores\n";
			//cout << "reversePos min : " << reversePos - numCanRM << endl;
			int i;
			for(i=1; score < reversePos; i++){
				score += (numChanged - lengthRM - i);
				mdfyStr.pop_back();
				lengthRM++;
				reversePos--;
				//cout << "remove "<<i<<endl;
				//cout << "\tstring: " << mdfyStr <<endl;
				//cout << "\tlengthRM: "<< lengthRM <<endl;
				//cout << "\treversePos: "<< reversePos<<endl;
				//cout << "\tscore become: "<< score<< endl;
			}
			//cout << "remove " << i-1 << " to change rPos " << reversePos << endl;
		}else{
			return numPrinted + find_with_score_and_print(isExist, num, mdfyStr, reversePos - 1, numChanged, lengthRM, score, str);
		}
	}
	score -= reversePos;
	for(unsigned int i = 0; i < sizeof(startChars)/sizeof(char) && numPrinted < num; i++){
		for(char c = startChars[i]; c <= endChars[i] && numPrinted < num; c++){
			mdfyStr[pos] = c;
			//cout << "c = " << c << " pos: " << pos << " str become: " << (isChanged? mdfyStr:strBegin) << endl;
			//cout << "score remain: " << (isChanged? (score-reversePos):score) << endl;
			if(c != str[pos]){
				numPrinted += find_with_score_and_print(isExist, num - numPrinted, mdfyStr,
									reversePos - 1, numChanged+1,
									lengthRM, score, str);
			}else{
				numPrinted += find_with_score_and_print(isExist, num - numPrinted, strBegin,
									reversePosBegin - 1, numChanged,
									lengthRMBegin, scoreBegin, str);
			}
		}
	}
	return numPrinted;
}
static bool compare_score(const StrAndScore& f, const StrAndScore& l){
	return (f.score < l.score);
}
int Bank::count_score(const string& strF, const string& strL){
	int commonLength = min(strF.size(), strL.size());
	int diffLength = abs(strF.size() - strL.size());
	int score = (1 + diffLength)*diffLength/2;
	for(int i = 0; i < commonLength; i++){
		if(strF[i] != strL[i])
			score += (commonLength - i);
	}
	return score;
}

void Bank::sort_score_and_print(int num, const string& str){
	vector<StrAndScore> scoreTable;
	scoreTable.reserve(data.size() + 1);

	for(map<string, Account>::iterator it = data.begin(); it != data.end(); ++it){
		scoreTable.push_back(StrAndScore(it, count_score(it->first, str)));
	}
	stable_sort(scoreTable.begin(), scoreTable.end(), compare_score);
	if(data.size() < (unsigned int)num)
		num = data.size();
	vector<StrAndScore>::iterator it = scoreTable.begin();
	for(int i = 1; i <= num; ++i, ++it){
		cout << (it->mapIt->first) << ((i == num)? '\n':',');
	}
}
void Bank::recommend_and_print_ID(bool isExist, const string& ID, int num){
        int score = 1;
	if(isExist){
		sort_score_and_print(num, ID);
	}else{
		while(num > 0){
			num -= find_with_score_and_print(isExist, num, ID, min(score, ID.length()), 0, 0, score, ID);
			score++;
		}
	}
}
