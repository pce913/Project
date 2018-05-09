#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
bool M[65][65];

string divide(int sx,int ex,int sy,int ey){
	if (ex - sx == 0 && ey - sy == 0)
		return M[sy][sx] == false ? "0" : "1";
	
	int hx=(sx + ex) / 2;
	int hy = (sy + ey) / 2;
	string a=divide(sx,hx,sy,hy);
	string b = divide(hx + 1, ex, sy, hy);
	string c = divide(sx, hx, hy + 1, ey);
	string d = divide(hx + 1, ex, hy + 1, ey);
	
	string ans;
	if (a == b && a == c && a == d){ 
		string z(a.size(), '0');
		string o(a.size(), '1');
		if (a!=z && a!=o)       //a가 0 또는 1로만 이루어져 있지가 않다면
			ans= "(" + a + b + c + d + ")";
		else
			ans= a;
	} 
	else
		ans= "(" + a + b + c + d + ")";
	return ans;
}
int main(){
	int N;
	scanf("%d",&N);
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++)
			scanf("%1d", &M[i][j]);
	}

	cout<<divide(1,N,1,N);
	return 0;
}