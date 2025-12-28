# inv.hpp 使用说明

## 接口概览
- 函数：
	- `template <typename T> T inv(T A);` 适用于`modint`, `matrix`等类，调用 `T(1) / A`，要求类型实现除法和`T(1)`幺元构造。
	- `long long inv(long long a, long long mod);` 求整数模逆，调用线性同余求解 `solve_LCE(a,1,mod)`。
- 断言/前提：整数版需 `a != 0 && gcd(a, mod) == 1` 才有逆元；模应为正数。

## 快速上手
```cpp
#include "head.hpp"
#include "inv.hpp"
int main(){
		long long a = 3, mod = 998244353;
		long long inva = inv(a, mod);           // 332748118

		// 泛型示例：假设有矩阵类型 Matrix 实现除法
		// Matrix M; Matrix Minv = inv(M);
}
```

## 注意事项
- 整数模逆底层使用扩展欧几里得解线性同余，`gcd(a, mod) != 1` 将返回 `-1`（来自 `solve_LCE`）。调用前最好先检查互质。
- 对于泛型版本，`inv(T)` 只是 `T(1) / A` 的语法糖，需确保类型实现了 `/`，且支持从整数 1 构造。
- 与 `qkpow(T,ll)` 联用时，负指数会依赖 `inv(T)`，因此需要确保 `inv()` 对目标类型可用且有意义。
- 本库的 `head.hpp` 自动设置快速 I/O；在同一程序中无需重复设置同步关闭。
