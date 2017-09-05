#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

vector<int> G[MAXN], C[MAXN], ret;
int deg[MAXN], f[MAXN], n, m, cnt;
bool vis[MAXN];

void dfs(int u, vector<int> &cc) {
    vis[u] = true; cc.push_back(u);
    for (auto v : G[u]) {
        if (!vis[v]) dfs(v, cc);
    }
}

bool circle(vector<int> cc) {
    for (int v : cc) {
        if (deg[v] != 2) return false;
    }
    return true;
}

int get(int x) {
    if (x != f[x]) f[x] = get(f[x]);
    return f[x];
}

bool chain(vector<int> cc) {
    ret.clear();
    int v0 = -1;
    for (int v : cc) {
        if (deg[v] > 2) return false;
        if (deg[v] == 0) v0 = v;
        if (deg[v] == 1) ret.push_back(v);
        f[v] = get(f[cc[0]]);
    }
    if (ret.size() > 2) return false;
    if (ret.size() == 0 && v0 == -1) return false;
    if (ret.size() == 0) ret.push_back(v0), ret.push_back(v0);
    return true;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) f[i] = i;
    for (int i = 0; i < m; ++ i) {
        int x, y; cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
        ++ deg[x]; ++ deg[y];
    }
    for (int i = 1; i <= n; ++ i) {
        if (!vis[i]) {
            dfs(i, C[cnt]);
            ++ cnt;
        }
    }
    if (cnt == 1) {
        if (circle(C[0])) cout << "YES\n0" << endl;
        else if (chain(C[0])) {
            cout << "YES" << endl;
            cout << "1" << endl;
            if (ret[0] > ret[1]) swap(ret[0], ret[1]);
            cout << ret[0] << " " << ret[1] << endl;
        }
        else cout << "NO" << endl;
    }
    else {
        bool flag = true;
        vector<int> nodes;
        for (int i = 0; i < cnt; ++ i) {
            if (!chain(C[i])) flag = false;
        }
        if (!flag) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            cout << cnt << endl;
            for (int i = 1; i <= n; ++ i) {
                for (int j = i; j <= n; ++ j) {
                    if (deg[i] < 2 && deg[j] < 2 && get(i) != get(j)) {
                        cout << i << " " << j << endl;
                        ++ deg[i], ++ deg[j], f[get(i)] = get(j);
                    }
                }
            }
            for (int i = 1, t = 0; i <= n; ++ i) {
                if (deg[i] == 0) {
                    cout << i << " " << i << endl;
                    break;
                }
                if (deg[i] == 1) {
                    cout << i << " \n"[t == 1];
                    ++ t;
                }
            }
        }
    }
    return 0;
}
