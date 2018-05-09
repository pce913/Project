//n만에 풀지 않으면 시간초과 난다.
#include <stdio.h>

int N, M, K;
int main(){
	scanf("%d %d %d", &N, &M, &K);  //N: 사람수, M:부르는 숫자 갯수 ,K: 동호의 '상대적 위치'
	int d;
	for (d = 1; d < N; d++){        //이 안에 답이 나옴
		int rest = (N - d + 1);   //(N - d + 1): 현재 남아있는 사람이 몇명인가
		int nM = M % rest == 0 ? rest : M % rest;    //퇴장하는 사람의 상대적 위치 

		if (K == nM)
			break;
		else  //동호의 '상대적 위치'를 변경해준다.
			K = K > nM ? K - nM : K - nM + (N - d) + 1;   //아하
	}
	printf("%d", d);
	return 0;
}

//#include<stdio.h>
//
//int tree[4 * 5000005];
//
//void init(int node, int start,int end){
//	if (start == end){
//		tree[node] = 1;
//	}
//	else{
//		init(2 * node, start, (start + end) / 2);
//		init(2 * node + 1, (start + end) / 2+1,end );
//		tree[node] = tree[2 * node] + tree[2 * node + 1];
//	}
//}
//
//void update(int node,int start,int end,int i,int value){
//	if (i > end || i < start)
//		return;
//	if (start == end){
//		tree[node] += value;
//	}
//	else{
//		update(2 * node, start, (start + end) / 2, i, value);
//		update(2 * node + 1, (start + end) / 2+1,end , i, value);
//		tree[node] = tree[2 * node] + tree[2 * node + 1];
//	}
//
//}
//
//int sum(int node, int start, int end, int i, int j){
//	if (i > end || j < start){
//		return 0;
//	}
//	if (start >= i && end <= j){
//		return tree[node];
//	}
//	int s1=sum(2 * node, start, (start + end) / 2, i, j);
//	int s2=sum(2 * node + 1, (start + end) / 2 + 1,end , i, j);
//	return s1 + s2;
//}
//
//int query(int node, int start, int end, int x){   //x: 현재 남은 애들중에 몇번째 인덱스니?
//	if (start == end)                       //x에 해당하는 인덱스가 실제로 몇번째 인덱스니? 를 나타내는 query
//		return start;
//	if (x <= tree[2 * node]){
//		return query(2 * node, start, (start + end) / 2, x);
//	}
//	else{
//		return query(2 * node + 1, (start + end) / 2 + 1, end, x - tree[2 * node]);
//	}
//}
//
//int main(){
//	int n, m, k;
//	scanf("%d %d %d",&n,&m,&k);
//	init(1,1,n);
//
//	int out = 1;   //마지막으로 폭발한 녀석이 누구이니? 초기화는 1부터 하면 편하다.
//	int ans = 0;
//	for (int i = n; i >= 1; i--){
//		ans++;
//		int pre = sum(1,1,n,1,out-1);    //앞에 몇개가 남아있니?
//		int next = (pre + m - 1) % i + 1;   //앞에 몇개가 남아있는데 그 중에 몇 번째니? 를 나타내는 변수. 1 베이스 일때는 이렇게 해준다.
//		out = query(1, 1, n, next);
//		update(1, 1, n, out, -1);
//		if (out == k)
//			break;
//	}
//	printf("%d",ans);
//	return 0;
//}