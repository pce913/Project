#include<stdio.h>
int N, M;
int point_people;
int a[10001];

long long many_people(long long t){
	long long sum = M;
	point_people = 0;
	for (int i = 1;i<=M;i++){
		sum += t / a[i];
		if (t%a[i] == 0)
			point_people++;
	}
	return sum;
}


int main(){	
	scanf("%d %d",&N,&M);
	for (int i = 1; i <= M; i++)
		scanf("%d",&a[i]);

	if (N <= M){
		printf("%d", N);
		return 0;
	}

	long long l = 1;
	long long r = 2000000000LL* M * 30;
	long long m = 0, e = 0, s = 0;
	while (l <= r){
		m = (l + r) / 2;
		e=many_people(m);
		s = e - point_people + 1;
		if (N > e)
			l = m + 1;
		else if (N < s)
			r = m - 1;
		else
			break;
	}
	int x = 1;
	for (x = 1; x <= M; x++){
		if (m%a[x] == 0){
			if (N == s)
				break;
			s++;
		}
	}
	printf("%d",x);
	return 0;
}