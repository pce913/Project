#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

void update(vector<int>& tree,int x,int diff){
	for (int i = x; i<tree.size(); i += i&-i){
		tree[i] += diff;
	}
}

long long sum(vector<int>& tree,int x){
	long long ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

long long sum(vector<int>& tree,int left,int right){
	if (left > right)
		return 0;
	return sum(tree, right) - sum(tree, left - 1);
}

int main(){
	int n;
	scanf("%d",&n);
	vector< pair<int,int> > a(n + 1);
	vector<int> tree(n + 1);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i].first);
		a[i].second = i;
		update(tree, i, 1);
	}
	sort(a.begin() + 1, a.end());               // 작업이 언제 완료되는지를 정렬함.

	long long total = 0;         //그 작업의 오른쪽에 있으면서 아직 완료되지 않은 작업의 갯수와 소요시간을 구할때 쓰임.
	int last = 0;    //마지막으로 몇까지 실행 시켰는지를 저장.
	vector<long long> ans(n + 1);
	long long remain = n;            //남은 작업의 갯수
	for (int i = 1; i <= n; i++){
		total += (a[i].first - last)*remain;            // 아하. 세그먼트 트리 활용 필기 참조.
		remain -= 1;
		ans[a[i].second] = total - sum(tree,a[i].second+1,n);
		update(tree,a[i].second,-1);
		last = a[i].first;
	}
	for (int i = 1; i <= n; i++) {
		printf("%lld\n", ans[i]);
	}
	return 0;
}