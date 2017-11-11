//#include <iostream>
//#include <cstdio>
//
//using namespace std;
//
//char ans[1009][1009];
//bool tmp[1009][1009];
//
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) scanf(" %c", &ans[1][i]);
//	for (int i = 1; i <= n; i++) {
//		if (ans[1][i] == '#') {
//			tmp[1][i - 1] ^= 1;
//			tmp[1][i + 1] ^= 1;
//			tmp[2][i] ^= 1;
//		}
//	}
//	for (int i = 2; i <= n; i++) {
//		for (int j = 1; j <= n; j++) {
//			if (tmp[i - 1][j] == 1) {  //바로 윗쪽을 홀수번 뒤집었을 경우 (# 이건 . 이건 상관 없음) 아하 알겠다.
//				               //#이 있는 자리 또한 '.' 으로 뒤집어 지고 난후 시작하므로 #이 있는 자리 또한 '.' 과 같이 짝수번 뒤집어야 한다.
//
//				ans[i][j] = '#';
//				tmp[i - 1][j] ^= 1;
//				tmp[i][j - 1] ^= 1;
//				tmp[i + 1][j] ^= 1;
//				tmp[i][j + 1] ^= 1;
//			}
//			else ans[i][j] = '.';
//		}
//	}
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++) {
//			printf("%c", ans[i][j]);
//		}
//		puts("");
//	}
//	return 0;
//}
#include<stdio.h>

char input[1005];
int a[4][1005];
int temp2[1005];

/*1.두 줄을 정확히 아는 상태에서 첫째줄을 뒤집는다.
2.그러면 밑이 나온다.(2째줄)   밑에 대하여 둘째줄 뒤집기를 한다.
3.그 결과 나온 값이 셋째줄이다.*/
// 반복해준다.

int main(){
	int n;
	scanf("%d", &n);
	scanf("%s", &input[1]);
	if (n == 1){
		printf("%c",input[1]);
		return 0;
	}

	for (int i = 1; i <= n; i++){
		a[1][i] = (input[i] == '.');
		temp2[i] = a[1][i];
	}

	for (int i = 1; i <= n; i++){
		if (a[1][i] == 0){   //# 일때
			temp2[i - 1] = !temp2[i - 1];
			temp2[i] = !temp2[i];
			temp2[i + 1] = !temp2[i + 1];
		}
	}
	//n이 1 일 경우 예외
	for (int i = 1; i <= n; i++)
		printf("%c", a[1][i] == 0 ? '#' : '.');
	printf("\n");
	for (int i = 1; i <= n; i++){
		a[2][i] = temp2[i];
		printf("%c", a[2][i] == 0 ? '#' : '.');
	}
	printf("\n");
	/////////////////////////////////////   n-2번만 반복
	for (int k = 1; k <= n - 2; k++){
		for (int i = 1; i <= n; i++){
			if (a[1][i] == 0){  //#이면
				temp2[i] = !temp2[i];   	//temp2 에는 둘째줄 정보가 들어가 있음. //밑을 구함
			}
		}
		for (int i = 1; i <= n; i++){
			if (a[2][i] == 0){        //둘째줄 뒤집기 시전.
				temp2[i - 1] = !temp2[i - 1];
				temp2[i] = !temp2[i];
				temp2[i + 1] = !temp2[i + 1];
			}
		}
		for (int i = 1; i <= n; i++){
			a[3][i] = temp2[i];
			printf("%c", a[3][i] == 0 ? '#' : '.');
			a[1][i] = a[2][i];
			a[2][i] = a[3][i];
		}
		printf("\n");
	}
	return 0;
}