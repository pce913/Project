//#include<stdio.h>
//#include<vector>
//using namespace std;
//
//void update(vector<int>& tree, int x, long long diff){
//	for (int i = x; i<tree.size(); i += i&-i){
//		tree[i] += diff;
//	}
//}
//
//long long sum(vector<int>& tree, int x){
//	long long ans = 0;
//	for (int i = x; i > 0; i -= i&-i){
//		ans += tree[i];
//	}
//	return ans;
//}
//
//long long sum(vector<int>& tree, int left, int right){
//	if (left > right)
//		return 0;
//	return sum(tree, right) - sum(tree, left - 1);
//}
//
//int main(){
//	int n;
//	scanf("%d", &n);
//	vector<int> a(n + 1);
//	vector<int> tree1(n + 1);             // tree1[i] : i가 등장한 갯수
//	vector<int> tree2(n + 1);             // tree2[i] : i 보다 앞쪽에 i보다 큰 수가 몇개 있는지를 저장.
//	for (int i = 1; i <= n; i++){
//		scanf("%d", &a[i]);
//	}
//	long long ans = 0;
//	for (int i = 1; i <= n; i++){                    // 7578번 공장 문제처럼 해결한다. A[i]<A[j], B[i]>B[j]
//		update(tree1, a[i], 1);                     //  대신 문제를 두번 풀어준다.
//		update(tree2, a[i], sum(tree1, a[i] + 1, n));
//		ans += sum(tree2, a[i] + 1, n);
//	}
//	printf("%lld", ans);
//	return 0;
//}
#include<stdio.h>
#include<vector>
using namespace std;                                        //http://wowoto.me/boj5012/ 참조

void update(vector<int>& tree, int x, long long diff){
	for (int i = x; i<tree.size(); i += i&-i){
		tree[i] += diff;
	}
}

long long sum(vector<int>& tree, int x){
	long long ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

long long sum(vector<int>& tree, int left, int right){
	if (left > right)
		return 0;
	return sum(tree, right) - sum(tree, left - 1);
}

int main(){
	int n;
	scanf("%d", &n);
	vector<int> a(n + 1);
	vector<int> tree1(n + 1);             // tree1[i] : i가 등장한 갯수
	vector<int> tree2(n + 1);             // tree2[i] : i가 등장한 갯수. for문을 돌면서 update
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		update(tree1, a[i], 1);
	}
	long long ans = 0;
	for (int i = 1; i <= n; i++){
		update(tree1, a[i], -1);
		ans += sum(tree2, a[i] + 1, n)*sum(tree1, 1, a[i] - 1);    // 왼쪽과 오른쪽으로 나눠서 푼다.
		update(tree2, a[i], 1);                                   // 현재 값보다 큰애들이 왼쪽에 몇개있는지*작은 애들이 오른쪽에 몇개있는지
	}
	printf("%lld", ans);
	return 0;
}

