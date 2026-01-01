#include "head.hpp"
// vector
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (int i = 1; i < v.size(); i++) is >> v[i]; return is; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (int i = 1; i < v.size(); i++) { os << ((i > 1) ? " " : "") << v[i]; } return os; }

// pair
template<typename T, typename V> istream& operator>>(istream& is, pair<T, V>& p) { is >> p.first >> p.second; return is; }
template<typename T, typename V> ostream& operator<<(ostream& os, pair<T, V>& p) { os << p.first << ' ' << p.second; return os; }
template<typename T, typename V> pair<T, V> operator+=(pair<T, V> a, pair<T, V> b) { a.first += b.first; a.second += b.second; return a; }
template<typename T, typename V> pair<T, V> operator+(pair<T, V> a, pair<T, V> b) { return { a.first + b.first, a.second + b.second }; }
template<typename T, typename V, typename G> pair<T, V> operator*=(pair<T, V> a, G b) { a.first *= b; a.second *= b; return a; }
template<typename T, typename V, typename G> pair<T, V> operator*(pair<T, V> a, G b) { return { a.first * b, a.second * b }; }
template<typename T, typename V, typename G> pair<T, V> operator*(G b, pair<T, V> a) { return a * b; }
template<typename T, typename V> pair<T, V> operator-(pair<T, V> a) { return { -a.first, -a.second }; }
template<typename T, typename V> pair<T, V> operator-=(pair<T, V> a, pair<T, V> b) { a += -b; return a; }
template<typename T, typename V> pair<T, V> operator-(pair<T, V> a, pair<T, V> b) { return a + (-b); }
