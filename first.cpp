#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

typedef long long ll;
typedef pair<int, int> ii;
#define fr first
#define sc second

const int MAXN = 300010;
const int BASE = 26;
const int inf = (1 << 30);

int n;
int t = 0;
bool yes[BASE * MAXN];
map<int, int> nxt[MAXN];

string ar[30010];

void add(string &s) {
	int u = 0;
	for (int i = 0; i < s.size(); i++) {
		int ch = s[i] - 'a';
		if (nxt[u].find(ch) == nxt[u].end()) {
			nxt[u][ch] = ++t;
		}
		u = nxt[u][ch];
		if (yes[u]) return;
	}
	yes[u] = true;
}

set<string> ans;

set<int> kills[BASE];
string cur;

void dfs(int u) {
	set<int> del;
	if (yes[u]) {
		ans.insert(cur);
		return;
	}
	vector<int> go, temp;
	for (int i = 0; i < BASE; i++) if (nxt[u].find(i) != nxt[u].end()) {
		temp.push_back(i);
	}
	for (auto &v : temp) {
		for (auto &x : kills[v]) {
			del.insert(x);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (auto &x : del) {
			for (auto &v : kills[x]) {
				del.insert(v);
			}
		}
	}
	for (auto &x : temp) if (!del.count(x)) {
		go.push_back(x);
	}
	for (auto &v : go) {
		vector<ii> temp2;
		for (auto &k : temp) if (k != v) for (auto &x : kills[k]) if (!kills[v].count(x)) {
			kills[v].insert(x);
			temp2.push_back({ v, x });
		}
		for (auto &x : temp) if (x != v && !kills[v].count(x)) {
			kills[v].insert(x);
			temp2.push_back({ v, x });
		}
		cur += v + 'a';
		dfs(nxt[u][v]);
		cur.resize(cur.size() - 1);
		for (auto &p : temp2) {
			kills[p.fr].erase(p.sc);
		}
	}
}

int main() {
	freopen("first.in", "r", stdin);
	freopen("first.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ar[i];
		add(ar[i]);
	}
	dfs(0);
	cout << ans.size() << endl;
	for (int i = 0; i < n; i++) {
		if (ans.count(ar[i])) {
			cout << ar[i] << endl;
		}
	}
}
