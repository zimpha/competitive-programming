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
#include <cassert>

using namespace std;

int dp[2][51][51][1001];
int idx[2000];

const int mod = 1e9 + 7;

void update(int &x, int y) {
    if ((x += y) >= mod) x -= mod;
}

class ClassRankings {
    public:
    int countWays(vector<int> amt, vector<int> lo, vector<int> hi) {
        int a = amt[0], b = amt[1], c = amt[2], s = a + b + c;
        std::vector<int> xs = {0};
        for (int i = 0; i < 3; ++i) {
            for (int x = lo[i]; x <= hi[i]; ++x) xs.push_back(x);
        }
        memset(idx, -1, sizeof(idx));
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
        int m = xs.size();
        for (int i = 0; i < m; ++i) idx[xs[i]] = i;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][0] = 1;
        for (int i = 0; i <= a; ++i) {
            int u = i & 1, v = u ^ 1;
            memset(dp[v], 0, sizeof(dp[v]));
            for (int j = 0; j <= b; ++j) {
                for (int k = 0; k <= c; ++k) {
                    for (int x = 0; x + 1 < m; ++x) if (dp[u][j][k][x]) {
                        int w = dp[u][j][k][x];
                        int na = std::max(xs[x + 1], lo[0]);
                        int nb = std::max(xs[x + 1], lo[1]);
                        int nc = std::max(xs[x + 1], lo[2]);
                        if (i + 1 <= a && na <= hi[0]) {
                            assert(idx[na] != -1);
                            update(dp[v][j][k][idx[na]], w);
                        }
                        if (j + 1 <= b && nb <= hi[1]) {
                            assert(idx[nb] != -1);
                            update(dp[u][j + 1][k][idx[nb]], w);
                        }
                        if (k + 1 <= c && nc <= hi[2]) {
                            assert(idx[nc] != -1);
                            update(dp[u][j][k + 1][idx[nc]], w);
                        }
                    }
                }
            }
        }
        int ret = 0;
        for (int i = 0; i < m; ++i) {
            update(ret, dp[a & 1][b][c][i]);
        }
        return ret;
    }
};

// CUT begin
ifstream data("ClassRankings.sample");

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

bool do_test(vector<int> amt, vector<int> lo, vector<int> hi, int __expected) {
    time_t startClock = clock();
    ClassRankings *instance = new ClassRankings();
    int __result = instance->countWays(amt, lo, hi);
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
        vector<int> amt;
        from_stream(amt);
        vector<int> lo;
        from_stream(lo);
        vector<int> hi;
        from_stream(hi);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(amt, lo, hi, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1578763492;
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
        cout << "ClassRankings (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
