//백준 강의자료 그대로. 검수 완료.
template <typename T>
void swap(T& a,T& b){
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
bool next_permutation(T a[],int n){
	int i = n - 1;   //뒤에서부터 본다.
	while (i > 0 && a[i - 1] >= a[i]){
		i--;
	}
	if (i <= 0){
		return false;  //마지막 순열
	}
	int j = n - 1;
	while (a[j] <= a[i - 1]){
		j--;
	}
	swap(a[i - 1], a[j]);
	j = n - 1;
	while (i < j){        //a[i]부터 순열을 뒤집는다.
		swap(a[i], a[j]);
		i++;
		j--;
	}
	return true;
}