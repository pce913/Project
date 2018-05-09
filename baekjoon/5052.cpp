#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Node{
	bool valid;
	int child[10];
	Node(){
		valid = false;
		for (int i = 0; i < 10; i++){
			child[i] = -1;
		}
	}
};

vector<Node> trie;

int make_node(){
	trie.push_back({});
	return (int)trie.size() - 1;
}

void make_trie(int node, string& s, int idx){
	if (idx == s.size()){
		trie[node].valid = true;
		return;
	}

	int c = s[idx] - '0';
	if (trie[node].child[c] == -1){
		int next = make_node();
		trie[node].child[c] = next;
	}
	make_trie(trie[node].child[c], s, idx + 1);
}

bool isYes(int node){
	for (int i = 0; i < 10; i++){   //리프노드를 제외한 중간 노드에서 valid 한 값이 나오면 NO 이다. 리프노드는 child가 하나도 없으므로 이 if문에 안걸린다.
		if (trie[node].child[i] != -1){
			if (trie[node].valid){
				return false;
			}
			else{
				if (!isYes(trie[node].child[i])){
					return false;
				}
			}
		}
	}
	return true;
}

void solve(){
	trie.clear();
	int n;
	cin >> n;

	int root = make_node();
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		make_trie(root, s, 0);
	}
	if (isYes(root)){
		cout << "YES" << "\n";
	}
	else{
		cout << "NO" << "\n";
	}

}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	for (int test = 1; test <= T; test++){
		solve();
	}
	return 0;
}