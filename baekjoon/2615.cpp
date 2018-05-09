#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<tuple>
#include<iomanip>
#include<algorithm>
#include<functional>
#include<cmath>
#include<unordered_set>
#include<unordered_map>
using namespace std;

struct Point{
	int x, y;
};
//여섯알 이상 연속으로 놓인경우는 이긴것이 아니다.

int dx[] = { 1, -1, 1, -1, 0, 0, -1, 1 };
int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

int n = 19;
int M[25][25];
Point candi[10];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			cin >> M[i][j];
		}
	}
	int ans_color = 0;
	int cn = 0;	bool isFind = false;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (M[i][j] == 0)continue;
			int cx = i, cy = j;
			for (int k = 0; k < 8; k++){
				int nx = cx, ny = cy;
				int dd = 0;
				int cn = 0;
				while (dd < 5){
					if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
						if (M[cx][cy] == M[nx][ny]){
							candi[cn++] = { nx, ny };
						}
					}
					nx += dx[k], ny += dy[k];
					dd++;
				}

				if (cn == 5){  //오목 완성
					isFind = true;    //육목처리가 아직도 안되고 있음
					if (nx >= 1 && nx <= n && ny >= 1 && ny <= n){
						if (M[cx][cy] == M[nx][ny]){
							isFind = false;  
						}
					}
					int rd = k ^ 1;
					if (cx + dx[rd] >= 1 && cx + dx[rd] <= n && cy + dy[rd] >= 1 && cy + dy[rd] <= n){
						if (M[cx][cy] == M[cx + dx[rd]][cy + dy[rd]]){
							isFind = false;   //육목일 경우 처리
						}
					}
					if (isFind){
						ans_color = M[cx][cy];
						break;
					}
				}
			}
			if (isFind)
				break;
		}
		if (isFind)
			break;
	}
	if (!isFind){
		cout << "0";
		return 0;
	}

	int ax = candi[0].x, ay = candi[0].y;
	for (int i = 1; i < 5; i++){
		if (ay>candi[i].y){
			ax = candi[i].x, ay = candi[i].y;
		}
	}
	cout << ans_color << "\n";
	cout << ax << " " << ay;
	return 0;
}