//#include<stdio.h>
//
//int n,ans=0;
//bool a[16][16];
//
//bool check(int row,int col){
//	for (int i = 0; i < n; i++){
//		if (i == row)
//			continue;
//		if (a[i][col])
//			return false;
//	}
//
//	int x = row - 1;
//	int y = col - 1;
//	while (x >= 0 && y >= 0) {
//		if (a[x][y]) 
//			return false;
//		x -= 1;
//		y -= 1;
//	}
//	x = row - 1;
//	y = col + 1;
//	while (x >= 0 && y < n) {
//		if (a[x][y]) 
//			return false;
//		x -= 1;
//		y += 1;
//	}
//	return true;
//}
//
//void calc(int row){
//	if (row == n){
//		ans++;
//		return;
//	}
//	for (int i = 0; i < n; i++){
//		if (check(row, i)){
//			a[row][i] = true;
//			calc(row + 1);
//		}
//		a[row][i] = false;
//	}
//}
//
//int main(){
//	scanf("%d",&n);
//	calc(0);
//	printf("%d",ans);
//	return 0;
//}
#include <stdio.h>

bool a[15][15];
int n;
bool check_col[15];
bool check_dig[40];
bool check_dig2[40];
bool check(int row, int col) {
	// |
	if (check_col[col]) {
		return false;
	}
	// 왼쪽 위 대각선
	if (check_dig[row + col]) {
		return false;
	}
	// /
	if (check_dig2[row - col + n]) {
		return false;
	}
	return true;
}
int calc(int row) {
	if (row == n) {
		return 1;
	}
	int cnt = 0;
	for (int col = 0; col<n; col++) {
		if (check(row, col)) {
			check_dig[row + col] = true;
			check_dig2[row - col + n] = true;
			check_col[col] = true;
			a[row][col] = true;
			cnt += calc(row + 1);
			check_dig[row + col] = false;
			check_dig2[row - col + n] = false;
			check_col[col] = false;
			a[row][col] = false;
		}
	}
	return cnt;
}
int main() {
	scanf("%d",&n);
	printf("%d",calc(0));
	return 0;
}