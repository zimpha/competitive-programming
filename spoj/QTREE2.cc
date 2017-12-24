#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10000 + 10, inf = 1e9;

struct Node *null;
struct Node {
    Node *p, *ch[2];
    int sz, sum, val, id, rev;
    bool d() {return this == p->ch[1];}
    bool isroot() {return p == null || (p->ch[0] != this && p->ch[1] != this);}
    void setc(Node *c, int d) {ch[d] = c; c->p = this;}
    void flip() {swap(ch[0], ch[1]); rev ^= 1;}
    void go() {if (!isroot()) p->go(); pushdown();}
    void rot() {
        Node *f = p, *ff = p->p;
        int c = d(), cc = p->d();
        f->setc(ch[!c], c); this->setc(f, !c);
        if (ff->ch[cc] == f) ff->setc(this, cc);
        else this->p = ff;
        f->update();
    }
    Node* splay() {
        for (go(); !isroot(); rot()) {
            if (!p->isroot()) d() == p->d() ? p->rot() : rot();
        }
        update(); return this;
    }
    Node *access() {
        for (Node *x = this, *y = null; x != null; y = x, x = x->p) {
            x->splay()->setc(y, 1); x->update();
        }
        return splay();
    }
    Node *find_root() {
        Node *x;
        for (x = access(); x->pushdown(), x->ch[0] != null; x = x->ch[0]);
        return x;
    }
    void make_root() {
        access()->flip();
    }
    void cut() {
        access();
        ch[0]->p = null, ch[0] = null;
        update();
    }
    void cut(Node *x) {
        if (this == x || find_root() != x->find_root()) return;
        else {x->make_root(); cut();}
    }
    void link(Node *x) {
        if (find_root() == x->find_root()) return;
        else {make_root(); p = x;}
    }
    void update() {
        // modify according to problem
        sum = val + ch[0]->sum + ch[1]->sum;
        sz = 1 + ch[0]->sz + ch[1]->sz;
    }
    void pushdown() {
        // modify according to problem
    }
} mem[MAXN], *pt[MAXN], *cnt;

inline Node *newnode(int _val = 0) {
    cnt->p = cnt->ch[0] = cnt->ch[1] = null;
    cnt->sz = 1; cnt->sum = cnt->val = _val; cnt->rev = 0;
    return cnt ++;
}

void init(int n) {
    cnt = mem; null = newnode();
    null->p = null->ch[0] = null->ch[1] = null; null->sz = 0;
    for (int i = 0; i < n; ++ i) {
        pt[i] = newnode();
        pt[i]->id = i + 1;
    }
}

Node* get_kth(Node *o, int k) { // k >= 1
    Node *x = o;
    while (x->ch[0]->sz + 1 != k) {
        if (k < x->ch[0]->sz + 1) x = x->ch[0];
        else k -= x->ch[0]->sz + 1, x = x->ch[1];
    }
    return x;
    /*
    for (Node *x = o; ;) {
        int c = x->ch[0]->sz + 1;
        if (k == c) return x;
        if (k > c) k -= c + 1, x = x->ch[1];
        else x = x->ch[0];
    }
    return null;*/
}

struct Edge {
    int v, w, nxt;
    Edge() {}
    Edge(int a, int b, int c) : v(a), w(b), nxt(c) {}
} E[MAXN << 1];

int G[MAXN], vis[MAXN];
int N, sz;

void dfs(int u, int f) {
    for (int now = G[u]; ~now; now = E[now].nxt) {
        int v = E[now].v, w = E[now].w; if (v == f) continue;
        dfs(v, u);
        pt[v]->val = w;
        pt[v]->update(); pt[v]->p = pt[u];
    }
}

void build_tree(int n) {
    for (int i = 0; i < n; ++ i) vis[i] = false;
    queue<int> Q; Q.push(0); vis[0] = true;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int now = G[u]; ~now; now = E[now].nxt) {
            int v = E[now].v, w = E[now].w; if (vis[v]) continue;
            vis[v] = true; Q.push(v);
            pt[v]->val = w; pt[v]->id = v + 1;
            pt[v]->update(); pt[v]->p = pt[u];
        }
    }
}

int query_kth(Node *x, Node *y, int k) {
    x->access();
    for (x = null; y != null; x = y, y = y->p) {
        y->splay();
        if (y->p == null) {
            int c = y->ch[1]->sz + 1;
            if (c == k) return y->id;
            else if (c > k) return get_kth(y->ch[1], c - k)->id;
            else return get_kth(x, k - c)->id;
        }
        y->setc(x, 1); y->update();
    }
}

int query_dis(Node *x, Node *y) {
    x->access();
    for (x = null; y != null; x = y, y = y->p) {
        y->splay();
        if (y->p == null) return y->ch[1]->sum + x->sum;
        y->setc(x, 1); y->update();
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T --) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++ i) G[i] = -1;
        sz = 0; init(N);
        for (int i = 1; i < N; ++ i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w); -- u, -- v;
            E[sz] = Edge(v, w, G[u]); G[u] = sz ++;
            E[sz] = Edge(u, w, G[v]); G[v] = sz ++;
        }
        //build_tree(N);
        dfs(0, -1);
        for (char st[10]; scanf("%s", st) == 1; ) {
            if (st[1] == 'O') break;
            if (st[0] == 'D') {
                int u, v; scanf("%d%d", &u, &v); -- u; -- v;
                printf("%d\n", query_dis(pt[u], pt[v]));
            }
            else {
                int u, v, k; scanf("%d%d%d", &u, &v, &k); -- u; -- v;
                printf("%d\n", query_kth(pt[u], pt[v], k));
            }
        }
    }
    return 0;
}
