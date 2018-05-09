#include<iostream>
#include<queue>
using namespace std;

struct Info{
	double rat;
	int cal;
	bool operator<(const Info& i)const{
		return rat < i.rat;
	}
};

priority_queue<Info> pq;
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	int n, a, b, dow;
	cin >> n >> a >> b >> dow;
	for (int i = 0; i < n; i++){
		int x;
		cin >> x;
		pq.push({ (double)x / b, x });
	}
	double ans = (double)dow / a;
	int son = dow, mother = a;
	while (!pq.empty()){
		auto p = pq.top();
		pq.pop();
		int cal = p.cal;
		if (ans < (double)(son + cal) / (mother + b)){
			ans = (double)(son + cal) / (mother + b);
			son += cal, mother += b;
		}
	}
	cout << (int)ans;
	return 0;
}