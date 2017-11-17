//1753번: 최단 경로 문제로 검수 완료.
template <typename T>
void swap(T& a,T& b){
	T temp = a;
	a = b;
	b = temp;
}

template <typename T>
struct priority_queue{
	T* heap;    //혹시나 배열 크기가 너무 크다고 판단될 경우에는 이 부분을 vector로 바꾸자. 배열을 미리 잡아놓으면 stack 메모리가 초과 되므로 동적 할당 하자.
	int n = 0;
	priority_queue(){
		heap = new T[10000005];
		n = 0;
	}
	~priority_queue(){
		delete[] heap;
	}
	void push(T value){
		heap[n++] = value;
		int node = n - 1;
		//루트에 도달하거나 value이상의 원소를 가진 조상을 만날 때까지 반복
		while (node > 0 && heap[(node - 1) / 2] < heap[node]){
			swap(heap[(node - 1) / 2], heap[node]);
			node = (node - 1) / 2;
		}
	}
	void pop(){
		heap[0] = heap[n - 1];
		n--;
		int node = 0;
		while (true){
			int left = 2 * node + 1;
			int right = 2 * node + 2;
			if (left >= n)  //리프 노드에 도달 했을때
				break;
			int next = node;
			if (heap[next] < heap[left]){  //보통 operator< 를 사용하므로 비교 연산을 사용할땐 '<' 로 해주는게 좋다. 
				next = left;
			}
			if (right < n && heap[next] < heap[right]){
				next = right;
			}
			if (next == node)  //두 자손이 모두 자기 자신 이하의 원소를 가지고 있을때
				break;
			swap(heap[node], heap[next]);
			node = next;
		}
	}
	T top(){
		return heap[0];
	}
	bool empty(){
		return n == 0;
	}
};