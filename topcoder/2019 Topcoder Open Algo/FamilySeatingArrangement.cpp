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

using int64 = long long;

const int N = 2000 + 10;
const int mod = 1e9 + 7;

int64 s[N][N], fac[N], pw[N], ifac[N];

int64 pow_mod(int64 a, int64 n) {
    int64 r = 1;
    for (; n; n >>= 1) {
        if (n & 1) r = r * a % mod;
        a = a * a % mod;
    }
    return r;
}

class FamilySeatingArrangement {
    public:
    int countWays(vector<int> a, int k) {
        int n = a.size();
        s[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                s[i][j] = (j * s[i - 1][j] + s[i - 1][j - 1]) % mod;
            }
        }
        ifac[0] = fac[0] = 1;
        for (int i = 1; i <= k; ++i) {
            fac[i] = fac[i - 1] * i % mod;
            ifac[i] = pow_mod(fac[i], mod - 2);
        }
        int64 ret = 0;
        for (int m = 1; m <= n && m <= k; ++m) {
            int64 tmp = s[n][m] * fac[k] % mod * ifac[k - m] % mod;
            pw[0] = 1;
            for (int i = 1; i <= 1000; ++i) {
                pw[i] = pw[i - 1] * (k - m + 1) % mod;
            }
            for (int j = 0; j < n; ++j) {
                tmp = tmp * pw[a[j]] % mod;
            }
            ret += tmp;
        }
        return ret % mod;
    }
};

// CUT begin
ifstream data("FamilySeatingArrangement.sample");

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

bool do_test(vector<int> a, int k, int __expected) {
    time_t startClock = clock();
    FamilySeatingArrangement *instance = new FamilySeatingArrangement();
    int __result = instance->countWays(a, k);
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
        vector<int> a;
        from_stream(a);
        int k;
        from_stream(k);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1562429433;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FamilySeatingArrangement (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
