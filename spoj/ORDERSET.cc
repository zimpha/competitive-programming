#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int INF = ~0U>>1;;

struct Node {
	int value, key, size;
	Node* ch[2];
	Node (int v, Node* n) : value(v) {
		ch[0] = ch[1] = n; size = 1; key = rand() - 1;
	}
	void Update() { size = ch[0]->size + ch[1]->size + 1; }
}*root, *null;

void rot(Node* &o, int d) { //d = 1, rotate left; d = 0, rotate right
	Node* k = o->ch[d];
	o->ch[d] = k->ch[!d];
	k->ch[!d] = o;
	o->Update(); k->Update(); o = k;
}

void Insert(Node* &o, int x) {
	if (o == null) o = new Node(x, null);
	else {
		if (x == o->value) return; //same value
		int d = x > o->value;
		Insert(o->ch[d], x);
		if (o->ch[d]->key < o->key) rot(o, d);
		else o->Update();
	}
}

void Delete(Node* &o, int x) {
	if (o == null) return;
	if (o->value == x) {
		int d = o->ch[1]->key < o->ch[0]->key;
		if (o->ch[d] == null) {
			delete o;
			o = null;
			return;
		}
		rot(o, d);
		Delete(o->ch[!d], x);
	} else {
		int d = x > o->value;
		Delete(o->ch[d], x);
	}
	o->Update();
}

int Kth(Node* o, int k) {
	int s = o->ch[0]->size + 1;
	if (k == s) return o->value;
	if (k < s) return Kth(o->ch[0], k);
	else return Kth(o->ch[1], k - s);
}

int Rank(Node* o, int x) {
	if (o == null) return 0;
	int s = o->ch[0]->size;
	if (x == o->value) return s;
	if (x < o->value) return Rank(o->ch[0], x);
	else return s + 1 + Rank(o->ch[1], x);
}

void init() {
	null = new Node(0, 0);
	null->ch[0] = null->ch[1] = null;
	null->size = 0; null->key = INF;
	root = null;
}

int main() {
	int Q; scanf("%d", &Q);
	init();
	while (Q --) {
		char st[10];
		int x;
		scanf("%s%d", st, &x);
		if (st[0] == 'I') Insert(root, x);
		else if (st[0] == 'D') Delete(root, x);
		else if (st[0] == 'C') printf("%d\n", Rank(root, x));
		else if (st[0] == 'K') {
			if (x > root->size) printf("invalid\n");
			else printf("%d\n", Kth(root, x));
		}
	}
	return 0;
}
