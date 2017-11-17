//7469번: k번째 숫자 문제로 검수 완료.
template <typename T>
int upper_bound(T arr, int start, int end, int value){   //arr가 vector일때는 T& 로 해주어야 한다.
	int left = start;
	int right = end;
	int ans = 0;     //lower_bound와는 다르게 초기화를 0으로 해줘야 한다.
	while (left <= right){
		int mid = (left + right) >> 1;
		if (arr[mid] <= value){
			ans = mid + 1;   //upper_bound는 어떤값 보다 큰것들 중 바로 다음 위치를 가리키고 있으므로 mid+1; 
			left = mid + 1;
		}
		else{
			right = mid - 1;
		}
	}
	return ans;
}