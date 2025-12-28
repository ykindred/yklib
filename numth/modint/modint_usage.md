# modint.hpp 使用说明

## 接口概览
- 类型：`modint<MOD>` 固定模整数类，要求 `0 < MOD < 2^31`。
- 静态成员：`modint::raw(u32 v)` 可快速构造mint字面量。
- 构造：支持所有整数类型，默认取模并保证非负。
- 访问：`val` 为当前值（`u32`）。
- 算术：重载了加减乘除和负号等；除法和逆要求被除数非零且与模互质(否则不存在逆元)。
- 幂：`qkpow(ll n)`，支持负指数，负指数会调用 `inv()`。
- 逆元：`inv()` 使用扩展欧几里得算法.
- 取反与比较：`operator-()`、`== != <`, 直接比较字面大小；流式读写 `>> <<`。

## 使用示例
```cpp
#include "yklib/head.hpp"
#include "yklib/numth/modint/modint.hpp"

int main() {
	mint998 a = 3, b = 5;
	mint998 c = a + b;        // 8
	mint998 d = a * b;        // 15
	mint998 p = a.qkpow(10);  // 幂
	mint998 inva = a.inv();   // 逆元（模需与 a 互质且非零）
	mint998 neg = -a;         // 取反

	// 负幂：qkpow(-n) = 1 / a.qkpow(n)
	mint998 one = a.qkpow(-1) * a; // 1

	// 流式 IO
    cin >> a >> b;
    cout << a << ' ' << b;

	// 重载了小于号, 可以直接排序/比较.
	vector<mint998> v = {b, a, mint998::raw(1)};
	sort(v.begin(), v.end());
}
```

## 注意事项
- 逆元/除法安全性：`inv()` 与 `operator/` 会 `assert(val != 0 && gcd(val, mod) == 1)`；非互质或 0 会触发断言。
- 负幂同样依赖 `inv()`，对 0 或非互质值会断言。
- 非质数模可用，但仅对与模互质的值可求逆；否则断言失败。
- 构造重载较多，如遇歧义可显式转换（如 `mint998((ll)x)`）。
- `umod` 受限于 `2^31`，适合 32 位以下模数；需要 64 位模数请使用 dynamic64/modint61。

## 常见片段
- 组合运算：
```cpp
mint s = 0;
for (int x : arr) s += mint(x);
```

- 模幂与逆元：
```cpp
mint base = 7;
mint pw = base.qkpow(1'000'000);
mint invb = base.inv();
```