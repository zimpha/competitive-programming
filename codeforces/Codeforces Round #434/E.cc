#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 5e5 + 10;

using int64 = long long;

namespace lct { //以路径加为例
  struct Node *null;
  struct Node{
    Node *fa,*ch[2];
    int sz,rev;
    int64 val,add,sum;
    void clr(int v) {
      fa=ch[0]=ch[1]=null;
      sum=val=v; sz=1; add=0;
    }
    void upd(); void psd(); void mark_add(int64 v);
    void setc(Node *p,int d){ch[d]=p;p->fa=this;}
    bool d(){return fa->ch[1]==this;}
    bool isroot(){return fa==null||(fa->ch[0]!=this&&fa->ch[1]!=this);}
    void flip(){if(this==null)return;std::swap(ch[0],ch[1]);rev^=1;}
    void go(){if(!isroot())fa->go();psd();}
    void make_root(){access()->flip();}
    void cut() {access();ch[0]->fa=null;ch[0]=null;upd();}
    void rot(){
      Node *f=fa,*p=fa->fa;
      int c=d(),cc=fa->d();
      f->setc(ch[!c],c); this->setc(f,!c);
      if (p->ch[cc]==f) p->setc(this,cc);
      else this->fa = p; f->upd();
    }
    Node* splay(){
      for (go(); !isroot(); rot()) {
        if(!fa->isroot()) d()==fa->d()?fa->rot():rot();
      }
      upd(); return this;
    }
    Node* access(){
      for(Node *p=this,*q=null; p!=null; q=p,p=p->fa){
        p->splay()->setc(q,1); p->upd();
      }
      return splay();
    }
    Node* find_root(){
      Node *x;
      for (x=access(); x->psd(),x->ch[0]!=null; x=x->ch[0]);
      return x;
    }
    void cut(Node *x){
      if (this== x||find_root()!=x->find_root()) return;
      else {x->make_root();cut();}
    }
    void link(Node *x){
      if(find_root()==x->find_root())return;
      else {make_root(); fa=x;}
    }
  } pool[N], *tail;
  //以下函数根据题目修改
  void Node::upd() {
    sz=1+ch[0]->sz+ch[1]->sz;
    sum=val+ch[0]->sum+ch[1]->sum;
  }
  void Node::mark_add(int64 v) {
    if (this==null) return;
    val += v; add += v;
    sum += v * sz;
  }
  void Node::psd() {
    if (rev){
      ch[0]->flip();ch[1]->flip();
      rev = 0;
    }
    if (add) {
      ch[0]->mark_add(add); ch[1]->mark_add(add);
      add = 0;
    }
  }
  void init() {
    tail=pool; null=tail++;
    null->fa=null->ch[0]=null->ch[1]=null;
    null->sz=null->rev=null->val=null->sum=null->add=0;
  }
  Node* new_node() {
    tail->fa = tail->ch[0] = tail->ch[1] = null;
    tail->sz = 1;
    tail->rev = tail->val = tail->sum = tail->add = 0;
    return tail++;
  }
}

std::vector<int> depth[N], tree[N];

void dfs(int u, int d) {
  depth[d].push_back(u);
  for (auto &&v: tree[u]) dfs(v, d + 1);
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<lct::Node*> nodes(n);
  std::vector<int> parent(n);
  lct::init();
  int root = 0;
  for (int i = 0; i < n; ++i) {
    nodes[i] = lct::new_node();
    scanf("%d", &parent[i]);
    --parent[i];
    if (parent[i] != -1) tree[parent[i]].push_back(i);
    else root = i;
  }
  std::vector<int64> ret(n);
  dfs(root, 0);
  for (int i = 0; i < n; ++i) {
    for (auto &&x: depth[i]) {
      if (parent[x] != -1) {
        nodes[x]->fa = nodes[parent[x]];
      }
      nodes[x]->access();
      nodes[x]->mark_add(1);
    }
    for (auto &&x: depth[i]) {
      nodes[x]->access();
      ret[x] = nodes[x]->sum - i - 1;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%lld", ret[i]);
  }
  puts("");
  return 0;
}
