#include<iostream>
using namespace std;

struct Point{
	int x, y;
	bool operator<(const Point& p)const{
		if (y != p.y)
			return y < p.y;
		return x < p.x;
	}
};

Point a[100005];

template <typename T>
void sort(T arr[],int start,int end){
	if (start >= end)
		return;
	int left = start - 1;
	int right = end + 1;
	T pivot = arr[(left + right) >> 1];
	while (true){
		while (arr[++left] < pivot);
		while (pivot < arr[--right]);
		if (left >= right)
			break;
		swap(arr[left], arr[right]);
	}
	sort(arr, start, left - 1);
	sort(arr, right + 1, end);
}

int main(){
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i].x >> a[i].y;
	}
	sort(a, 1, n);
	for (int i = 1; i <= n; i++){
		cout << a[i].x << " " << a[i].y << "\n";
	}
	return 0;
}