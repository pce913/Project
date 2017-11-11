#include<stdio.h>
#include<iostream>
using namespace std;
int R, C;
char board[20][20];
bool check[26];
int ans = 1;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
void go(int x,int y,int cnt){
	if (cnt > ans)
		ans = cnt;
	for (int k = 0; k < 4; k++){
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx >= 0 && ny >= 0 && nx < R && ny < C){
			int a = board[nx][ny] - 'A';
			if (check[a] == false){
				check[a] = true;
				go(nx, ny,cnt+1);
				check[a] = false;
			}
			
		}
	}
}

int main(){
	scanf("%d %d\n",&R,&C);
	for (int i = 0; i < R; i++)
		scanf("%s", &board[i][0]);
	check[board[0][0] - 'A'] = true;
	go(0, 0,1);
	printf("%d",ans);
	return 0;
}