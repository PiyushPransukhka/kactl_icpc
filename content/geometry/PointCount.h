/**
 * Author: archit
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: include Point.h 
 * Time: 
 * Status: tested
 */

ll operator^(P r) const { return ll(x) * ll(r.y) - ll(y) * ll(r.x); }
static bool compareYX(P a, P b){ return a.y < b.y || (!(b.y < a.y) && a.x < b.x); }
static bool compareXY(P a, P b){ return a.x < b.x || (!(b.x < a.x) && a.y < b.y); }
typedef Point <ll> Vec;
using i64 = long long;
#define rep(i,n) for(int i=0; i<(int)(n); i++)

auto pointL = vector<int>(N); // bx < Ax
auto pointM = vector<int>(N); // bx = Ax
rep(i,N) rep(j,M) if(A[i].y == B[j].y){
    if(B[j].x < A[i].x) pointL[i]++;
    if(B[j].x == A[i].x) pointM[i]++;
}
auto edgeL = vector<vector<int>>(N, vector<int>(N)); // bx < lerp(Ax, Bx)
auto edgeM = vector<vector<int>>(N, vector<int>(N)); // bx = lerp(Ax, Bx)
rep(a,N){
    struct PointId { int i; int c; Vec v; };
    vector<PointId> points;
    rep(b,N) if(A[a].y < A[b].y) points.push_back({ b, 0, A[b] - A[a] });
    rep(b,M) if(A[a].y < B[b].y) points.push_back({ b, 1, B[b] - A[a] });
    rep(b,N) if(A[a].y < A[b].y) points.push_back({ b, 2, A[b] - A[a] });
    sort(points.begin(), points.end(), [&](const PointId& l, const PointId& r){
        i64 det = l.v ^ r.v;
        if(det != 0) return det < 0;
        return l.c < r.c;
    });
    int qN = points.size();
    vector<int> queryOrd(qN); rep(i,qN) queryOrd[i] = i;
    sort(queryOrd.begin(), queryOrd.end(), [&](int l, int r){
        return make_pair(points[l].v.y, points[l].c%2) < make_pair(points[r].v.y, points[r].c%2);
    });
    vector<int> BIT(qN);
    for(int qi=0; qi<qN; qi++){
        int q = queryOrd[qi];
        if(points[q].c == 0){
            int buf = 0;
            int p = q+1;
            while(p > 0){ buf += BIT[p-1]; p -= p & -p; }
            edgeL[a][points[q].i] = buf;
        } else if(points[q].c == 1) {
            int p = q+1;
            while(p <= qN){ BIT[p-1]++; p += p & -p; }
        } else {
            int buf = 0;
            int p = q+1;
            while(p > 0){ buf += BIT[p-1]; p -= p & -p; }
            edgeM[a][points[q].i] = buf;
        }
    }
    rep(b,N) edgeM[a][b] -= edgeL[a][b];
        }