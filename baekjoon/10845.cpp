#include<iostream>
//#include<queue>
#include<string>
using namespace std;
template <typename T>
struct queue{
	T* arr;
	int n;    //  들어있는 갯수
	int ffront, rear;    //왼쪽이 ffront, 오른쪽이 rear
	queue(){
		arr = new T[10000005];
		n = 0;
		rear = 0, ffront = 0;
	}
	void push(T t){
		arr[rear++] = t;
		n++;
	}
	T front(){
		return arr[ffront];
	}
	T back(){
		return arr[rear - 1];
	}
	int size(){
		return n;
	}
	void pop(){
		ffront++;
		n--;
	}
	bool empty(){
		return n == 0;
	}
};
queue<int> q;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		if (s == "push"){
			int x;
			cin >> x;
			q.push(x);
		}
		else if (s == "pop"){
			if (q.empty()){
				cout << -1 << "\n";
			}
			else{
				cout << q.front() << "\n";
				q.pop();
			}
		}
		else if (s == "size"){
			cout << q.size()<<"\n";
		}
		else if (s == "empty"){
			cout << (q.empty() ? 1 : 0) << "\n";
		}
		else if (s == "front"){
			cout << (q.empty() ? -1 : q.front()) << "\n";
		}
		else if (s == "back"){
			cout << (q.empty() ? -1 : q.back()) << "\n";
		}
	}
	return 0;
}