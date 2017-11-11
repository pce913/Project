#include<string>
#include<set>
#include<iostream>
using namespace std;

string in[1005];
string ver[1005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int r, c;
	cin >> r >> c;
	for (int i = 0; i < r; i++){
		cin >> in[i];
	}
	for (int i = 0; i < c; i++){
		for (int j = 0; j < r; j++){
			ver[i] += in[j][i];
		}
	}
	int count = 0;
	
	for (int i = 0; i < r; i++){
		set<string> st;
		for (int j = 0; j < c; j++){
			ver[j][i] = '!';
			st.insert(ver[j]);
		}
		if (st.size() >= c){
			count++;
		}
		else{
			break;
		}
	}
	cout << count;
	return 0;
}