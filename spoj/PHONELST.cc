#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

struct node {
	node *ch[10];
	bool flag;
}*root;

node *new_node() {
	node *p=new(node);
	for (int i=0; i<10; i++) p->ch[i]=NULL;
	p->flag=false; return p;
}

bool insert(char s[]) {
	node *p=root;
	bool t=false;
	for (int i=0; s[i]; i++) {
		if (p->ch[s[i]-'0']==NULL) p->ch[s[i]-'0']=new_node(), t=true;
		p=p->ch[s[i]-'0'];
		if (p->flag) return false;
	}
	if (!t) return false;
	return p->flag=true;
}

void del(node *p) {
	if (p==NULL) return;
	for (int i=0; i<10; i++) del(p->ch[i]);
	free(p);
}

int main() {
	int T, n; scanf("%d", &T);
	for (int cas=1; cas<=T; cas++) {
		scanf("%d", &n); root=new_node();
		bool flag=true;
		for (int i=0; i<n; i++) {
			char s[100]; scanf("%s", s);
			if (flag) flag=insert(s);
		}
		printf("%s\n", flag?"YES":"NO");
		del(root);
	}
	return 0;
}
