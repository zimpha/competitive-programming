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

const int N = 2e4 + 10;

class EllysWordCoins {
    public:
    int gao(string s, string t) {
        int ret = 0;
        for (int i = 0; i < s.size() || i < t.size(); ++i) {
            int a = i < s.size() ? s[i] - 'A' + 1 : 0;
            int b = i < t.size() ? t[i] - 'A' + 1 : 0;
            ret += a - b;
        }
        return ret;
    }
    map<string, int> idx;
    int getCost(vector<string> market, string S, string G) {
        int m = market.size(), n = 0;
        std::vector<int> from(m), to(m);
        std::vector<int> cost(market.size());
        for (int i = 0; i < market.size(); ++i) {
            int p = market[i].find(' ');
            string a = market[i].substr(0, p);
            string b = market[i].substr(p + 1);
            if (!idx.count(a)) idx[a] = n++;
            if (!idx.count(b)) idx[b] = n++;
            //std::cout << from[i] << ' ' << to[i] << std::endl;
            cost[i] = -gao(a, b);
            from[i] = idx[a], to[i] = idx[b];
        }
        vector<int> dis(n, 1e9);
        dis[idx[S]] = 0;
        for (int it = 0; it < dis.size(); ++it) {
            for (int i = 0; i < m; ++i) {
                if (dis[to[i]] > dis[from[i]] + cost[i]) {
                    dis[to[i]] = dis[from[i]] + cost[i];
                }
            }
        }
        return dis[idx[G]];
    }
};

// CUT begin
ifstream data("EllysWordCoins.sample");

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

bool do_test(vector<string> market, string S, string G, int __expected) {
    time_t startClock = clock();
    EllysWordCoins *instance = new EllysWordCoins();
    int __result = instance->getCost(market, S, G);
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
        vector<string> market;
        from_stream(market);
        string S;
        from_stream(S);
        string G;
        from_stream(G);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(market, S, G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1524319973;
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
        cout << "EllysWordCoins (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
