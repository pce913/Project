#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct Node{
	int valid;  //갯수를 세어야 하므로 int형으로 만들어줌.
	int child[4];
	int pi;
	Node(){
		valid = 0;
		for (int i = 0; i < 4; i++){
			child[i] = -1;
		}
		pi = -1;
	}
};

vector<Node> trie;
int to_node[129];
int root;

int make_node(){
	trie.push_back({});
	return trie.size() - 1;
}

void make_trie(string& s){
	int node = root;
	for (int i = 0; i < s.size(); i++){
		int c = to_node[s[i]];
		if (trie[node].child[c] == -1){
			int next = make_node();
			trie[node].child[c] = next;
		}
		node = trie[node].child[c];
	}
	trie[node].valid = 1;
}

void fill_pi(){
	queue<int> q;
	trie[root].pi = root;
	q.push(root);
	while (!q.empty()){
		int node = q.front();
		q.pop();
		for (int i = 0; i < 4; i++){
			int next = trie[node].child[i];
			if (next == -1)
				continue;
			if (node == root){
				trie[next].pi = root;
			}
			else{
				int x = trie[node].pi;
				while (x != root && trie[x].child[i] == -1){
					x = trie[x].pi;
				}
				if (trie[x].child[i] != -1){
					x = trie[x].child[i];
				}
				trie[next].pi = x;
			}
			int pi = trie[next].pi;
			trie[next].valid += trie[pi].valid;   //ok
			q.push(next);
		}
	}
}

int find_ans(string& s){
	int ans = 0;
	int node = root;
	for (int i = 0; i < s.size(); i++){
		int c = to_node[s[i]];
		while (node != root && trie[node].child[c] == -1){
			node = trie[node].pi;
		}
		if (trie[node].child[c] != -1){
			node = trie[node].child[c];
		}
		ans += trie[node].valid;
	}
	return ans;
}

void solve(){
	trie.clear();
	int n, m;
	string s, p;
	cin >> n >> m >> s >> p;
	root = make_node();
	for (int i = 0; i < p.size(); i++){
		for (int j = i; j < p.size(); j++){
			string tp = p;
			reverse(tp.begin() + i, tp.begin() + j + 1);
			make_trie(tp);
		}
	}
	fill_pi();
	cout << find_ans(s) << "\n";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	to_node['A'] = 0, to_node['T'] = 1;
	to_node['G'] = 2, to_node['C'] = 3;
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}