#include<iostream>
#include<string>
#include<queue>
#include<vector>
using namespace std;

//trie: 여러 패턴이 주어 지고, 여러개의 쿼리가 들어오는데
//쿼리로 주는 패턴이 기존의 패턴들 중에 있니? 를 물을때 사용함.
//aho-corasick: 여러 패턴이 주어지고, 하나의 긴 문자열이 들어오는데
//그 문자열 안에 패턴들이 몇번 등장하니? 를 물을때 사용함.

//aho-corasick에서 '어떤 패턴을 각각 몇개씩 찾았니?'를 물을때는
//Node 정보에 indexes라는 배열도 필요함.  백준 강의자료 참조.

struct Node{   //이 문제의 질문은 몇개씩 찾았니가 아니라 존재 여부만 물으므로 indexes필요 없다.
	bool valid;
	int child[26];
	int pi;
	Node(){
		for (int i = 0; i < 26; i++){
			child[i] = -1;
		}
		valid = false;
		pi = -1;
	}
};
vector<Node> trie;

int make_node(){
	trie.push_back({});
	return (int)trie.size() - 1;
}

void make_trie(int root, string& s){   //트라이 만들기 비재귀 구현.
	int node = root;
	for (int i = 0; i < s.size(); i++){
		int c = s[i] - 'a';
		if (trie[node].child[c] == -1){
			int next = make_node();
			trie[node].child[c] = next;
		}
		node = trie[node].child[c];
	}
	trie[node].valid = true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int root = make_node();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		make_trie(root, s);
	}
	queue<int> q;
	trie[root].pi = root;  //시작지점의 pi는 루트가 될 수 밖에 없다.
	q.push(root);
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		for (int i = 0; i < 26; i++){  //현재위치 cur에서 다음위치 next의 pi를 갱신해준다.
			int next = trie[cur].child[i];
			if (next == -1)
				continue;
			if (cur == root){
				trie[next].pi = root;
			}
			else{
				int x = trie[cur].pi;
				while (x != root && trie[x].child[i] == -1){
					x = trie[x].pi;
				}
				if (trie[x].child[i] != -1){
					x = trie[x].child[i];
				}
				trie[next].pi = x;
			}
			int pi = trie[next].pi;
			trie[next].valid |= trie[pi].valid;   //이거 안넣으면 100%에서 틀린다!!!!!!!!!!! 아하.
			q.push(next);
		}
	}
	int m;
	cin >> m;
	for (int qq = 0; qq < m; qq++){
		string s;
		cin >> s;
		int node = root;
		bool isYes = false;
		for (int i = 0; i < s.size(); i++){
			int c = s[i] - 'a';
			while (node != root&& trie[node].child[c] == -1){
				node = trie[node].pi;
			}
			if (trie[node].child[c] != -1){
				node = trie[node].child[c];
			}
			if (trie[node].valid){
				isYes = true;
				break;
			}
		}
		cout << (isYes ? "YES" : "NO") << "\n";
	}
	return 0;
}