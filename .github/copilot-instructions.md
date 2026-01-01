# AI Agent Instructions for yklib (C++ CP Library)

## Overview
- This repo is a header-only C++ library for competitive programming. Include targeted headers from `ds/`, `numth/`, `others/` etc. The umbrella `head.hpp` sets fast I/O and type aliases.
- GCC/Libstdc++ idioms are used widely: `<bits/stdc++.h>`, `__int128`, and PBDS (`<ext/pb_ds/...>`). Prefer `g++` on Linux.
- Modules are small, focused utilities with minimal global state. Cross-file dependencies are explicit via includes (e.g., `qkpow.hpp` → `inv.hpp` → `numth/equations.hpp`).

## Build & Test
- No build system; compile directly. Use GNU C++17+:
```bash
g++ -std=gnu++17 -O2 -pipe -Wall -Wextra -march=native test.cpp -o test
./test
```
- If you use PBDS containers (`ds/orderedset.hpp`, `ds/hashtable.hpp`), ensure `libstdc++` is available (default on Linux). Clang++ works if it uses GNU libstdc++.

## Conventions & Patterns
- Always include `head.hpp` first to enable fast I/O (`ios::sync_with_stdio(false); cin.tie(nullptr);`) and aliases like `ll`, `ull`, `INF`, `INFLL`.
- Prefer explicit templates and free functions over macros. Functions in `numth/tools.hpp` (`numth::mul`, `numth::add`) use `__int128` to avoid overflow.
- Segment/Fenwick trees are generic via function-pointer ops with identity `e()`. Example signatures mirror AtCoder-style `SegTree` APIs.
- Modular arithmetic:
  - Fixed mod: `numth/modint/modint.hpp` (`modint<MOD>`), with `qkpow(n)` and `inv(modprime=true)`.
  - Dynamic mod: `numth/modint/dynamic_modint.hpp` (`Dynamic_Modint<id>`). Call `mint::set_mod(mod)` once before use; use `pow(n)` and `inverse()`.
  - Montgomery variants are under `numth/modint/mongomery_modint.hpp` (name intentionally spelled as in file).

## Key Modules
- `ds/segtree.hpp`: `SegTree<S, op, e>` with `set(p,x)`, `get(p)`, `prod(l,r)`, `max_right(l, check)`, `min_left(r, check)`.
- `ds/fwktree.hpp`: `FwkTree<S, op, e>` with `add(p,x)`, prefix `sum(p)`, range `sum<inv>(l,r)`, `kth(k)`, and `search(check)`.
- `ds/ufset.hpp`: Union-Find with path compression + union by size; `merge(a,b)`, `same(a,b)`, `size(a)`, `count()`.
- `ds/orderedset.hpp`: PBDS-based `ordered_set<T>` and `ordered_multiset<T>` with `kth(k)` and `rank(x)` helpers.
- `ds/hashtable.hpp`: `HashMap<K,V>` / `HashSet<K>` using `gp_hash_table` and anti-hash `chash` for integers, pairs, and strings.
- `numth/tools.hpp`: Safe `mul/add` under modulus using `__int128`.
- `qkpow.hpp`: Fast exponentiation overloads: generic `qkpow(T a,ll b)` using `inv(a)` for negative exponent, and integer `qkpow(ll a,ll b,ll mod)` using `numth::mul`.
- `inv.hpp`: Generic `inv(T)` via `T(1)/A`; integer inverse via `solve_LCE(a,1,mod)`.
- `numth/equations.hpp`: Linear Diophantine (`solve_LDE`) and congruence (`solve_LCE`).
- `numth/primetest.hpp`: Deterministic Miller–Rabin under 64-bit using Montgomery modint.
- `numth/factor.hpp`: Pollard-rho (`rho`) with RNG and helpers; `factor(n)` returns prime factors with exponents.
- `others/random/rng64.hpp`: Fast 64-bit RNG helpers `RNG_64()`, `RNG(lim)`, `RNG(l,r)`.

## Usage Examples
- Dynamic modint quick start:
```cpp
#include "head.hpp"
#include "numth/modint/dynamic_modint.hpp"
using mint = Dynamic_Modint<-1>;
int main(){
  mint::set_mod(998244353);
  mint a = 3, b = 5;
  auto c = a * b;           // c.val
  auto p = a.pow(10);
  auto inva = a.inverse();  // not inv()
}
```
- Segment tree sum:
```cpp
SegTree<ll> sg(vector<ll>{1,2,3,4});
sg.set(2, 10);
auto s = sg.prod(1, 3); // [1,3) -> 2+10
```
- Fenwick range sum with inverse op:
```cpp
FwkTree<ll> fw(5);
fw.add(0, 1); fw.add(3, 7);
auto r = fw.sum<fw_default::inv_add>(0, 4); // sum [0,4)
```

## Integration Notes
- PBDS: Requires GNU extensions; avoid MSVC. Header paths already included; no extra linking flags.
- Negative exponents in `qkpow(T,ll)` call `inv(T)`. Ensure the type implements division; for integers use the `qkpow(ll,ll,ll)` overload.
- Dynamic modint exposes optional NTT info accessors (`set_ntt_info`, `can_ntt`) but are not wired to a full NTT implementation in this repo.

## Project-Specific Gotchas
- `Dynamic_Modint` uses `inverse()`, not `inv()`. Tests or new code should call `inverse()`.
- `mongomery_modint.hpp` file name is spelled "mongomery" (match exactly when including).
- `head.hpp` auto-initializes fast I/O via a static lambda; avoid redefining I/O sync settings elsewhere.

## When Adding New Code
- Keep headers small and focused; avoid hidden global state.
- Prefer `ll`/`u64` and `__int128`-based helpers for modular ops.
- Reuse existing utilities (`numth/tools.hpp`, `inv.hpp`) rather than duplicating arithmetic.

---
If any area is unclear (e.g., preferred compile flags, additional test workflow), tell me and I’ll refine these instructions to fit your usage in this repo.
