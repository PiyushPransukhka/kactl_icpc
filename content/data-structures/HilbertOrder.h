/**
 * 
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
