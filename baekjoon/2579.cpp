#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int in[300], M[300][2], s;
	cin >> s;
	for (int i = 0; i < s; i++)
		cin >> in[i];

	M[s - 1][0] = in[s - 1];
	M[s - 1][1] = in[s - 1];
	M[s - 2][0] = in[s - 2] + M[s - 1][0];
	M[s - 2][1] = 0;
	for (int i = s - 3; i >= 0; i--){
		M[i][0] = M[i + 1][1] + in[i];
		M[i][1] = max(M[i + 2][0], M[i + 2][1]) + in[i];
	}
	cout << max(max(M[0][0], M[0][1]), M[1][0]) << endl;
	return 0;
}