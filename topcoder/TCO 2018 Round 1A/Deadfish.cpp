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

const int N = 5000000 + 10, delta = 2500000;

class Deadfish {
    public:
    int dp[N], q[N];
    int shortestCode(int n) {
        int h = 0, t = 0;
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        q[t++] = 0;
        while (h < t) {
            int u = q[h++];
            if (u == n) break;
            if (u + 1 < N && dp[u + 1] == -1) {
                dp[u + 1] = dp[u] + 1;
                q[t++] = u + 1;
            }
            if (u - 1 >= 0 && dp[u - 1] == -1) {
                dp[u - 1] = dp[u] + 1;
                q[t++] = u - 1;
            }
            if (1ll * u * u < N && dp[u * u] == -1) {
                dp[u * u] = dp[u] + 1;
                q[t++] = u * u;
            }
            if (u > 0) {
                static char s[10];
                int m = 0;
                for (int x = u; x; x /= 10) {
                    s[m++] = x % 10;
                }
                std::sort(s, s + m);
                std::reverse(s, s + m);
                int r = 0;
                for (int i = 0; i < m; ++i) r = r * 10 + s[i];
                if (r < N && dp[r] == -1) {
                    dp[r] = dp[u] + 1;
                    q[t++] = r;
                }
            }
        }
        return dp[n];
    }
};

// CUT begin
ifstream data("Deadfish.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int __expected) {
    time_t startClock = clock();
    Deadfish *instance = new Deadfish();
    int __result = instance->shortestCode(N);
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
        int N;
        from_stream(N);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1524327178;
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
        cout << "Deadfish (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
