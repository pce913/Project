#include<iostream>
#include<algorithm>
using namespace std;

int a[10005];
int lefts[10005], rights[10005]; //i¹ø ±×·ìÀÇ ¸Ç ¿ÞÂÊ ÀÎµ¦½º,¿À¸¥ÂÊ ÀÎµ¦½º
int sz[10005];
int grp[10005];
int GN;
int n;
int go(int ll, int rr){
	int lidx = ll;
	int ridx = rr;
	int ret = 0;
	while (lidx >= 1 && ridx <= n && a[lidx] == a[ridx]){
		if (sz[grp[lidx]] + sz[grp[ridx]] >= 4){
			ret += sz[grp[lidx]] + sz[grp[ridx]];
			lidx = lefts[grp[lidx]] - 1;
			ridx = rights[grp[ridx]] + 1;
		}
		else
			break;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];

	for (int i = 1; i <= n;){
		++GN;
		lefts[GN] = i;
		sz[GN]++;
		grp[i] = GN;
		i++;
		while (a[i] == a[i - 1]){
			sz[GN]++;
			grp[i] = GN;
			i++;
		}
		rights[GN] = i - 1;
	}

	int ans = 0;
	for (int i = 1; i <= n; i++){
		if (a[i - 1] == a[i] && a[i] == a[i + 1])continue;
		for (int j = 1; j <= 2; j++){
			int c = (a[i] + j - 1) % 3 + 1;
			int candi = 0;
			if (a[i - 1] == a[i + 1]){
				if (a[i + 1] == c){
					if (sz[grp[i - 1]] + sz[grp[i + 1]] >= 3){
						candi += 1;
						candi += sz[grp[i - 1]] + sz[grp[i + 1]];
						candi += go(lefts[grp[i - 1]] - 1, rights[grp[i + 1]] + 1);
						ans = max(ans, candi);
					}
				}
			}
			else{
				if (a[i - 1] == c){
					if (sz[grp[i - 1]] >= 3){
						candi += sz[grp[i - 1]];
						candi += go(lefts[grp[i - 1]] - 1, i + 1);
						ans = max(ans, candi);
					}
				}
				else if (a[i + 1] == c){
					if (sz[grp[i + 1]] >= 3){
						candi += sz[grp[i + 1]];
						candi += go(i - 1, rights[grp[i + 1]] + 1);
						ans = max(ans, candi);
					}
				}
			}
		}
	}
	cout << n - ans;
	return 0;
}