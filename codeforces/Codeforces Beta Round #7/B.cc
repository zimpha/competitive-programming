#include <bits/stdc++.h>
using namespace std;

const int MAXM = 10000;

int id[MAXM], m, cnt, t;
bool vis[MAXM];

void Alloc() {
    int n, pos = -1; cin >> n;
    bool flag=  false;
    for (int i = 1; i <= m; ++ i) {
        if (vis[i] == 0) {
            flag = true;
            for (int j = 0; j < n; ++ j) {
                if (i + j > m || vis[i + j] != 0) flag = false;
            }
            if (flag) {
                pos = i;
                break;
            }
        }
    }
    if (pos == -1) cout << "NULL" << endl;
    else {
        ++ cnt;
        for (int i = 0; i < n; ++ i) id[pos + i] = cnt, vis[pos + i] = true;
        cout << cnt << endl;
    }
}

void Erase() {
    int x; cin >> x;
    bool flag = false;
    for (int i = 1; i <= m; ++ i) {
        if (vis[i] && id[i] == x) {
            vis[i] = 0;
            flag = true;
        }
    }
    if (!flag) cout << "ILLEGAL_ERASE_ARGUMENT" << endl;
}

void defragment() {
    for (int i = 1, j; i <= m; ++ i) {
        if (vis[i] == 0) {
            for (j = i; j <= m && vis[j] == 0; ++ j);
            if (j > m) break;
            for (int k = i; k <= m; ++ k) {
                vis[k] = vis[j + k - i];
                id[k] = id[j + k - i];
            }
        }
    }
}

int main() {
    cin >> t >> m; cnt = 0;
    for (int i = 1; i <= m; ++ i) vis[i] = 0;
    while (t --) {
        string type;
        cin >> type;
        if (type == "alloc") Alloc();
        else if (type == "erase") Erase();
        else defragment();
    }
    return 0;
}
