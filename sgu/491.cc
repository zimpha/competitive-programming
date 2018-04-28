#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 100000 + 10;

vector<int> divisor[MAXN];
vector<int> S[MAXN];

int main() {
    int N; scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        for (int j = i; j <= N; j += i) {
            divisor[j].push_back(i);
        }
    }
    long long ret = 0;
    /*for (int A = 1; A < N; ++ i) {
        for (int x = 1; x * A < N; ++ x) {
            int tmp = N - A * x;
        }
    }*/
    for (int i = 1; i < N; ++ i) {
        for (int _ = 0; _ <(int)divisor[i].size(); ++ _) {
            int A = divisor[i][_];
            vector<int> &tmp = divisor[N - i];
            vector<int>::iterator it = upper_bound(tmp.begin(), tmp.end(), A);
            for (; it != tmp.end(); ++ it) {
                S[A].push_back(*it);
            }
        }
    }
    for (int i = 1; i <= N; ++ i) {
        sort(S[i].begin(), S[i].end());
        S[i].erase(unique(S[i].begin(), S[i].end()), S[i].end());
        ret += S[i].size();
    }
    cout << ret << endl;
    return 0;
}
