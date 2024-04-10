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
    int bits = 30;      // check
    array<int, 30> b;   // basis
    Basis ()
    { for (int i = 0; i < bits; i++) b[i] = 0; }
    void add (int x) {
        for (int i = bits-1; i >= 0 && x > 0; --i)
            if (b[i]) x = min(x, x ^ b[i]);
            else b[i] = x, x = 0;
    }
    void merge (const Basis &other) {
        for (int i = bits-1; i >= 0; --i) {
            if (!other.b[i]) break;
            add(other.b[i]);
        }
    }
    int getmax () {
        int ret = 0;
        for (int i = bits-1; i >= 0; --i)
            ret = max(ret, ret ^ b[i]);
        return ret;
    }
    bool isPossible (int k) const {
        for (int i = bits-1; i >= 0; --i)
            k = min(k, k ^ b[i]);
        return k == 0;
    }
};