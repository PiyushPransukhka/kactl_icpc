/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vi& a, bool inv, int mod) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				inv ? pii((v - u + mod)%mod, u) : pii(v, (u + v)%mod); // AND
				// inv ? pii(v, (u - v + mod)%mod) : pii((u + v)%mod, u); // OR /// include-line
				// pii((u + v)%mod, (u - v + mod)%mod);                   // XOR /// include-line
		}
	}
	// if (inv) for (int& x : a) x = (1LL * x * inverse(sz(a), mod))%mod; // XOR only /// include-line
}
vi conv(vi a, vi b, int mod) {
	FST(a, 0, mod); FST(b, 0, mod);
	rep(i,0,sz(a)) a[i] = (1LL*a[i]*b[i])%mod;
	FST(a, 1, mod); return a;
}
