#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

int a[1005], b[1005], suma[1005], sumb[1005];
vector<int> aset, bset;
int n, m;
void make_set(){
	for (int len = 1; len < n; len++){
		for (int i = 1; i <= n; i++){
			int j = (len + i - 1) % n;
			if (j >= i){
				aset.push_back(suma[j] - suma[i - 1]);
			}
			else{
				aset.push_back(suma[n] - suma[i - 1] + suma[j]);
			}
		}
	}
	aset.push_back(suma[n]);

	for (int len = 1; len < m; len++){
		for (int i = 1; i <= m; i++){
			int j = (len + i - 1) % m;
			if (j >= i){
				bset.push_back(sumb[j] - sumb[i - 1]);
			}
			else{
				bset.push_back(sumb[m] - sumb[i - 1] + sumb[j]);
			}
		}
	}
	bset.push_back(sumb[m]);
	//피자 한판 전체는 딱 한번만 넣어준다.
}

int main(){
	int s;
	scanf("%d %d %d", &s, &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		suma[i] = suma[i - 1] + a[i];
	}
	for (int i = 1; i <= m; i++){
		scanf("%d",&b[i]);
		sumb[i] = sumb[i - 1] + b[i];
	}
	make_set();
	sort(aset.begin(), aset.end());
	sort(bset.begin(), bset.end());
	long long ans = 0;
	for (int i = 0; i < aset.size(); i++){   //A로만 이루어져 있을때
		if (aset[i] == s)
			ans++;
	}
	for (int i = 0; i < bset.size(); i++){  //B로만 이루어져 있을때
		if (bset[i] == s)
			ans++;
	}
	for (int i = 0; i < aset.size(); i++){  //A,B 섞여있을때
		auto p = equal_range(bset.begin(), bset.end(), s - aset[i]);
		ans += p.second - p.first;
	}
	printf("%lld",ans);
	return 0;
}