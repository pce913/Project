#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#define N_MAX 100001
#define S_MAX 1 << 18
using namespace std;
int N, M, a[N_MAX], sz;
vector<int> bkt[1001];

void init() {
	sz = sqrt(N);
	for (int i = 0; i < N; i++)
		bkt[i / sz].push_back(a[i]);
	for (int i = 0; i < N / sz + 1; i++)
		sort(bkt[i].begin(), bkt[i].end());
}

void update(int pos, int val) {
	int idx = lower_bound(bkt[pos / sz].begin(), bkt[pos / sz].end(), a[pos]) - bkt[pos / sz].begin();
	bkt[pos / sz][idx] = val;
	sort(bkt[pos / sz].begin(), bkt[pos / sz].end());
	a[pos] = val;
}

int query(int lo, int hi, int k) {
	int ret = 0;
	while (lo % sz && lo <= hi)
	if (a[lo++] >= k)	ret++;
	while ((hi + 1) % sz && lo <= hi)
	if (a[hi--] >= k)	ret++;
	while (lo <= hi) {
		ret += bkt[lo / sz].end() - lower_bound(bkt[lo / sz].begin(), bkt[lo / sz].end(), k);
		lo += sz;
	}
	return ret;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	init();
	while (M--) {
		int x, k;
		scanf("%d", &x);
		if (x == 1) {
			scanf("%d", &k);
			printf("%d\n", query(1 - 1, N - 1, k));
		}
		else {
			int y, z;
			scanf("%d %d", &y, &z);
			update(y - 1, z);
		}
	}
	return 0;
}