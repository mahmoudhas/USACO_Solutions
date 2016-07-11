#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
const int MAXF = 3 * MAXN;

typedef long long ll;

ll ft[MAXF];
void add(int i, int x) {
	i++;
	for (; i < MAXF; i += i & -i) {
		ft[i] += x;
	}
}
ll rsq(int i) {
	i++;
	ll sum = 0;
	for (; i; i -= i & -i) {
		sum += ft[i];
	}
	return sum;
}

int n, x;
int ar[MAXN];
int sum[MAXN];

ll ans;

int main() {
	freopen("median.in", "r", stdin);
	freopen("median.out", "w", stdout);
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; i++) {
		scanf("%d", ar + i);
		ar[i] = ar[i] >= x;
		sum[i] = ar[i] + (i ? sum[i - 1] : 0);
	}
	for (int i = 0; i <= n; i++) {
		ans += rsq(2 * sum[i] - i + MAXN);
		add(2 * sum[i] - i + MAXN, 1);
	}
	printf("%lld\n", ans);
}
