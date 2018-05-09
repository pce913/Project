#include<iostream>
using namespace std;

int a[10];
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n = 5;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n - i; j++){
			if (a[j] > a[j + 1]){
				swap(a[j], a[j + 1]);
				for (int k = 1; k <= n; k++){
					cout << a[k] << " ";
				}
				cout << "\n";
			}
		}
	}
	return 0;
}