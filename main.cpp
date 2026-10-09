#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
const ll inf = LONG_LONG_MAX / 2;

typedef vector<bitset<13000>> vb;
struct Maxclique {
	double limit=0.025, pk=0;
	struct Vertex { int i, d=0; };
	typedef vector<Vertex> vv;
	vb e;
	vv V;
	vector<vi> C;
	vi qmax, q, S, old;
	void init(vv& r) {
		for (auto& v : r) v.d = 0;
		for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
		sort(all(r), [](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d;
		rep(i,0,sz(r)) r[i].d = min(i, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (sz(R)) {
			if (sz(q) + R.back().d <= sz(qmax)) return;
			q.push_back(R.back().i);
			vv T;
			for(auto v:R) if (e[R.back().i][v.i]) T.push_back({v.i});
			if (sz(T)) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
				C[1].clear(), C[2].clear();
				for (auto v : T) {
					int k = 1;
					auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(all(C[k]), f)) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) T[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) T[j - 1].d = 0;
				rep(k,mnk,mxk + 1) for (int i : C[k])
					T[j].i = i, T[j++].d = k;
				expand(T, lev + 1);
			} else if (sz(q) > sz(qmax)) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vi maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vb conn) : e(conn), C(sz(e)+1), S(sz(C)), old(S) {
		rep(i,0,sz(e)) V.push_back({i});
	}
};

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	ll n;
	string s;
	cin >> n >> s;
	vector<string> words(n);
	vector<ll> anscount(26);
	rep(i, 0, 5) anscount[s[i] - 'A']++;
	rep(i, 0, n) cin >> words[i];
	vb adj(n);
	ll edges = 0;
	vector<tuple<ll, vector<ll>, ll>> ordering(n);
	rep(i, 0, n) {
		vector<ll> acount(26);
		rep(k, 0, 5) acount[words[i][k] - 'A']++;
		rep(k, 0, 26) acount[k] = min(acount[k], anscount[k]);
		ll repeat = 0;
		rep(k, 0, 5) if (s[k] == words[i][k]) repeat++;
		ordering[i] = {repeat, acount, i};
	}
	rep(i, 0, n) rep(j, 0, n) if (i != j) {
		vector<ll> acount(26), bcount(26);
		rep(k, 0, 5) acount[words[i][k] - 'A']++;
		rep(k, 0, 5) bcount[words[j][k] - 'A']++;
		bool good = true;
		rep(k, 0, 5) if (words[i][k] == s[k] && words[j][k] != s[k]) good = false;
		rep(k, 0, 5) if (words[i][k] != s[k] && words[j][k] == words[i][k]) good = false;
		rep(k, 0, 26) {
			if (acount[k] > anscount[k] && bcount[k] != anscount[k]) good = false;
			if (acount[k] <= anscount[k] && bcount[k] < acount[k]) good = false;
		}
		if (good) {
			if (!adj[i][j]) edges++;
			adj[i].set(j);
			adj[j].set(i);
		}
	}
	cerr << edges << endl;
	Maxclique mc(adj);
	vi x = mc.maxClique();
	sort(all(x), [&](int a, int b){ return ordering[a] < ordering[b]; });
	for (int y : x) {
		cout << words[y] << endl;
	}
}
