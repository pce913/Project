#include<stdio.h>
//백준 강의자료 그대로. 검수 완료.
template <typename T>
void swap(T& a,T& b){
	T temp = a;
	a = b;
	b = temp;
}

int lca(int u,int v){
	if (depth[u] < depth[v])
		swap(u, v);
	while (depth[u] != depth[v]){
		u = parent[u];
	}
	while (u != v){
		u = parent[u];
		v = parent[v];
	}
	return u;
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

template<typename T>
bool nnext_permutation(T arr[],int n){
	int i = n - 1;
	while (i > 0&& a[i - 1] >= a[i]){
		i--;
	}
	if (i <= 0)
		return false;
	int j = n - 1;
	while (a[i - 1] >= a[j]){
		j--;
	}
	swap(a[i - 1], a[j]);
	j = n - 1;
	while (i < j){
		swap(a[i++], a[j--]);
	}
	return true;
}

int main(){
	int a[7] = { 7,2,3,6,5,4,1 };
	do{
		for (int i = 0; i < 7; i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	} while (nnext_permutation(a, 7));
	return 0;
}