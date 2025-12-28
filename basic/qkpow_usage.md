# qkpow.hpp 使用说明

## 接口概览
- 函数：
	- `template <typename T> T qkpow(T a, long long b);` 通用快速幂，适用于`matrix`, `modint`等类. 支持负指数，负指数时调用 `inv(a)`。
	- `long long qkpow(long long a, long long b, long long mod);` 最快的整数模快速幂，使用 `numth::mul` 防溢出。
- 复杂度：`O(log b)`。

## 快速上手
```cpp
#include "yklib/head.hpp"
#include "yklib/basic/qkpow.hpp"
int main(){
		long long x = qkpow(2LL, 10, 1'000'000'007); // 1024

		// 与自定义模数类型配合
		using mint = modint<998244353>;
		mint a = 3;
		mint pw = qkpow(a, 5);   // 3^5 mod 998244353
		mint inva = qkpow(a, -1); // 3^{-1}
}
```

## 注意事项
- 负指数分支依赖 `inv(a)`：
	- 对整数请使用 `qkpow(ll,ll,ll mod)` 版本（不支持负指数），或先手动求逆后再正幂。
	- 对自定义类型需实现 `inv()` 或重载 `/` 供 `inv.hpp` 使用。
- 整数版内部使用 `numth::mul` 基于 `__int128` 做乘法，避免 64 位乘法溢出；`mod` 应为正且不为 0。
- 输入底数会先取模：`a %= mod`。若 `mod == 1` 返回 0。
- `head.hpp` 已开启快速 I/O，同一程序无需重复设置。
