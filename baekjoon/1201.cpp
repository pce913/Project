#include<stdio.h>
int main(){
	int N, M, K;
	scanf("%d %d %d",&N,&M,&K);
	// N >=M+K-1 : 적어도 M개의 정수는 증가 수열에 포함되어야 하고
//적어도 K개의 정수는 감소 수열에 포함되어야 한다.
//두 수열은 최대 정수 1개를 공유할 수 있기 때문에  N >=M+K-1  이어야 한다.
// N<=M*K :  만약 N이 MK+1일 경우 길이가 M+1인 증가 수열이나
// 길이가 k+1인 감소 수열을 반드시 만들 수 있다. (비둘기집 원리)
	

	//1. 1부터 N까지 수를 오름차순으로 적는다
	//2. 수를 M등분 한다. 이때, 그룹에 들어있는 수는 K보다 작거나 같아야 하며, 적어도 한 그룹은
	//   들어있는 수의 개수가 K이어야 한다.
    //3. 각 그룹에 들어있는 수의 순서를 뒤집는다
	//4. 끝
	if (N<M + K - 1 || N>M*K)
		printf("-1");
	else{
		int mass = (M>1) ? (N-K)/(M-1) : 0;     
		int rest = (M>1) ? (N - K) % (M - 1) : 0;
		int start = K;
		int end = 1;
		int split = 1;
		while (split <= M){ 
			for (int i = start; i >= end; i--)
				printf("%d ",i);
			end = start+1;
			start += mass + (rest>0 ? 1 : 0);
			if (rest > 0)
				rest--;
			split++;
		}
	}
	return 0;
}