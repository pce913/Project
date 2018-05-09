#include<stdio.h>
#include<vector>
using namespace std;

template <typename T>
void reverse(T& v){
	int i = 0;
	int j = (int)v.size() - 1;
	while (i < j){
		swap(v[i++], v[j--]);
	}
}

int pow(int x,int y){
	int ans = 1;
	while (y != 0){
		if (y & 1){
			ans *= x;
		}
		x = x*x;
		y >>= 1;
	}
	return ans;
}

int main(){
	vector<int> a;
	int base_a, base_b;
	scanf("%d %d",&base_a,&base_b);
	int m;
	scanf("%d",&m);
	for (int i = 0; i < m; i++){
		int x;
		scanf("%d",&x);
		a.push_back(x);
	}

	reverse(a);
	int a_ten = 0;
	for (int i = 0; i < a.size(); i++){
		a_ten += a[i] * pow(base_a, i);
	}
	vector<int> ans;
	while (a_ten != 0){
		ans.push_back(a_ten%base_b);
		a_ten /= base_b;
	}
	reverse(ans);
	for (int i = 0; i < ans.size(); i++){
		printf("%d ",ans[i]);
	}
	return 0;
}