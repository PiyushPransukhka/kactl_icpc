/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Lazy segtree
 * Time: $O(\log{N})$ per query
 * Status: tested
 */

template<typename T>
struct LazySegmentTree{
    vector<T> st;
    void assign(int n){
        st.resize(4*n+1);
    }
    ll combine(ll x,ll y){
        return x+y;         // check which opeartion is to be performed
    }
    void build(vector<ll> &v1, int v, int tl, int tr){
        if(tl==tr)    st[v].sum=v1[tl];     //  check
        else{
            int mid=((tl+tr)>>1);
            build( v1, (v<<1), tl, mid );
            build( v1, (v<<1)+1, mid+1, tr );
            st[v].sum = combine( st[(v<<1)].sum , st[(v<<1)+1].sum );
        }
    }
    void prop(int v, int tl, int tr){
        if(st[v].mark){
            st[v].sum=(tr-tl+1)*st[v].change; // check which opeartion is to be performed
            if(tl!=tr){
                st[(v<<1)].change=st[(v<<1)+1].change=st[v].change;
                st[(v<<1)].mark=st[(v<<1)+1].mark=1;
                st[(v<<1)].lazy=st[(v<<1)+1].lazy=0;
            }
            st[v].change=st[v].mark=0;
        }
        if(st[v].lazy!=0){
            st[v].sum+=(tr-tl+1)*st[v].lazy; // check which opeartion is to be performed
            if(tl!=tr){
                st[(v<<1)].lazy+=st[v].lazy;
                st[(v<<1)+1].lazy+=st[v].lazy;   
            }
            st[v].lazy=0;
// if st[v].lazy is != 0 at any point, it means from that vertex onwards we have to make updations
        }
    }
    ll query(int v, int tl, int tr, int l, int r){
        if(tr<l || r<tl) return 0;   // check which opeartion is to be performed
        prop(v,tl,tr);
        if(l<=tl && tr<=r)  return st[v].sum;
        int mid=((tl+tr)>>1);
        return combine( query((v<<1),tl,mid,l,min(r,mid)), query((v<<1)+1,mid+1,tr,max(l,mid+1),r) );
    }
    void update_many(int v, int tl, int tr, int l, int r, ll newVal){
        prop(v,tl,tr);    
        if(tr<l || r<tl)    return;
        if(l==tl && r==tr){
            st[v].lazy+=newVal;
            prop(v,tl,tr);
            return;
        }else{
            int mid=((tl+tr)>>1);
            update_many( (v<<1), tl, mid, l, min(r,mid), newVal);
            update_many( (v<<1)+1, mid+1, tr, max(l,mid+1), r, newVal);
            st[v].sum = combine( st[(v<<1)].sum, st[(v<<1)+1].sum );
        }
    }
    void change_many(int v, int tl, int tr, int l, int r, ll newVal){
        prop(v,tl,tr);
        if(tr<l || r<tl)    return;
        if(l==tl && r==tr){
            st[v].lazy=0,st[v].mark=1,st[v].change=newVal;
            prop(v,tl,tr);
            return;
        }else{
            int mid=((tl+tr)>>1);
            change_many( (v<<1), tl, mid, l, min(r,mid), newVal);
            change_many( (v<<1)+1, mid+1, tr, max(l,mid+1), r, newVal);
            st[v].sum = combine( st[(v<<1)].sum, st[(v<<1)+1].sum );
        }
    }
};
 
struct Node{
    ll sum,lazy,change;
    bool mark;
};
LazySegmentTree<Node> lazyseg;