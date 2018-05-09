#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
/*
	 두 번 이하로 swap하여 어떤 숫자를 제자리에 놓을 수 있다.
	 O(n^2)코드.
*/

int a[10005];
int n;
vector< pair<int,int> > v;

void move(int start,int end){
	int mid = (start + end) / 2;
	int i = start;
	int j = mid + 1;
	while (i <= mid && j <= end){
		swap(a[i++], a[j++]);
	}
}

int find_where(int idx){
	for (int i = idx + 1; i <= n; i++){
		if (a[i] == idx){
			return i;
		}
	}
	return 0;
}

void solve(){
	v.clear();
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
	}
	for (int idx = 1; idx <= n; idx++){
		if (a[idx] == idx)
			continue;
		int cur = find_where(idx);
		int len = cur - idx;
		if (cur + len - 1 > n){  //두 번의 swap을 하는 경우.
			if ((n - idx + 1) % 2 == 1){   //idx ~ n 까지의 길이가 홀수인경우 따로 처리해야함.
				v.push_back({ idx + 1, n });
				move(idx + 1, n);
			}
			else{
				v.push_back({ idx, n });
				move(idx, n);
			}
			cur = find_where(idx);
			len = cur - idx;
		}
		v.push_back({ idx, cur + len - 1 });
		move(idx, cur + len - 1);
	}
	printf("%d\n",v.size());
	for (int i = 0; i < v.size(); i++){
		printf("%d %d\n",v[i].first,v[i].second);
	}
}

int main(){
	int T;
	scanf("%d",&T);
	for (int test = 0; test < T; test++){
		solve();
	}
	return 0;
}

//#include<stdio.h>
//#include<algorithm>
//#include<vector>
//using namespace std;
//int a[10005],temp[10005];
//int n;
//int ans;
//vector< pair<int, int> > v;
//void merge(int start,int end){
//	int mid = (start + end) / 2;
//	int i = start;
//	int j = mid + 1;
//	int k = start;
//	while (i <= mid && j <= end){
//		if (a[i] < a[j]){
//			temp[k++] = a[i++];
//		}
//		else{
//			temp[k++] = a[j++];
//		}
//	}
//	while (i <= mid){
//		temp[k++] = a[i++];
//	}
//	while (j <= end){
//		temp[k++] = a[j++];
//	}
//	for (int x = start; x <= end; x++){
//		a[x] = temp[x];
//	}
//}
//
//void find_ans(int start,int end){   //이거 자체가 잘못됨.
//	int mid = (start + end) / 2;
//	int llen = mid - start + 1;
//	int rlen = end - mid;
//	if (llen == rlen){
//		ans++;
//		v.push_back({ start, end });
//	}
//	else{
//		int len = min(llen, rlen);
//		ans += len + 1;
//		if (llen < rlen){
//			v.push_back({ start, end - 1 });
//			int i = end - 1;
//			int j = end;
//			while (len--){
//				v.push_back({ i--, j-- });
//			}
//		}
//		else{
//			v.push_back({ start + 1, end });
//			int i = start;
//			int j = start + 1;
//			while (len--){
//				v.push_back({ i++, j++ });
//			}
//		}
//	}
//}
//
//void merge_sort(int start,int end){
//	if (start >= end)
//		return;
//	int mid = (start + end) / 2;
//	merge_sort(start, mid);
//	merge_sort(mid + 1, end);
//	if (a[start] <= a[mid + 1])
//		return;
//	merge(start, end);
//	find_ans(start, end);
//
//}
//
//void solve(){
//	ans = 0;
//	v.clear();
//	scanf("%d",&n);
//	for (int i = 1; i <= n; i++){
//		scanf("%d",&a[i]);
//	}
//	merge_sort(1, n);
//	printf("%d\n",ans);
//	for (int i = 0; i < v.size(); i++){
//		printf("%d %d\n",v[i].first,v[i].second);
//	}
//}
//
//int main(){
//	int T;
//	scanf("%d",&T);
//	for (int test = 0; test < T; test++){
//		solve();
//	}
//	return 0;
//}