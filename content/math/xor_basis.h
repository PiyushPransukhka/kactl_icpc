/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: XOR basis
 * Status: tested
 */

#pragma once


// check int or long long int

struct Basis {
    int bits = 30; // check
    array<int, 30> basis;  // check
 
    Basis(){
      for(int i=0;i<bits;i++){
          basis[i]=0;
      }
    }
 
    void add(int x) {
        for (int i = bits-1; i >= 0 && x > 0; --i) {
            if (basis[i]) x = min(x, x ^ basis[i]);
            else {basis[i] = x; x = 0;}
        }
    }
    void merge(const Basis &other) {
        for (int i = bits-1; i >= 0; --i) {
            if (!other.basis[i]) break;
            add(other.basis[i]);
        }
    }
    int getmax() {
        int ret = 0;
        for (int i = bits-1; i >= 0; --i) {
            ret = max(ret, ret ^ basis[i]);
        }
        return ret;
    }
    bool isPossible(int k) const {
        for (int i = bits-1; i >= 0; --i) {
            k = min(k, k ^ basis[i]);
        }
        return k == 0;
    }
};