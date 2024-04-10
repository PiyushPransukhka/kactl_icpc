/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Gauss elimination
 * Status: tested
 */

#pragma once

template<typename T>
int gauss (vector < vector<T> > a, vector<T> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
 
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i){
            if ((a[i][col].val) > (a[sel][col].val))sel = i;
        }
        if ((a[sel][col]) == 0)continue;  // In case of T = double, change it to if(abs(a[sel][col]) < eps) where eps  = 1e-9.
        for (int i=col; i<=m; ++i){
            swap (a[sel][i], a[row][i]);
        }
        where[col] = row;
 
        for (int i=0; i<n; ++i){
            if (i != row) {
                T c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j){
                    a[i][j] -= a[row][j] * c;
                }
            }
        }    
        ++row;
    }
    for (int i=0; i<m; ++i){
        if (where[i] != -1)ans[i] = a[where[i]][m] / a[where[i]][i];
    }
    for (int i=0; i<n; ++i) {
        T sum = 0;
        for (int j=0; j<m; ++j)sum += ans[j] * a[i][j];
        if ((sum - a[i][m])  != 0 )return 0;  // No solution
    }
 
    for (int i=0; i<m; ++i){
        if (where[i] == -1)return 2;  // infinite solutions
    }    
    return 1; // unique solution
}