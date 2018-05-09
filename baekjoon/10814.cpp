#include<stdio.h>

struct Info{
	int age, ord;
	char name[105];
	bool operator<(const Info& i)const{
		if (age != i.age){
			return age < i.age;
		}
		return ord < i.ord;
	}
};

template <typename T>
void swap(T& a,T& b){
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
void sort(T arr[], int start, int end){
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

Info info[100005];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 1; i <= n; i++){
		scanf("%d %s", &info[i].age, info[i].name);
		info[i].ord = i;
	}
	sort(info, 1, n);
	for (int i = 1; i <= n; i++){
		printf("%d %s\n", info[i].age, info[i].name);
	}
	return 0;
}