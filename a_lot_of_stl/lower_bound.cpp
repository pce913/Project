#include<stdio.h>
//12015번: 가장 긴 증가하는 부분 수열2 문제로 검수 완료.
template <typename T>
int lower_bound(T arr[],int start,int end,T value){   //arr가 vector일때는 T& 로 해주어야 한다.
	int left = start;
	int right = end;
	int ans = end + 1;   //lower_bound는 value값이 없을 경우 v.end() 를 가리키므로 이렇게 초기화 한다.
	while(left <= right){
		int mid = (left + right) >> 1;
		if (value <= arr[mid]){
			ans = mid;
			right = mid - 1;
		}
		else{
			left = mid + 1;
		}
	}
	return ans;
}

template <typename T>
void llower_bound(T arr[],int start,int end,int value){
	int left = start;
	int right = end;
	int ans = end + 1;
	while (left <= right){
		int mid = (left + right) >> 1;
		if (value <= arr[mid]){
			ans = mid;
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return ans;
}


//template <typename T>
//void llower_bound(T arr,int start,int end,int value){
//	int left = start;
//	int right = end;
//	int ans = end + 1;
//	while (left <= right){
//		int mid = (left + right) >> 1;
//		if (value <= arr[mid]){
//			ans = mid;
//			right = mid - 1;
//		}
//		else{
//			left = mid + 1;
//		}
//	}
//	return ans;
//}



int main(){
	int a[15] = { 0, 1, 4, 9, 16, 20, 20, 20, 20, 20, 20, 20 };
	printf("%d", lower_bound(a, 0, 11, 12));
	return 0;
}