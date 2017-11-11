#include<iostream>
#include<string>
#include<map>
using namespace std;

map<string, char> m = { { "000", '0' }, { "001", '1' }, { "010", '2' }, { "011", '3' }, { "100", '4' }, { "101", '5' }, { "110", '6' }, {"111",'7'} };
map<string, char> m_one = { { "1", '1' }, { "10", '2' }, { "11", '3' }, { "100", '4' }, { "101", '5' }, { "110", '6' }, { "111", '7' } };
string bin;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> bin;
	int bsize = bin.size();
	int locate = bsize - 3 * (bsize / 3);

	string s = "";
	int one = 0;
	for (int i = 0; i < locate; i++){
		s += bin[i];
	}
	if (locate != 0){
		cout << m_one[s];
	}
	
	s = "";
	int k = 0;
	for (int i = locate; i < bsize; i++){
		s += bin[i];
		k++;
		if(k%3==0){
			cout << m[s];
			s = "";
			k = 0;
		}
	}
	return 0;
}