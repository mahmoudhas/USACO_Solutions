#include <bits/stdc++.h>

using namespace std;

#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

const int MAXN = 100010;
const int MAXK = 21;
const int mod = 1000000007;

typedef pair<int, int> ii;
typedef long long ll;

int n, K;
vector<int> adj[MAXN];
int cnt[MAXN];

int dp[MAXN][MAXK];
int par[MAXN];

void dfs(int u, int p = -1) {
	par[u] = p;
	dp[u][0] = cnt[u];
	for (auto &v : adj[u]) if (p != v) {
		dfs(v, u);
		for (int i = 1; i <= K; i++) {
			dp[u][i] += dp[v][i - 1];
		}
	}
}

int main() {
	freopen("nearcows.in", "r", stdin);
	freopen("nearcows.out", "w", stdout);
	cin >> n >> K;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		cin >> cnt[i];
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= K; j++) {
			dp[i][j] += dp[i][j - 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		int k = K;
		int u = i;
		int ans = dp[u][k];
		while (--k >= 0 && u != 1) {
			int v = par[u];
			ans += dp[v][k] - (k ? dp[u][k - 1] : 0);
			u = v;
		}
		cout << ans << endl;
	}
}
