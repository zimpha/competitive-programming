#include <queue>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)

using namespace std;

const int MAXN = 10000 + 10, inf = 1e9;

struct Node *null;
struct Node {
    Node *fa, *ch[2];
    int mx, val, rev;
    bool d() {return this == fa->ch[1];}
    bool isroot() {return fa == null || (fa->ch[0] != this && fa->ch[1] != this);}
    void setc(Node *p, int d) {ch[d] = p; p->fa = this;}
    void flip() {swap(ch[0], ch[1]); rev ^= 1;}
    void go() {if (!isroot()) fa->go(); pushdown();}
    void rot() {
        Node *f = fa, *ff = fa->fa;
        int c = d(), cc = fa->d();
        f->setc(ch[!c], c); this->setc(f, !c);
        if (ff->ch[cc] == f) ff->setc(this, cc);
        else this->fa = ff;
        f->update();
    }
    Node* splay() { // rotate this to root
        for (go(); !isroot(); rot()) {
            if (!fa->isroot()) d() == fa->d() ? fa->rot() : rot();
        }
        update();
        return this;
    }
    Node* access() {
        for (Node *p = this, *q = null; p != null; q = p, p = p->fa) {
            p->splay()->setc(q, 1);
            p->update();
        }
        return splay();
    }
    Node* find_root() {
        Node *p;
        for (p = access(); p->pushdown(), p->ch[0] != null; p = p->ch[0]);
        return p;
    }
    void make_root() {
        access()->flip();
    }
    void cut() {
        access();
        ch[0]->fa = null, ch[0] = null;
        update();
    }
    void cut(Node *x) {
        if (this ==x || find_root() != x->find_root()) return;
        else {x->make_root(); cut();}
    }
    void link(Node *x) {
        if (find_root() == x->find_root()) return;
        else {make_root(); fa = x;}
    }
    void update() {
        // modify according to problem
        mx = max(val, max(ch[0]->mx, ch[1]->mx));
    }
    void pushdown() {
        // modify according to problem
    }
};

Node mem[MAXN], *cnt;
Node *pt[MAXN], *ee[MAXN];

Node *newnode(int _val = 0) {
    cnt->fa = cnt->ch[0] = cnt->ch[1] = null;
    cnt->mx = cnt->val = _val;
    return cnt ++;
}

void init(int n) {
    cnt = mem; null = newnode();
    null->fa = null->ch[0] = null->ch[1] = null;
    for (int i = 0; i < n; ++ i) pt[i] = newnode();
}

struct Edge {
    int v, w, id, nxt;
    Edge() {}
    Edge(int a, int b, int c, int d) : v(a), w(b), id(c), nxt(d) {}
} E[MAXN << 1];

int G[MAXN], vis[MAXN];
int N, sz;

void build_tree(int n) {
    for (int i = 0; i < N; ++ i) vis[i] = false;
    queue<int> Q; Q.push(0); vis[0] = true;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int now = G[u]; ~now; now = E[now].nxt) {
            int v = E[now].v, id = E[now].id;
            if (vis[v]) continue;
            vis[v] = true; Q.push(v);
            ee[id] = pt[v];
            pt[v]->val = E[now].w;
            pt[v]->update();
            pt[v]->fa = pt[u];
        }
    }
}

int query(Node *x, Node *y) {
    x->access();
    for (x = null; y != null; x = y, y = y->fa) {
        y->splay();
        if (y->fa == null) return max(y->ch[1]->mx, x->mx);
        y->setc(x, 1); y->update();
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T --) {
        scanf("%d", &N);
        init(N); sz = 0;
        for (int i = 0; i < N; ++ i) G[i] = -1;
        for (int i = 1; i < N; ++ i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w); -- u, -- v;
            E[sz] = Edge(v, w, i, G[u]); G[u] = sz ++;
            E[sz] = Edge(u, w, i, G[v]); G[v] = sz ++;
        }
        build_tree(N);
        for (char st[20]; scanf("%s", st) == 1; ) {
            if (st[0] == 'D') break;
            int x, y; scanf("%d%d", &x, &y);
            if (st[0] == 'Q') printf("%d\n", query(pt[x - 1], pt[y - 1]));
            else ee[x]->splay()->val = y, ee[x]->update();
        }
    }
    return 0;
}
