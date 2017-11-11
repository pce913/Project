#include<iostream>
using namespace std;

int a[2000];
int b[2000];
int ans = 0;
void merge(int start, int end){
	int mid = (start + end) / 2;
	int i = start;
	int j = mid + 1;
	bool isReverse = false;
	while (i <= mid && j <= end){
		if (a[i] != a[j]){
			if (a[i++] > a[j++]){
				isReverse = true;
			}
			break;
		}
	}

	if (isReverse){
		i = start;
		j = mid + 1;
		int k = 0;
		while (j <= end){
			b[k++] = a[j++];
		}

		i = start;
		j = mid + 1;
		while (i <= mid && j <= end){
			a[j++] = a[i++];
		}

		i = start;
		k = 0;
		while (i <= mid){
			a[i++] = b[k++];
		}
		int range = (end - start + 1);
		ans += range*range / 2;
	}
}

void sort(int start, int end){
	if (start == end){
		return;
	}
	int mid = (start + end) / 2;
	sort(start, mid);
	sort(mid + 1, end);
	merge(start, end);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	n = (1 << n);
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(0, n-1);
	cout << ans << "\n";
	for (int i = 0; i < n; i++){
		cout << a[i] << "\n";
	}
	return 0;
}
//#include<iostream>
//#include<string>
//using namespace std;
//
//string s = "";
//int ans = 0;
//void merge(int start, int end){
//	int mid = (start + end) / 2;
//	int range = (end - start + 1) / 2;
//	string left = s.substr(start, range);
//	string right = s.substr(mid + 1, range);
//	if (left > right){
//		string result = right + left;
//		int k = 0;
//		//for (int i = start; i <= end; i++){  //한글자씩 넣으면 안된다.
//		//	s[i] = result[k++];
//		//}
//		int i = start;
//		while (k < result.size()){
//			s[i++] = result[k++];
//		}
//		int rs = result.size();
//		ans += rs*(rs / 2);
//		/*if (ans == 28){
//			int zz = 0;
//		}
//		cout << "ans : " << ans << "\n";*/
//	}
//}
//
//void sort(int start, int end){
//	if (start == end){
//		return;
//	}
//	int mid = (start + end) / 2;
//	sort(start, mid);
//	sort(mid + 1, end);
//	merge(start, end);
//}
//
//int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	int n;
//	cin >> n;
//
//	int re = (1 << n);
//	for (int i = 0; i < re; i++){
//		string c;
//		cin >> c;
//		s += c;
//	}
//	sort(0, s.size()-1);
//	cout << ans << "\n";
//	for (int i = 0; i < s.size(); i++){
//		cout << s[i]<<"\n";
//	}
//	return 0;
//}