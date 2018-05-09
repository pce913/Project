#include<iostream>
#include<set>
using namespace std;

int a[15];
int n, k;
int cptr;
bool re[15];
int temp[15];
int tn;
set<int> st;
void fact(){
	if (tn == k){
		int wh = 0;
		for (int i = 0; i < tn; i++){
			if (temp[i] < 10)
				wh = 10 * wh + temp[i];
			else
				wh = 100 * wh + temp[i];
		}
		if (st.count(wh) == 0)
			st.insert(wh);
	}
	else{
		for (int i = 0; i < n; i++){
			if (!re[i]){
				re[i] = true;
				temp[tn++] = a[i];
				fact();
				re[i] = false;
				tn--;
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	fact();
	cout << st.size();
	return 0;
}