#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct Node{
	bool valid;
	int child[26];
	Node(){
		valid = false;
		for (int i = 0; i < 26; i++){
			child[i] = -1;
		}
	}
};
int root;
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };
char M[10][10];
bool check[10][10];
vector<Node> trie;
vector<string> words;
int point[9];

int make_node(){
	trie.push_back({});
	return (int)trie.size() - 1;
}

void make_trie(int node,string& s,int idx){
	if (idx == s.size()){
		trie[node].valid = true;
		return;
	}

	int c = s[idx] - 'A';
	if (trie[node].child[c] == -1){
		int next = make_node();
		trie[node].child[c] = next;
	}
	make_trie(trie[node].child[c], s, idx + 1);
}

void dfs(int cx,int cy,string& s,int node){
	if (s.size() > 8)
		return;
	int c = M[cx][cy] - 'A';
	int next = trie[node].child[c];
	if (next == -1){
		return;
	}
	if (trie[next].valid){
		words.push_back(s);
	}

	check[cx][cy] = true;
	for (int i = 0; i < 8; i++){
		int nx = cx + dx[i];
		int ny = cy + dy[i];
		if (nx >= 1 && nx <= 4 && ny >= 1 && ny <= 4){
			if (!check[nx][ny]){
				s.push_back(M[nx][ny]);
				dfs(nx, ny, s, next);
				s.pop_back();
			}
		}
	}

	check[cx][cy] = false;
}

void solve(){
	words.clear();
	for (int i = 1; i <= 4; i++)
		cin >> &M[i][1];

	string s = "";
	for (int i = 1; i <= 4; i++){
		for (int j = 1; j <= 4; j++){
			s.push_back(M[i][j]);
			dfs(i, j, s, root);
			s.pop_back();
		}
	}

	sort(words.begin(), words.end());
	words.erase(unique(words.begin(), words.end()), words.end());
	int max_len = 0;
	int max_point = 0;
	string ans_s;
	int find_cnt = words.size();
	for (auto& it : words){
		max_point += point[it.size()];
		if (max_len < it.size()){
			max_len = it.size();
			ans_s = it;
		}
	}
	cout << max_point << " " << ans_s << " " << find_cnt<<"\n";
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int w;
	cin >> w;

	int root = make_node();
	for (int i = 0; i < w; i++){
		string s;
		cin >> s;
		make_trie(root, s, 0);
	}
	point[3] = 1, point[4] = 1, point[5] = 2;
	point[6] = 3, point[7] = 5, point[8] = 11;
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}