#include "../numth/modint/modint61.hpp"
#include "../others/random/rng64.hpp"
/*-------rollinghash.hpp------*/
struct StringHash {
    using m61 = modint61;
    static m61 base1, base2;
    static vector<m61> pow1, pow2;

    vector<m61> h1, h2;

    // 初始化base
    static void init() {
        if (base1.val != 0) return; 
        base1 = m61(RNG(1000, m61::mod - 1));
        base2 = m61(RNG(1000, m61::mod - 1));
        while (base2 == base1) base2 = m61(RNG(1000, modint61::mod - 1));
        pow1 = {1};
        pow2 = {1};
    }

    // 预处理幂次, 按需扩展
    static void expand(int n) {
        if (pow1.empty()) init();
        while ((int)pow1.size() <= n) {
            pow1.push_back(pow1.back() * base1);
            pow2.push_back(pow2.back() * base2);
        }
    }

    StringHash() {}

    // O(|s|)
    StringHash(const string& s) {
        int n = s.size();
        expand(n);
        h1.resize(n + 1);
        h2.resize(n + 1);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = h1[i] * base1 + s[i];
            h2[i + 1] = h2[i] * base2 + s[i];
        }
    }

    // 查询子串 s[l...r-1] 的哈希值 (左闭右开)
    // 返回 pair<u64, u64>
    pair<u64, u64> query(int l, int r) const {
        // H[l...r-1] = H[r] - H[l] * B^(r-l)
        m61 res1 = h1[r] - h1[l] * pow1[r - l];
        m61 res2 = h2[r] - h2[l] * pow2[r - l];
        return {res1.val, res2.val};
    }
    
    // 合并两个 Hash 值 (对应 s1 + s2)
    // len_right: 右边子串的长度
    static pair<u64, u64> merge(pair<u64, u64> h_left, pair<u64, u64> h_right, int len_right) {
        expand(len_right);
        m61 res1 = m61(h_left.first) * pow1[len_right] + modint61(h_right.first);
        m61 res2 = m61(h_left.second) * pow2[len_right] + modint61(h_right.second);
        return {res1.val, res2.val};
    }
};

// 全局成员定义
inline modint61 StringHash::base1;
inline modint61 StringHash::base2;
inline vector<modint61> StringHash::pow1;
inline vector<modint61> StringHash::pow2;
/*---------------------------*/