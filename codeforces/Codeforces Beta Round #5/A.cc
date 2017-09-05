#include <set>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

set<string> S;
string tmp;
int ans;

int main()
{
    ans=0; S.clear();
    while (getline(cin, tmp))
    {
        if (tmp[0]=='+')
        {
            tmp[0]=' ';
            S.insert(tmp);
        }
        else if (tmp[0]=='-')
        {
            tmp[0]=' ';
            S.erase(tmp);
        }
        else
        {
            int l;
            for (l=0; l<tmp.size(); l++)
                if (tmp[l]==':') break;
            ans+=(tmp.size()-l-1)*S.size();
        }
    }
    printf("%d\n", ans);
    return 0;
}
