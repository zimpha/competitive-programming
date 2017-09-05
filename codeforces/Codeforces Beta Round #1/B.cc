#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

bool check(string s)
{
	if (s[0]=='R'&&isdigit(s[1]))
	{
		for (int i=2; i<s.size(); i++)
			if (isupper(s[i])) return true;
		return false;
	}
	else return false;
}

int main()
{
	int n;
	for (scanf("%d", &n); n; n--)
	{
		string s, ret;
		cin >> s;
		if (check(s))
		{
			int c=0, r=0, i=1;
			while (s[i]!='C')
			{
				r=r*10+s[i]-'0';
				i++;
			}
			i++;
			while (i<s.size())
			{
				c=c*10+s[i]-'0';
				i++;
			}
			ret="";
			while (c)
			{
				ret=(char)((c-1)%26+'A')+ret;
				c=(c-1)/26;
			}
			cout << ret << r << endl;
		}
		else
		{
			int i, r=0, c=0;
			for (i=0; i<s.size(); i++)
				if (isupper(s[i])) c=c*26+s[i]-'A'+1;
				else break;
			for (; i<s.size(); i++) r=r*10+s[i]-'0';
			cout << 'R' << r << 'C' << c << endl;
		}
	}
	return 0;
}
