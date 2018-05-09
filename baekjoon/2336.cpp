#include<stdio.h>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

const int INF = 500001;

struct Exam{
	int first, second, third;
};

bool cmp(const Exam& a,const Exam& b){
	return a.second < b.second;
}

void init(vector<int>& tree, int node, int start, int end){
	tree[node] = INF;
	if (start != end){
		init(tree,2*node,start,(start+end)/2);
		init(tree, 2 * node + 1, (start + end) / 2+1,end );
	}
}

int query(vector<int>& tree,int node,int start,int end,int left,int right){           //구간의 최소값을 구함.
	if (left > end || right < start){
		return -1;
	}
	if (left <= start && right >= end){
		return tree[node];
	}
	int m1 = query(tree,2*node,start,(start+end)/2,left,right);
	int m2 = query(tree, 2 * node + 1, (start + end) / 2+1,end , left, right);
	if (m1 == -1){
		return m2;
	}
	else if (m2 == -1){
		return m1;
	}
	else{
		return min(m1,m2);
	}
}

void update(vector<int>& tree,int node,int start,int end,int i,int value){
	if (i > end || i < start)
		return;
	tree[node] = min(tree[node],value);
	if (start != end){
		update(tree,2*node,start,(start+end)/2,i,value);
		update(tree, 2 * node + 1, (start + end) / 2+1,end , i, value);
	}
}

int main(){
	int n;
	scanf("%d",&n);
	vector<Exam> a(n+1);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<int> tree(tree_size);                  // tree[i] : 첫번째 시험 등수가 i일때 세번째 시험 등수.
	for (int i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);
		a[t].first = i;
	}
	for (int i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);
		a[t].second = i;
	}
	for (int i = 1; i <= n; i++) {
		int t;
		scanf("%d", &t);
		a[t].third = i;
	}
	
	sort(a.begin(), a.end(),cmp);
	int ans = 0;
	init(tree,1,1,n);         //나보다 두번째 시험을 잘본 녀석들이 존재하는데,
	                           // 그 중에 첫번째 시험도 나보다 잘 본 녀석들이 있고,
	                           // 마지막으로 세번째 시험은 나보다 못봤다면 ans++
	for (int i = 1; i <= n; i++){
		int temp = query(tree, 1, 1, n,1,a[i].first);   //나보다 첫번째 시험 등수가 같거나 낮은 녀석들의 세번째 시험 등수 중에서 최소값.
		                                                // 즉, 가장 높은 등수를 가져옴.
		if (temp > a[i].third){                  // 현재 학생의 세번째 시험 등수가 앞의 학생들보다 좋다면 얘는 굉장한 학생이다,
			ans++;
		}
		update(tree,1,1,n,a[i].first,a[i].third);
	}
	printf("%d",ans);
	return 0;
}