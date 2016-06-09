#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int MAXN = 510;
const int MAXX = 1010;
const int inf = (1 << 30);

int n;

vector<int> ar[MAXX];
vector<int> trap[MAXX];

vector<int> helpx;
vector<int> helpy;

int ans1, ans2;
void optimize(int a, int b) {
	if (a < ans1) return;
	if (a == ans1) ans2 = min(ans2, b);
	else {
		ans1 = a;
		ans2 = b;
	}
}

int main() {
	freopen("cowrect.in", "r", stdin);
	freopen("cowrect.out", "w", stdout);
	_;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		char cow;
		cin >> x >> y >> cow;
		if (cow == 'H') {
			ar[x].push_back(y);
		}
		else {
			trap[x].push_back(y);
		}
		helpx.push_back(x);
		helpy.push_back(y);
	}
	
	sort(helpx.begin(), helpx.end());
	sort(helpy.begin(), helpy.end());
	helpx.resize(unique(helpx.begin(), helpx.end()) - helpx.begin());
	helpy.resize(unique(helpy.begin(), helpy.end()) - helpy.begin());
	
	for (int i = 0; i < helpy.size(); i++) {
		for (int j = i; j < helpy.size(); j++) {
			int bottom = helpy[i];
			int top = helpy[j];
			int cur = 0;
			int l = -1;
			for (int k = 0; k < helpx.size(); k++) {
				int x = helpx[k];
				if (cur == 0) l = x;
				bool nooo = false;
				int add = 0;
				for (auto &y : ar[x]) {
					add += y >= bottom && y <= top;
				}
				for (auto &y : trap[x]) {
					nooo |= y >= bottom && y <= top;
				}
				if (nooo) {
					cur = 0;
					l = -1;
				}
				else {
					cur += add;
					optimize(cur, (top - bottom) * (x - l));
				}
			}
		}
	}
	cout << ans1 << endl << ans2 << endl;
}
