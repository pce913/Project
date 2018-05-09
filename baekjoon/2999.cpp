#include<string>
#include<iostream>
#include<vector>
using namespace std;

char M[105][105];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	int len = s.size();

	int r = 1;
	int c = len;
	vector<int> aa;
	for (int i = 2; i*i <= len; i++){
		if (len%i == 0){
			r = i;
			c = len / i;
		}
	}
	//printf("%d %d",r,c);
	int k = 0;
	for (int j = 1; j <= c; j++){
		for (int i = 1; i <= r; i++){
			M[i][j] = s[k++];
		}
	}
	for (int i = 1; i <= r; i++){
		printf("%s", M[i] + 1);
	}
	return 0;
}