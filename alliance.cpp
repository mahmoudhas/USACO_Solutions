#include <bits/stdc++.h>

using namespace std;

#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

const int MAXN = 100010;
const int mod = 1000000007;

typedef pair<int, int> ii;
typedef long long ll;

int n, m;
vector<int> adj[MAXN];

map<ii, int> st;

bitset<MAXN> vis;
ii dfs(int u) {
	if (vis[u]) return make_pair(0, 0);
	vis[u] = true;
	ii ret = { 1, 0 };
	for (auto &v : adj[u]) {
		if (!st[{ u, v }]) continue;
		st[{ u, v }]--;
		st[{ v, u }]--;
		ii cur = dfs(v);
		ret.first += cur.first;
		ret.second += cur.second + 1;
	}
	return ret;
}

int main() {
	freopen("alliance.in", "r", stdin);
	freopen("alliance.out", "w", stdout);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
		st[{ u, v }]++;
		st[{ v, u }]++;
	}
	int ans = 1;
	for (int i = 1; i <= n; i++) if (!vis[i]) {
		ii cur = dfs(i);
		if (cur.second > cur.first) {
			ans = 0;
			break;
		}
		if (cur.second == cur.first - 1) {
			ans = (1LL * ans * cur.first) % mod;
		}
		else if (cur.second == cur.first) {
			ans = ans * 2 % mod;
		}
		else assert(false);
	}
	cout << ans << endl;
}
