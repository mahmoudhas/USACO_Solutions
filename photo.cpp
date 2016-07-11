#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20010;

map<int, int> pos[5];

bool cmp(int lhs, int rhs) {
	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		cnt += pos[i][lhs] < pos[i][rhs];
	}
	return cnt >= 3;
}

int n;
int ar[MAXN];

int main() {
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
	
	cin >> n;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n; j++) {
			cin >> ar[j];
			pos[i][ar[j]] = j;
		}
	}
	sort(ar, ar + n, cmp);
	for (int i = 0; i < n; i++) {
		printf("%d\n", ar[i]);
	}
}
