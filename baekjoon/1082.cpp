#include<stdio.h>
#include<cstring>
int a[10];

int main(){
	freopen("input.txt", "r", stdin);
	int N;
	int out[51];
	while (scanf("%d", &N) == 1){
		int t,m;
		for (int i = 0; i < N; i++){
			scanf("%d",&t);
			a[i] =t;
		}
		scanf("%d",&m);
		                 
		int v = m / a[0];
		m -= v*a[0];
		memset(out,0,v*sizeof(int));

		int j = 0;
		int start = j;
		bool check = false;
		while (j<v){
			bool isZero = true;
			m += a[0];
			for (int i = N - 1; i > 0; i--){
				if (m >= a[i]){
					out[j] = i;
					j++;
					m -= a[i];
					isZero = false;
					check = true;
					break;
				}
			}
			if (isZero == true && check == true)
				break;
			else if (isZero == true && check == false){
				j++;
				start = j;
			}
		}
		if (check==false)
			printf("0");
		for (int i = start;i<v; i++)
			printf("%d", out[i]);
		printf("\n");
	}
	return 0;
}
//#include<stdio.h>
//int n, c[10], p;
//char r[51];
//int main() {
//	while (scanf("%d", &n) != -1) {
//		int m = 50, idx, s = 0, rcnt = 0;
//		for (int i = 0; i < n; i++) {
//			scanf("%d", c + i);
//			if (m >= c[i]) m = c[i], idx = i;
//		}
//		scanf("%d", &p);
//		for (; p >= m;) r[rcnt++] = idx + '0', p -= m;
//		for (int i = 0; i < rcnt; i++) {
//			for (int j = n - 1; j >= 0; j--)
//			if (c[j] <= p + m) { r[i] = j + '0'; p += m - c[j]; break; }
//			if (r[s] == '0') s++, p += m;
//		}
//		puts(s == rcnt ? "0" : r + s);
//	}
//	return 0;
//}
