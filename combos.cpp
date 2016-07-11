#include <bits/stdc++.h>

using namespace std;

#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl "\n"

typedef pair<int, int> ii;

const int MAXN = 21;
const int MAXL = 16;
const int MAXK = 1010;
const int BASE = 3;

int n, k;
string ar[MAXN];

ii tran[MAXN][MAXL][BASE];
int score[MAXN][MAXL];

int memo[MAXK][MAXN][MAXL];
int bt(int i, int n1, int l1) {
	if (i == k) return 0;
	int &ret = memo[i][n1][l1];
	if (ret != -1) return ret;
	ret = 0;
	for (int nex = 0; nex < BASE; nex++) {
		if (tran[n1][l1][nex].first == -1) continue;
		ret = max(ret, score[n1][l1] + bt(i + 1, tran[n1][l1][nex].first, tran[n1][l1][nex].second));
	}
	return ret;
}

bool cmp(string &a, string &b) {
	return a.size() > b.size();
}

int main() {
	freopen("combos.in", "r", stdin);
	freopen("combos.out", "w", stdout);
	_;
	cin >> n >> k;
	for (int n1 = 0; n1 < n; n1++) {
		cin >> ar[n1];
	}
	sort(ar, ar + n, cmp);

	for (int n1 = 0; n1 < n; n1++) {

		for (int l1 = 0; l1 < ar[n1].size(); l1++) {
			string cur = ar[n1].substr(0, l1 + 1);

			for (int nex = 0; nex < BASE; nex++) {
				tran[n1][l1][nex] = { -1, -1 };
				string cur1 = cur + char(nex + 'A');
				bool found = false;
				for (int l2 = cur1.size() - 1; l2 >= 0 && !found; l2--) {
					for (int n2 = 0; n2 < n && !found; n2++) {
						if (ar[n2].size() < l2 + 1) continue;
						string cur2 = ar[n2].substr(0, l2 + 1);
						if (cur1.substr(cur1.size() - cur2.size()) == cur2) {
							tran[n1][l1][nex] = { n2, l2 };
							found = true;
						}
					}
				}
			}

			for (int i = 0; i < n; i++) {
				if (ar[i].size() > cur.size()) continue;
				score[n1][l1] += cur.substr(cur.size() - ar[i].size()) == ar[i];
			}

		}
	}

	memset(memo, -1, sizeof memo);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans = max(ans, bt(0, i, 0));
	}
	cout << ans << endl;
}
