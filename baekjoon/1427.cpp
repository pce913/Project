#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//int a[1000001];
//int b[1000001];
//
//void merge(int start, int end){
//	int mid = (start + end) / 2;
//	int i = start;
//	int j = mid + 1;
//	int k = 0;
//	while (i <= mid && j <= mid){
//		if (a[i] <= a[j]){
//			b[k++] = a[i++];
//		}
//		else{
//			b[k++] = a[j++];
//		}
//	}
//	while (i <= mid){
//		b[k++] = a[i++];
//	}
//	while (j <= end){
//		b[k++] = a[j++];
//	}
//
//	k = 0;
//	for (int i = start; i <= end; i++){
//		a[i] = b[k++];
//	}
//}
//
//void sorting(int start, int end){
//	if (start == end){
//		return;
//	}
//	int mid = (start + end) / 2;
//	sorting(start, mid);
//	sorting(mid + 1, end);
//	merge(start, end);
//}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	sort(s.begin(), s.end());
	reverse(s.begin(), s.end());
	cout << s;
		
	return 0;
}