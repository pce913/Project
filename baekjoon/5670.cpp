#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

/*입력으로 들어오는 모든 문자열을 trie에 저장한 후 현재 확인중인 문자에서 다음 
문자로 넘어가는 경로가 2 이상인 경우나 해당 지점에서 문자열이 끝나는 경우가 
버튼을 눌러야 하는 경우이니 카운트를 증가시켜주어 return하는 쿼리를 구현하여 해결 가능하다.*/

struct Node{
	bool valid;   //문자열의 끝인지 아닌지를 표시.
	int child[26];   //자식의 노드번호를 저장.
	int cnum;
	Node(){
		valid = false;
		cnum = 0;
		for (int i = 0; i < 26; i++){
			child[i] = -1;
		}
	}
};

int n;
int root;
vector<Node> trie;
string a[100005];
int make_node(){   //만든 노드 번호를 리턴
	trie.push_back({});
	return (int)trie.size() - 1;
}

void make_trie(string& s){
	int node = root;    //루트노드
	for (int i = 0; i < s.size(); i++){
		int c = s[i] - 'a';
		if (trie[node].child[c] == -1){
			int next = make_node();
			trie[node].child[c] = next;
			trie[node].cnum++;
		}
		node = trie[node].child[c];
	}
	trie[node].valid = true;
}

//자식의 갯수가 1개일때는

int get_cnt(string& s){
	int node = root;
	bool isOne = false;
	int cnt = 1; //시작은 1   //문자열이 끝나는 경우 버튼을 한번 꼭 눌러야 하는 경우.
	for (int i = 0; i < (int)s.size() - 1; i++){
		int c = s[i] - 'a';
		node = trie[node].child[c];
		if (trie[node].cnum > 1 || trie[node].valid){
			cnt++;
		}
	}
	return cnt;
}

void solve(){
	int sum = 0;
	for (int i = 0; i < n; i++){
		sum += get_cnt(a[i]);
	}
	cout <<fixed<<setprecision(2) <<(double)sum / n<<'\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (cin>>n){
		trie.clear();
		root = make_node();
		for (int i = 0; i < n; i++){
			cin >> a[i];
			make_trie(a[i]);
		}
		solve();
	}
	return 0;
}