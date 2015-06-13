#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
using namespace std;
static const char startChars[] = {'0', 'A', 'a'};
static const char endChars[] = {'9', 'Z', 'z'};

bool is_perfect_square(int num){
	assert(num >= 0);
	int tst = (int)(sqrt(num) + 0.5);
	  return (tst*tst == num);
}
int min(int a, int b){
	return ((a < b)? a:b);
}
int extend_str_and_print(int num, string strExtend, int numExtended, int score, const string& str){
	assert(score >= 0);
	if(score == 0){
		cout << str << strExtend << endl;
		return 1;
	}

	int numPrinted = 0;
	numExtended++;
	for(unsigned int i = 0; i < sizeof(startChars)/sizeof(char) && numPrinted < num; i++){
		for(char c = startChars[i]; c <= endChars[i] && numPrinted < num; c++){
			numPrinted += extend_str_and_print(num - numPrinted, strExtend + c, numExtended,
			                                   score - numExtended, str);
		}
	}
	return numPrinted;
}

int find_with_score_and_print(int num, string mdfyStr, int reversePos,
                              int numChanged, int lengthRM, int score, const string& str){
	//cout << "rPos = " << reversePos << " original str = " << mdfyStr << endl;
	assert(score >= 0);
	if(reversePos == 0){
		if(score == 0){
			//cout << "rPos and score = 0    " << endl;
			cout << mdfyStr << endl;
			return 1;
		}
		if(lengthRM == 0 && mdfyStr.length() <= 100 && is_perfect_square(8*score + 1)){
			//cout << "score = " << score << " call extend\n" << endl;
			return extend_str_and_print(num, string(), 0, score, mdfyStr);
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
		cout << mdfyStr.substr(0, pos) << endl;
		numPrinted++;
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
			return numPrinted + find_with_score_and_print(num, mdfyStr, reversePos - 1,
								      numChanged, lengthRM, score, str);
		}
	}
	score -= reversePos;
	for(unsigned int i = 0; i < sizeof(startChars)/sizeof(char) && numPrinted < num; i++){
		for(char c = startChars[i]; c <= endChars[i] && numPrinted < num; c++){
			mdfyStr[pos] = c;
			//cout << "c = " << c << " pos: " << pos << " str become: " << (isChanged? mdfyStr:strBegin) << endl;
			//cout << "score remain: " << (isChanged? (score-reversePos):score) << endl;
			if(c != str[pos]){
				numPrinted += find_with_score_and_print(num - numPrinted, mdfyStr,
									reversePos - 1, numChanged+1,
									lengthRM, score, str);
			}else{
				numPrinted += find_with_score_and_print(num - numPrinted, strBegin,
									reversePosBegin - 1, numChanged,
									lengthRMBegin, scoreBegin, str);
			}
		}
	}
	return numPrinted;
}
			
void recommend_and_print_ID(const string& ID, int num){
        int score = 1;
        while(num > 0){
                num -= find_with_score_and_print(num, ID, min(score, ID.length()), 0, 0, score, ID);
                score++;
        }
}

int main(){
	int n;
	string str;

	cout<< "str: ";
	cin>> str;
	cout<< "score: ";
	while(cin >> n){
		find_with_score_and_print(2147483647, str, min(n, str.length()), 0, 0, n, str); 
		cout<< "score: ";
	}
	//cout<< "num: ";
	//cin>> n;

	//recommend_and_print_ID(str, n);

	return 0;
}

