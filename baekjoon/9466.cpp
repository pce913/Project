//#include<stdio.h>
//#include<stack>
//using namespace std;
//int M[100001];
//bool check[100001];
//bool notcycle[100001];
//int main(){
//	int T, N;
//	scanf("%d", &T);
//	for (int t = 0; t < T; t++){
//		scanf("%d", &N);
//		for (int i = 1; i <= N; i++){
//			scanf("%d", &M[i]);
//			check[i] = false;
//			notcycle[i] = false;
//		}
//		int i = 1;
//		int temp = 2;
//		int count = 0;
//		int start = 1;
//		int Rnum=0;
//		
//		stack<int> S;
//		stack<int>* tS=new stack<int>;
//		while (count <= N){
//			if (check[i] == true){
//				int num = 0;
//				bool iscycle = false;
//				while (!S.empty()){
//					num++;
//					if (S.top() == i){
//						S.pop();
//						iscycle = true;
//						break;
//					}
//					tS->push(S.top());
//					S.pop();
//				}
//
//				if (S.empty()){
//					if (!iscycle)
//						num = 0;
//					
//					while (!tS->empty()){
//						notcycle[tS->top()] = true;
//						tS->pop();
//					}
//				}
//				else{
//					delete tS;
//					tS = new stack<int>;
//					while (!S.empty()){
//						notcycle[S.top()] = true;
//						S.pop();
//					}
//				}
//				Rnum += num;
//				
//
//				if (count >= N)
//					break;
//				for (int h = temp; h <= N; h++){
//					if (check[h] == false && notcycle[h]==false){
//						i = h;
//						temp = h + 1;
//						break;
//					}
//				}
//			}
//			else{
//				check[i] = true;
//				S.push(i);
//				i = M[i];
//				count++;
//			}
//		}
//		printf("%d\n",N-Rnum);
//	}
//	return 0;
//}

#include<stdio.h>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int indegree[100001];
int a[100001];





int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		int n;
		scanf("%d",&n);

		queue<int> q;
		memset(indegree, 0, sizeof(indegree));
		for (int i = 1; i <= n; i++){
			int x;
			scanf("%d",&x);
			a[i] = x;
			indegree[x]++;
		}
		for (int i = 1; i <= n; i++){
			if (indegree[i] == 0){
				q.push(i);
			}
		}
		
		while (!q.empty()){
			int node=q.front();
			q.pop();
			int next = a[node];
			indegree[next]--;
			if (indegree[next] == 0){
				q.push(next);
			}
		}

		int ans = 0;
		for (int i = 1; i <= n; i++){
			if (indegree[i]==0){
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}