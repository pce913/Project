#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int n;
int D[MAXN], r[MAXN], pi[MAXN], lcp[MAXN], sa[MAXN];
//D[i]: LCP[i+1]~ LCP[n] 중에서 연속으로 sa[i]가 나타내는 접미사의 길이보다 큰 LCP의 개수

void fill_pi(string& s){
	pi[0] = 0;
	int j = 0;
	for (int i = 1; i < n; i++){
		while (j>0 && s[i] != s[j]){
			j = pi[j - 1];
		}
		if (s[i] == s[j]){
			pi[i] = j + 1;
			j += 1;
		}
		else{
			pi[i] = 0;
		}
	}
}

int get_lcp(vector< vector<int> >& group, int k, int i, int j){
	int ans = 0;
	while (i < n&&j < n&&k >= 0){
		if (group[k][i] == group[k][j]){
			ans += (1 << k);
			i += (1 << k);
			j += (1 << k);
		}
		k--;
	}
	return ans;
}

void fill_D(){  //D[i]: LCP[i+1]~ LCP[n] 중에서 연속으로 sa[i]가 나타내는 접미사의 길이보다 큰 LCP의 개수
	for (int i = 0; i < n; i++){
		D[i] = 1;
	}
	for (int i = n - 1; i >= 0; i--){
		for (int j = i + 1; j < n; j++){
			if (lcp[j] >= n - sa[i]){   //n - sa[i]: 접미사 sa[i]의 길이
				D[i] += D[j];
				j += D[j] - 1;    //알겠다. 이코드가 있어야 펑펑 뛰면서 확인하므로 시간초과가 안난다.
			}
			else
				break;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin >> s;
	n = s.size();
	fill_pi(s);
	vector< vector<int> > group(22, vector<int>(n + 1));
	for (int i = 0; i < n; i++){
		sa[i] = i;
	}
	for (int i = 0; i < n; i++){
		group[0][i] = s[i] - 'A';
	}
	group[0][n] = -1;
	int k = 0;

	for (int len = 1; len / 2 < n; len *= 2){
		auto cmp = [&](const int& u, const int& v){
			return group[k][u] == group[k][v] ? group[k][u + len] < group[k][v + len] : group[k][u] < group[k][v];
		};
		sort(sa, sa + n, cmp);
		group[k + 1][sa[0]] = 0;
		group[k + 1][n] = -1;
		for (int i = 1; i < n; i++){
			group[k + 1][sa[i]] = group[k + 1][sa[i - 1]] + cmp(sa[i - 1], sa[i]);
		}
		k++;
	}
	for (int i = 1; i < n; i++){
		lcp[i] = get_lcp(group, k, sa[i - 1], sa[i]);
	}
	fill_D();
	for (int i = 0; i<n; i++){
		r[sa[i]] = i;
	}
	vector< pair<int, int> > ans;
	ans.push_back({ n, 1 });
	int x = pi[n - 1];    //x: 길이
	while (x > 0){
		int idx = r[n - x];   //지금보는 접미사(n - x)가 sa상에서 몇번째 인덱스인지를 가져온다. 아하.
		ans.push_back({ x, D[idx] });
		x = pi[x - 1];
	}
	cout << ans.size() << "\n";
	for (int i = ans.size() - 1; i >= 0; i--){
		cout << ans[i].first << " " << ans[i].second << "\n";
	}
	return 0;
}