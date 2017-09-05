#include <map>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MP make_pair
#define PB push_back

using namespace std;

typedef pair<int, int> PII;

vector<pair<int, string> > V, proc, T;

void Find(string name, int score)
{
	for (int i=0; i<V.size(); i++)
		if (V[i].second==name)
		{
			V[i].first-=score;
			return;
		}
	V.PB(MP(-score, name));
}

int main()
{
	int n, i;
	V.clear(); proc.clear(); T.clear();
	for (cin >> n, i=0; i<n; i++)
	{
		string name;
		int score;
		cin >> name >> score;
		proc.PB(MP(score, name));
		Find(name, score);
	}
	sort(V.begin(), V.end());
	int m=-V[0].first;
	for (int i=0; i<V.size(); i++)
		if (V[i].first==-m) T.PB(MP(0, V[i].second));
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<T.size(); j++)
			if (proc[i].second==T[j].second)
			{
				T[j].first-=proc[i].first;
				if (T[j].first<=-m) 
				{
					cout << T[j].second << endl;
					return 0;
				}
			}
	}
	return 0;
}
