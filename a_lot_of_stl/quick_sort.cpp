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
	sort(arr,right + 1, end);
}
