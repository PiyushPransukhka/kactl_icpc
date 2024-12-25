/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: Use $RT = 5$ in case of 998244353 and 1000000007 and $RT = 62$ in case of any other MOD.
 * Use conv for 998244353 and $conv\_general$ for any other MOD.
 * Time: O(N \log N)
 * Status: tested
 */

template<int MOD, int RT> struct mint {
    static const int mod = MOD; int v; 
    static constexpr mint rt() { return RT; } // primitive root
    explicit operator int() const { return v; } 
    mint():v(0) {}
    mint(ll _v):v(int(_v%MOD)) { v += (v<0)*MOD; }
    mint& operator+=(mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((ll)v*o.v%MOD); return *this; }
    friend mint pow(mint a, ll p) { assert(p >= 0);return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
    friend mint inv(mint a) { assert(a.v != 0); return pow(a,MOD-2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
};
using mi = mint<998244353,5>; // Check mod 
template<class T> void fft(vector<T>& A, bool invert = 0) { // NTT
    int n = A.size(); assert((T::mod-1)%n == 0); vector<T> B(n);
    for(int b = n/2; b; b /= 2, swap(A,B)) { // w = n/b'th root
        T w = pow(T::rt(),(T::mod-1)/n*b), m = 1; 
        for(int i = 0; i < n; i += b*2, m *= w) for(int j = 0;j < b;j++) {
            T u = A[i+j], v = A[i+j+b]*m;
            B[i/2+j] = u+v; B[i/2+j+n/2] = u-v;
        }
    }
    if (invert) { reverse(1+A.begin(),A.end()); 
        T z = inv(T(n)); for(auto &t : A) t *= z; }
} // for NTT-able moduli
template<class T> vector<T> conv(vector<T> A, vector<T> B) {
    if (!min(A.size(),B.size())) return {};
    int s = A.size()+B.size()-1, n = 1; for (; n < s; n *= 2);
    A.resize(n), fft(A); B.resize(n), fft(B);
    for(int i = 0;i < n;i++) A[i] *= B[i];
    fft(A,1); A.resize(s); return A;
}
template<class M, class T> vector<M> mulMod(const vector<T>& x, const vector<T>& y) {
    auto con = [](const vector<T>& v) {
        vector<M> w(v.size()); for(int i = 0;i < v.size();i++) w[i] = (int)v[i];
        return w; };
    return conv(con(x), con(y));
} // arbitrary moduli
template<class T> vector<T> conv_general(const vector<T>& A, const vector<T>& B) {
    using m0 = mint<(119<<23)+1,62>; auto c0 = mulMod<m0>(A,B);
    using m1 = mint<(5<<25)+1,  62>; auto c1 = mulMod<m1>(A,B);
    using m2 = mint<(7<<26)+1,  62>; auto c2 = mulMod<m2>(A,B);
    int n = c0.size(); vector<T> res(n); m1 r01 = inv(m1(m0::mod)); 
    m2 r02 = inv(m2(m0::mod)), r12 = inv(m2(m1::mod));
    for(int i = 0;i < n;i++) { // a=remainder mod m0::mod, b fixes it mod m1::mod
        int a = c0[i].v, b = ((c1[i]-a)*r01).v, 
            c = (((c2[i]-a)*r02-b)*r12).v;
        res[i] = (T(c)*m1::mod+b)*m0::mod+a; // c fixes m2::mod
    }
    return res;
}

// For mod M,using mi = mint<M,RT>
// vector<mi> a, b
// auto c = conv_general(a, b) 