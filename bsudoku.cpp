#include <bits/stdc++.h>

using namespace std;

const int inf = 1 << 30;

const int N = 9;

int ar[N][N];
int p[N];

int memo[1 << N][1 << N][N][2];
int bt(int mask1, int mask2, int cur, int par) {
	if (cur == 9) {
		return !mask1 && !mask2 ? 0 : inf;
	}
	int &ret = memo[mask1][mask2][cur][par];
	if (ret == -1) ret = inf;
	else return ret;
	if (!par) ret = min(ret, bt(mask1, mask2, cur + 1, p[cur + 1]));
	int s1 = cur / 3 * 3, e1 = s1 + 3;
	int s2 = cur % 3 * 3, e2 = s2 + 3;
	for (int i = s1; i < e1; i++) {
		for (int j = s2; j < e2; j++) {
			ret = min(ret, 1 + bt(mask1 ^ (1 << i), mask2 ^ (1 << j), cur, !par));
		}
	}
	return ret;
}

int main() {	
	freopen("bsudoku.in", "r", stdin);
	freopen("bsudoku.out", "w", stdout);
	memset(memo, -1, sizeof memo);
	int mask1 = 0, mask2 = 0;
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == '1') {
				mask1 ^= 1 << i;
				mask2 ^= 1 << j;
				p[i / 3 * 3 + j / 3] ^= 1;
			}
		}
	}
	printf("%d\n", bt(mask1, mask2, 0, p[0]));
}

