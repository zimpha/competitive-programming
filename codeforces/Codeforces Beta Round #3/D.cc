#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

priority_queue<pair<LL, LL> > q;
int cnt, a, b;
LL ret;
string st;

int main()
{
	while (!q.empty()) q.pop();
	cin >> st; cnt=ret=0;
	for (int i=0; i<st.size(); i++)
	{
		if (st[i]=='(') cnt++;
		else if (st[i]==')') cnt--;
		else
		{
			cin >> a >> b;
			st[i]=')'; cnt--;
			ret+=b; q.push(make_pair(b-a, i));
		}
		if (cnt<0)
		{
			if (q.empty()) break;
			pair<LL, LL> tt=q.top(); q.pop();
			cnt+=2; ret-=tt.first;
			st[tt.second]='(';
		}
	}
	if (cnt!=0) cout << "-1\n";
	else cout << ret << endl << st << endl;
	return 0;
}
