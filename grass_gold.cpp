#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int MAXN = 100010;
const int inf = (1 << 30);

int n, m;
vector<int> ingoing[MAXN], outgoing[MAXN];

bitset<MAXN> vis;

vector<int> order;
void toposort(int u) {
	if (vis[u]) return;
	vis[u] = true;
	for (auto &v : outgoing[u]) {
		toposort(v);
	}
	order.push_back(u);
}

int t;
int scc[MAXN];
int sccsz[MAXN];
void computescc1(int u) {
	if (vis[u]) return;
	vis[u] = true;
	scc[u] = t;
	sccsz[t]++;
	for (auto &v : ingoing[u]) {
		computescc1(v);
	}
}

vector<int> dagingoing[MAXN], dagoutgoing[MAXN];
void computescc2(int u) {
	if (vis[u]) return;
	vis[u] = true;
	for (auto &v : outgoing[u]) {
		if (scc[v] != scc[u]) {
			dagingoing[scc[v]].push_back(scc[u]);
			dagoutgoing[scc[u]].push_back(scc[v]);
		}
		computescc2(v);
	}
}

int dp1[MAXN], dp2[MAXN];
int bt(int dp[], vector<int> in[], int u) {
	if (u == scc[1]) {
		return 0;
	}
	if (in[u].empty()) {
		return -inf;
	}
	if (dp[u] != -1) return dp[u];
	int &ret = dp[u];
	ret = -inf;
	for (auto &v : in[u]) {
		ret = max(ret, sccsz[u] + bt(dp, in, v));
	}
	return ret;
}

int main() {
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
	_;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		ingoing[v].push_back(u);
		outgoing[u].push_back(v);
	}
	vis = 0;
	for (int i = 1; i <= n; i++) {
		toposort(i);
	}
	reverse(order.begin(), order.end());
	vis = 0;
	for (int i = 0; i < n; i++) {
		t += !vis[order[i]];
		computescc1(order[i]);
	}
	vis = 0;
	for (int i = 1; i <= n; i++) {
		computescc2(i);
	}
	for (int i = 1; i <= t; i++) {
		sort(dagingoing[i].begin(), dagingoing[i].end());
		dagingoing[i].resize(unique(dagingoing[i].begin(), dagingoing[i].end()) - dagingoing[i].begin());
		sort(dagoutgoing[i].begin(), dagoutgoing[i].end());
		dagoutgoing[i].resize(unique(dagoutgoing[i].begin(), dagoutgoing[i].end()) - dagoutgoing[i].begin());
	}
	
	memset(dp1, -1, sizeof dp1);
	memset(dp2, -1, sizeof dp2);
	
	int ans = sccsz[scc[1]];
	for (int i = 1; i <= t; i++) {
		for (auto &v : dagingoing[i]) {
			ans = max(ans, bt(dp1, dagingoing, i) + bt(dp2, dagoutgoing, v) + sccsz[scc[1]]);
		}
	}

	cout << ans << endl;
}
