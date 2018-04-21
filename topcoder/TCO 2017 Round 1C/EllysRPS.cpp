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
#include <map>

using namespace std;

class EllysRPS {
    public:
    vector<string> s;
    int score(char a, char b) {
        if (a == b) return 0;
        if (a == 'R' && b == 'P') return -1;
        if (a == 'R' && b == 'S') return 1;
        if (a == 'P' && b == 'S') return -1;
        if (a == 'P' && b == 'R') return 1;
        if (a == 'S' && b == 'R') return -1;
        if (a == 'S' && b == 'P') return 1;
        return 0;
    }
    long long getCount(vector<string> s) {
        this->s = s;
        int n = s.size(), m = s[0].size();
        int a = m / 2, b = m - a;
        vector<int> pw(m + 1, 1);
        for (int i = 1; i <= m; ++i) pw[i] = pw[i - 1] * 3;
        map<vector<int>, int> count;
        for (int mask = 0; mask < pw[a]; ++mask) {
            vector<int> sum(n);
            for (int i = 0; i < a; ++i) {
                char u = "RSP"[mask / pw[i] % 3];
                for (int j = 0; j < n; ++j) {
                    sum[j] += score(u, s[j][i]);
                }
            }
            count[sum]++;
        }
        long long ret = 0;
        for (int mask = 0; mask < pw[b]; ++mask) {
            vector<int> sum(n);
            for (int i = 0; i < b; ++i) {
                char u = "RSP"[mask / pw[i] % 3];
                for (int j = 0; j < n; ++j) {
                    sum[j] -= score(u, s[j][i + a]);
                }
            }
            ret += count[sum];
        }
        return ret;
    }
};

// CUT begin
ifstream data("EllysRPS.sample");

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

bool do_test(vector<string> strategies, long long __expected) {
    time_t startClock = clock();
    EllysRPS *instance = new EllysRPS();
    long long __result = instance->getCount(strategies);
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
        vector<string> strategies;
        from_stream(strategies);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(strategies, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1524320800;
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
        cout << "EllysRPS (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
