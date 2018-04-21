#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int N = 100, mod = 1e9 + 7;

using int64 = long long;

int64 pow_mod(int64 a, int64 n) {
    int64 r = 1;
    for (; n; n >>= 1) {
        if (n & 1) r = r * a % mod;
        a = a * a % mod;
    }
    return r;
}

class SubtreeSumHash {
    public:
    std::vector<std::vector<int>> edges;
    std::vector<int> weight;
    int64 dp[N];
    int n, x;

    void dfs(int u, int p = -1) {
        dp[u] = 1;
        for (auto &&v: edges[u]) if (v != p) {
            dfs(v, u);
            dp[u] *= dp[v] + 1;
            dp[u] %= mod;
        }
        dp[u] %= mod;
        dp[u] = dp[u] * pow_mod(x, weight[u]) % mod;
    }

    int count(vector<int> weight, vector<int> p, int x) {
        this->weight = weight;
        this->x = x;
        n = weight.size();
        edges.resize(n);
        for (int i = 0; i < n - 1; ++i) {
            edges[p[i]].emplace_back(i + 1);
            edges[i + 1].emplace_back(p[i]);
        }
        dfs(0);
        int64 ret = 0;
        for (int i = 0; i < n; ++i) {
            ret += dp[i];
        }
        return ret % mod;
    }
};

// CUT begin
ifstream data("SubtreeSumHash.sample");

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

bool do_test(vector<int> weight, vector<int> p, int x, int __expected) {
    time_t startClock = clock();
    SubtreeSumHash *instance = new SubtreeSumHash();
    int __result = instance->count(weight, p, x);
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
        vector<int> weight;
        from_stream(weight);
        vector<int> p;
        from_stream(p);
        int x;
        from_stream(x);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(weight, p, x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1524317979;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SubtreeSumHash (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
