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

const int mod = 1e9 + 7;

class IncreasingNumber {
    public:
    std::pair<int, std::vector<int64>> prepare(int64 n, int m) {
        std::vector<int64> last(m, -1);
        std::vector<int64> cnt(m, 0);
        int x = 0, start = -1, period = -1;
        for (int i = 0; i < n; ++i) {
            x = (x * 10 + 1) % m;
            if (last[x] != -1) {
                start = last[x];
                period = i - last[x];
                break;
            }
            last[x] = i;
        }
        if (start == -1) {
            int s = 0;
            for (int i = 0; i < n; ++i) {
                s = (s * 10 + 1) % m;
                cnt[s]++;
            }
            return {s, cnt};
        }
        n -= start;
        int64 y = n / period;
        int64 r = n % period;
        x = 0;
        for (int i = 0; i < start; ++i) {
            x = (x * 10 + 1) % m;
            cnt[x]++;
        }
        int s = x;
        for (int i = 0; i < period; ++i) {
            x = (x * 10 + 1) % m;
            if (y) cnt[x] += y;
            if (i < r) ++cnt[x];
            if (i == r - 1) s = x;
        }
        if (r == 0) s = x;
        return {s, cnt};
    }

    int64 pow_mod(int64 a, int64 n) {
        int64 r = 1;
        for (; n; n >>= 1) {
            if (n & 1) r = r * a % mod;
            a = a * a % mod;
        }
        return r;
    }

    int64 dp[501][9][500], inv[10];

    void update(int64 &x, int64 y) {
        x = (x + y) % mod;
    }

    int64 binom(int64 n, int m) {
        int64 ret = 1;
        for (int i = 0; i < m; ++i) {
            ret = (n - i) % mod * ret % mod * inv[i + 1] % mod;
        }
        return ret;
    }

    int countNumbers(int64 n, int m) {
        for (int i = 1; i < 10; ++i) {
            inv[i] = pow_mod(i, mod - 2);
        }
        auto res = prepare(n, m);
        auto s = res.first;
        auto cnt = res.second;
        memset(dp, 0, sizeof(dp));
        dp[0][0][s] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j <= 8; ++j) {
                for (int k = 0; k < m; ++k) if (dp[i][j][k]) {
                    update(dp[i + 1][j][k], dp[i][j][k]);
                    for (int e = 1; e + j <= 8; ++e) {
                        update(dp[i + 1][e + j][(k + i * e) % m], dp[i][j][k] * binom(cnt[i] + e - 1, e) % mod);
                    }
                }
            }
        }
        int64 ret = 0;
        for (int i = 0; i <= 8; ++i) {
            update(ret, dp[m][i][0]);
        }
        return ret;
    }
};

// CUT begin
ifstream data("IncreasingNumber.sample");

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

bool do_test(long long digits, int divisor, int __expected) {
    time_t startClock = clock();
    IncreasingNumber *instance = new IncreasingNumber();
    int __result = instance->countNumbers(digits, divisor);
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
        long long digits;
        from_stream(digits);
        int divisor;
        from_stream(divisor);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(digits, divisor, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1562412795;
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
        cout << "IncreasingNumber (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
