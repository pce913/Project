#include<stdio.h>
//2751번: 수 정렬하기2 문제로 검수 완료.
template <typename T>
void swap(T& x, T& y){
	T temp = x;
	x = y;
	y = temp;
}

template <typename T>
void sort(T arr[],int start,int end) { //vector를 정렬시키고 싶을땐 T를 T&로 바꿔줘야 한다.
	if (start >= end)
		return;
	int left = start - 1;
	int right = end + 1;
	T pivot = arr[(start + end) / 2];
	while (true) {
		while (arr[++left] < pivot);
		while (pivot < arr[--right]);    //operator < 를 사용하기 위해선 사실 pivot < arr[right] 이게 더 낫다.
		if (left >= right)
			break;
		swap(arr[left], arr[right]);
	}
	sort(arr,start, left - 1);
	sort(arr, right + 1, end);
}

template <typename T>
void ssort(T arr[],int start,int end){
	if (start >= end)return;
	int left = start - 1;
	int right = end + 1;
	T pivot = arr[(left + right) / 2];
	while (true){
		while (arr[++left] < pivot);
		while (pivot < arr[--right]);
		if (left >= right)break;
		swap(arr[left], arr[right]);
	}
	ssort(arr, start, left - 1);
	ssort(arr, right + 1, end);
}

//template<typename T>
//void ssort(T arr[],int start,int end){
//	if (start >= end)
//		return;
//	int left = start - 1;
//	int right = end + 1;
//	T pivot = arr[(left + right) / 2];
//	while (true){
//		while (arr[++left] < pivot);
//		while (pivot < arr[--right]);
//		if (left >= right)break;
//		swap(arr[left], arr[right]);
//	}
//	ssort(arr, start, left - 1);
//	ssort(arr, right + 1, end);
//}


int a[10] = { 1, 4, 2, 5, 7, 3, 6, 8 };
int main(){
	ssort(a,0, 7);
	for (int i = 0; i < 8; i++){
		printf("%d ",a[i]);
	}
	return 0;
}