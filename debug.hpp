#include "head.hpp"
#ifndef ONLINE_JUDGE
    #define debug(x...) cerr << "[" << #x << "]:\n", _print(x)
#else
    #define debug(...) 42
#endif
template <typename T> struct is_pair : false_type {}; template <typename T, typename U> struct is_pair<pair<T, U>> : true_type {};
template <typename T> struct is_string : false_type {}; template <> struct is_string<string> : true_type {};
template <typename T, typename = void> struct is_iterable : false_type {}; template <typename T> struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};
template <typename T> void __print(const T &x) {
    if constexpr (is_string<T>::value) cerr << '\"' << x << '\"';
    else if constexpr (is_pair<T>::value) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; } 
    else if constexpr (is_iterable<T>::value) { cerr << '{'; int f = 0; for (auto &i : x) { cerr << (f++ ? "," : ""); __print(i); } cerr << "}"; } 
    else cerr << x;
}
inline void _print() { cerr << "\n" << endl; }
template <typename T, typename... V>
void _print(T t, V... v) {
    __print(t);
    if (sizeof...(v)) cerr << ", ";
    _print(v...);
}