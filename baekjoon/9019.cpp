#include<stdio.h>
#include<queue>
#include<string>
#include<iostream>
using namespace std;

void bfs(int fnum,int tnum,bool* check,int* from,char how[]){
	queue<int> q;
	q.push(fnum);
	check[fnum] = true;
	from[fnum] = -1;
	how[fnum] = 'X';

	while (!q.empty()){
		if (check[tnum] == true)
			break;

		int now = q.front();
		q.pop();
		pair<char, int> DSLR[4] = {make_pair('D',(now*2)%10000),
		make_pair('S',(now==0 ? 9999 : now-1)),
		make_pair('L',(now%1000)*10 + now/1000),make_pair('R',(now/10)+ (now%10)*1000)};
		for (int i = 0; i < 4; i++){
			int next = DSLR[i].second;
			if (check[next] == false){
				q.push(next);
				check[next] = true;
				from[next] = now;
				how[next] = DSLR[i].first;
			}
		}
	}
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int fnum, tnum;
		bool check[10001];
		int from[10001];
		char how[10001];
		for (int i = 0; i < 10001; i++){
			check[i] = false;
			from[i] = 0;
			how[i] = 'Y';
		}
		scanf("%d %d",&fnum,&tnum);
		bfs(fnum, tnum,check,from,how);

		int temp = tnum;
		string ans = "";
		while (from[temp] != -1){
			ans = how[temp] + ans;
			temp = from[temp];
		}
		cout << ans << "\n";
	}
	return 0;
}