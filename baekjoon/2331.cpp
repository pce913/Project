#include<stdio.h>
#include<vector>
using namespace std;

vector<int> list;

bool check[400000];

int pow(int t,int p){
	int ret = 1;
	while (p>0){
		if (p % 2 == 1){
			ret *= t;
		}
		t = t*t;
		p /= 2;
	}
	return ret;
}

int calc(int x,int p){
	int ret = 0;
	while (x > 0){
		int t = x % 10;
		x /= 10;
		ret+=pow(t, p);
	}
	return ret;
}

int main(){
	int a, p;
	scanf("%d %d",&a,&p);

	int x = a;
	check[x] = true;
	list.push_back(x);
	int snum = 0;
	while (true){
		x = calc(x, p);
		if (!check[x]){
			check[x] = true;
			list.push_back(x);
		}
		else{
			snum = x;
			break;
		}
	}

	int ans = 0;
	for (int i = 0; i < list.size(); i++){
		if (snum != list[i]){
			ans++;
		}
		else{
			break;
		}
	}
	printf("%d",ans);
	return 0;
}