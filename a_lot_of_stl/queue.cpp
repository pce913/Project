#include<stdio.h>
//10845번: 큐 문제로 검수 완료
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
	~queue(){
		delete[] arr;
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

template<typename T>
struct qqueue{
	T* arr;
	int n, rear, ffront;
	qqueue(){
		arr = new T[10000005];
		n = 0, rear = 0, ffront = 0;
	}
	~qqueue(){
		delete[] arr;
	}
	void push(T x){
		arr[rear++] = x;
		n++;
	}
	T front(){
		return arr[ffront];
	}
	void pop(){
		ffront++;
		n--;
	}
	bool empty(){
		return n == 0;
	}
};


int main(){
	qqueue<int> q;
	q.push(0), q.push(1), q.push(2), q.push(3);
	while (!q.empty()){
		printf("%d ",q.front());
		q.pop();
	}
	q.push(5);
	q.push(6), q.push(7);
	while (!q.empty()){
		printf("%d ", q.front());
		q.pop();
	}
	return 0;
}