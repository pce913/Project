#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

vector<string> a;
vector< pair<string, int> > line;

int tree[100005];
int n;

void update(int x,int value){
	for (int i = x; i <= n ; i += i&-i){
		tree[i] += value;
	}
}

int query(int x){
	int ans = 0;
	for (int i = x; i > 0; i -= i&-i){
		ans += tree[i];
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		a.push_back(s);
	}
	sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); i++){
		line.push_back({ a[i], i + 1 });    // A를 사전순으로 정렬했을때의 순서를 함께 저장
	}
	for (int i = 0; i < line.size(); i++){
		string &ts = line[i].first;
		reverse(ts.begin(), ts.end());    //각 문자열을 뒤집어서 다시 저장
	}
	sort(line.begin(), line.end());     //뒤집은 문자열로 다시 정렬
	reverse(line.begin(), line.end());   //순서를 뒤집는다. 왜냐하면  조건중에 
	                             //B'가 A'보다 사전 순으로 앞서면  이라는 것을 만족시키기 위해
	                          //A'이 사전순으로 뒤쪽인것을 보면서 A가 B보다 사전순으로 앞서는 녀석을
	                          //보기 위함이다.
	long long ans = 0;
	for (int i = 0; i < line.size(); i++){
		int x = line[i].second;
		ans+=query(x);
		update(x, 1);
	}
	cout << ans;
	return 0;
}