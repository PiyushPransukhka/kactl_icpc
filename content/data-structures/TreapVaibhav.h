/**
 * Author: kingmessi
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: LCA
 * Inputs must be in [0, mod).
 * Time: O(log N) per query
 * Status: tested
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using pt = struct tnode*;
pt root = NULL;
struct tnode {
    int pri, val; pt c[2]; // essential
    int sz; ll sum; // for range queries
    bool flip = 0; // lazy update
    tnode(int _val) {
        pri = rng(); sum = val = _val;
        sz = 1; c[0] = c[1] = nullptr;
    }
    ~tnode() { rep(i,0,2) delete c[i]; } /// assume no sharing of data
};
int getsz(pt x) { return x?x->sz:0; }
ll getsum(pt x) { return x?x->sum:0; }
void prop(pt x) { // lazy propagation
    if (!x || !x->flip) return;   
    swap(x->c[0],x->c[1]);
    x->flip = 0; rep(i,0,2) if (x->c[i]) x->c[i]->flip ^= 1;
    // return x;
}
pt calc(pt x) {
    pt a = x->c[0], b = x->c[1];
    // assert(!x->flip); 
    prop(a), prop(b);
    x->sz = 1+getsz(a)+getsz(b);
    x->sum = x->val+getsum(a)+getsum(b);
    return x;
}
void tour(pt x, vi& v) { // print values of nodes, 
    if (!x) return; // inorder traversal
    prop(x); tour(x->c[0],v); v.pb(x->val); tour(x->c[1],v);
}
//not for implicit
pair<pt,pt> split(pt t, int v) { // >= v goes to the right
    if (!t) return {t,t};
    prop(t);
    if (t->val >= v) {
        auto p = split(t->c[0], v); t->c[0] = p.ss;
        return {p.ff,calc(t)};
    } else {
        auto p = split(t->c[1], v); t->c[1] = p.ff;
        return {calc(t),p.ss};
    }
}

//for implicit
pair<pt,pt> splitsz(pt t, int sz) { // sz nodes go to left used for implicit
    if (!t) return {t,t};
    prop(t);
    if (getsz(t->c[0]) >= sz) {
        auto p = splitsz(t->c[0],sz); t->c[0] = p.ss;
        return {p.ff,calc(t)};
    } else {
        auto p=splitsz(t->c[1],sz-getsz(t->c[0])-1); t->c[1]=p.ff;
        return {calc(t),p.ss};
    }
}
pt merge(pt l, pt r) { //  keys in l < keys in r
    if (!l || !r) return l?:r;
    prop(l), prop(r); pt t;
    if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
    else r->c[0] = merge(l,r->c[0]), t = r;
    return calc(t);
}

//not for implicit
// pt ins(pt x, int v,int idx) { // insert v
//     auto a = splitsz(x,idx), b = splitsz(a.ss,0);
//     return merge(a.ff,merge(new tnode(v),b.ss)); }
// pt del(pt x, int idx) { // delete v
//     auto a = splitsz(x,idx), b = splitsz(a.ss,1);
//     return merge(a.ff,b.ss); }

//for implicit
pt ins(pt x, int v,int idx) { // insert v at idx(0 based indexing)
    auto a = splitsz(x,idx);
    return merge(a.ff,merge(new tnode(v),a.ss)); }
pt del(pt x, int idx) { // delete v at idx(0 based indexing)
    auto a = splitsz(x,idx), b = splitsz(a.ss,1);
    return merge(a.ff,b.ss); }
int find_kidx(pt t,int idx){//idx is 1 based
    assert(getsz(t) >= idx);
    prop(t);
    if(getsz(t->c[0]) == idx-1)return t->val;
    else if(getsz(t->c[0]) < idx)return find_kidx(t->c[1],idx-getsz(t->c[0])-1);
    else return find_kidx(t->c[0],idx);
}

//not for implicit
int find_k(pt t,int k){//find k-th largest element in t's subtree(1-based k)
    assert(getsz(t) >= k);
    prop(t);
    if(getsz(t->c[0]) == k-1)return t->val;
    else if(getsz(t->c[0]) < k)return find_k(t->c[1],k-getsz(t->c[0])-1);
    else return find_k(t->c[0],k);
}
int find_cnt(pt t,int k){//find count of elements less than k in t's subtree
    if(!t)return 0;
    prop(t);
    if(t -> val < k)return getsz(t->c[0])+1+find_cnt(t->c[1],k);
    else return find_cnt(t->c[0],k);
}
bool pre(pt t,int k){//checks if k is present in the treap
    if(!t)return 0;
    if(t->val == k)return 1;
    prop(t);
    if(t->val<k)return pre(t->c[1],k);
    else return pre(t->c[0],k);
}