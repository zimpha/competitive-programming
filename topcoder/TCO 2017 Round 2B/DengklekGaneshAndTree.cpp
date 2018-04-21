#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int N = 1000 + 10, mod = 1e9 + 7;
using ll = long long;

class DengklekGaneshAndTree {
    public:
    std::vector<int> edges[N];
    std::string col;
    int dep[N], vis[N];
    ll dp[N][N];
    void dfs(int u, int p = -1, int d = 0) {
      dep[u] = d;
      for (auto &&v: edges[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
      }
    }
    std::pair<int, int> bfs(int u, char c) {
      std::queue<int> q;
      q.push(u);
      vis[u] = true;
      int mx = dep[u];
      int mi = dep[u];
      while (!q.empty()) {
        u = q.front();
        q.pop();
        mx = std::max(mx, dep[u]);
        mi = std::min(mi, dep[u]);
        for (auto &&v: edges[u]) {
          if (col[v] == c && !vis[v]) {
            vis[v] = true;
            q.push(v);
          }
        }
      }
      return {mi + 1, mx + 1};
    }
    int getCount(string labels, vector<int> parents) {
      col = labels;
      int n = labels.size();
      for (int i = 1; i < n; ++i) {
        edges[parents[i - 1]].push_back(i);
        edges[i].push_back(parents[i - 1]);
      }
      dfs(0);
      memset(vis, 0, sizeof(vis));
      int m = 0;
      for (int i = 0; i < n; ++i) {
        m = std::max(m, dep[i] + 1);
      }
      std::vector<std::pair<int, int>> all;
      for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
          all.push_back(bfs(i, col[i]));
        }
      }
      std::sort(all.begin(), all.end());
      //for (auto &&e: all) printf("%d %d\n", e.first, e.second);
      dp[0][0] = 1;
      for (size_t i = 0; i < all.size(); ++i) {
        for (int j = 0; j <= m; ++j) {
          if (dp[i][j] == 0) continue;
          dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
          if (all[i].second <= j) dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
          else if (all[i].first <= j + 1) {
            dp[i + 1][all[i].second] = (dp[i + 1][all[i].second] + dp[i][j]) % mod;
          }
        }
      }
      int ret = 0;
      for (int i = 0; i <= all.size(); ++i) {
        ret = (ret + dp[i][m]) % mod;
      }
      //printf("%lld\n", dp[all.size()][m]);
      return dp[all.size()][m];
    }
};

// CUT begin
ifstream data("DengklekGaneshAndTree.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string labels, vector<int> parents, int __expected) {
    time_t startClock = clock();
    DengklekGaneshAndTree *instance = new DengklekGaneshAndTree();
    int __result = instance->getCount(labels, parents);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string labels;
        from_stream(labels);
        vector<int> parents;
        from_stream(parents);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(labels, parents, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499530522;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "DengklekGaneshAndTree (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
