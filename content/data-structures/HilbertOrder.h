/**
 * Author: koderkushy
 * Date: 2024-04-08
 * License: CC0
 * Source: self
 * Description: Returns hilbert curve order of (x, y)
 * Status: tested
 */

#pragma once

lol hilbertorder (int x, int y) {
    lol o = 0; const int mx = 1 << 20;
    for (int p = mx; p; p >>= 1){
        bool a = x&p, b = y&p;
        o = (o << 2) | (a * 3) ^ static_cast<int>(b);
        if (!b) {
            if (a) x = mx - x, y = mx - y;
            x ^= y ^= x ^= y;
        }
    }
    return o;
}
