#include <cstdio>
#include <cstring>
#include <cstdlib>

struct node
{
	int v;
	node *s[26];
};

char st[100];
node *T;
int n;

node *new_node()
{
	node *p=new node;
	p->v=0;
	for (int i=0; i<26; i++) p->s[i]=NULL;
	return p;
}

int Insert(char *st, int n)
{
	node *p=T;
	for (int i=0; i<n; i++)
	{
		if (p->s[st[i]-'a']==NULL) p->s[st[i]-'a']=new_node();
		p=p->s[st[i]-'a'];
	}
	p->v++;
	return p->v;
}

int main()
{
	T=new_node();
	scanf("%d", &n);
	for (int i=0; i<n; i++)
	{
		scanf("%s", st);
		int t=Insert(st, strlen(st));
		if (t==1) puts("OK");
		else printf("%s%d\n", st, t-1);
	}
	return 0;
}
