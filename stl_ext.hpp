#include "head.hpp"
// vector
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (int i = 1; i < v.size(); i++) is >> v[i]; return is; }
template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) { for (int i = 1; i < v.size(); i++) { os << ((i > 1) ? " " : "") << v[i]; } return os; }

// pair
template<typename T, typename V> istream& operator>>(istream& is, pair<T, V>& p) { is >> p.first >> p.second; return is; }
template<typename T, typename V> ostream& operator<<(ostream& os, pair<T, V>& p) { os << p.first << ' ' << p.second; return os; }

