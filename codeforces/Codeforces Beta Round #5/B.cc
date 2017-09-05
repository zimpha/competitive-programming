#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

vector<string> VS;

inline void space(int x) {
	while (x--) cout << " ";
}

inline void star(int x) {
	while (x--) cout <<"*";
}

int main() {
	string s; VS.clear();
	int n=0;
	while (getline(cin, s)) {
		VS.push_back(s);
		n=max(n, (int)s.size());
	}
	star(n+2); cout << endl;
	bool left=true;
	for (int i=0; i<(int)VS.size(); i++) {
		star(1);
		int m=VS[i].size();
		int b=(n-m)/2, a=n-m-b;
		if (a==b) {
			space(a); cout << VS[i]; space(b);
		}
		else {
			if (!left) {
				space(a); cout << VS[i]; space(b);
			}
			else {
				space(b); cout << VS[i]; space(a);
			}
			left=!left;
		}
		star(1); cout << endl;
	}
	star(n+2); cout << endl;
	return 0;
}
