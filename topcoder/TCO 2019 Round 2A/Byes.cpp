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

class Byes {
    public:
    long long solve(long long bound, int n, int m) {
        if (bound == 0) return -1;
        std::string s;
        long long now = 0;
        long long ret = -1;
        for (int i = n - 1; i >= 0; --i) {
            int o = bound >> i & 1;
            if (o == 0) {
                s += char('0' + 1);
                int z = 0, tot = 0;
                for (size_t j = 0, k = 0; j < s.size(); j = k) {
                    for (k = j; k < s.size() && s[j] == s[k]; ++k);
                    if (j == 0) ++tot;
                    else if (s[j] == '0') tot += k - j;
                }
                if (tot == m) {
                    auto tmp = now | (1ll << i);
                    if (ret == -1 || ret > tmp) ret = tmp;
                }
                int rest = i;
                if (tot < m && rest > 1 && rest > m - tot) {
                    auto tmp = now | (1ll << i);
                    int one = rest - (m - tot);
                    tmp |= 1ll << (one - 1);
                    if (ret == -1 || ret > tmp) ret = tmp;
                }
                s.pop_back();
            }
            now |= (long long)(o) << i;
            s += char('0' + o);
        }
        return ret;
    }
    long long getNumberOfPlayers(long long lowerBound, int numberOfByes) {
        int mn = 0;
        --lowerBound;
        for (auto m = lowerBound; m; m >>= 1) ++mn;
        if (mn == 0) mn = 1;
        long long ret = solve(lowerBound, mn, numberOfByes);
        if (ret != -1) return ret;
        if (numberOfByes == 0) {
            return 1ll << mn;
        }
        if (numberOfByes == 1) {
            return (1ll << mn) | (1ll << (mn - 1));
        }
        mn = std::max(mn, numberOfByes);
        int one = mn - numberOfByes + 1;
        return 1ll << mn | ((1ll << one) - 1);
    }
};

// CUT begin
ifstream data("Byes.sample");

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

bool do_test(long long lowerBound, int numberOfByes, long long __expected) {
    time_t startClock = clock();
    Byes *instance = new Byes();
    long long __result = instance->getNumberOfPlayers(lowerBound, numberOfByes);
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
        long long lowerBound;
        from_stream(lowerBound);
        int numberOfByes;
        from_stream(numberOfByes);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(lowerBound, numberOfByes, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1558574919;
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
        cout << "Byes (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
