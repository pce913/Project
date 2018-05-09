#include<iostream>
using namespace std;
int n, m, x, y, i, j, l, k = -1;    //l:주기, k: 몇번째 위치인지.
//http://codersbrunch.blogspot.kr/2016/10/13253.html
//codersbrunch 풀이가 명확하고 좋다.
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> x >> y;
	do{
		if (i == x && j == y){
			k = l;
		}
		i = (i + 1) % n;
		j = (j + 1) % m;
		l++;
	} while (!(i == 0 && j == 0));
	cout << (double)(k == -1 ? -1 : k*(l - k));
	return 0;
}