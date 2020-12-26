#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

template<typename T> T Sqr(const T& item);
template<typename First, typename Second> pair<First, Second> Sqr(pair<First, Second>& p);
template<typename T> vector<T> Sqr(vector<T> vec);
template<typename First, typename Second> map<First, Second> Sqr(map<First, Second> m);

template<typename T>
T Sqr(const T& item) {
    return item * item;
}

template<typename First, typename Second>
pair<First, Second> Sqr(pair<First, Second>& p) {
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template<typename T>
vector<T> Sqr(vector<T> vec) {
    for (T& item : vec)
        item = Sqr(item);

    return vec;
}

template<typename First, typename Second>
map<First, Second> Sqr(map<First, Second> m) {
    for (auto& [key, value] : m)
        value = Sqr(value);

    return m;
}

int main() {
    vector<int> v = { 1, 2, 3 };

    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    pair<const int, pair<const int, int>> p = { 1, {10, 20} };

    cout << Sqr(p).first << " " << Sqr(p).second.first << " " << Sqr(p).second.second << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };

    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}

/*
template<typename T>
vector<T> Sqr(const vector<T>& value) {
  vector<T> result;
  for (const T& x : value) {
    // Здесь важно, что вместо x * x вызывается функция Sqr:
    // это позволяет возводить в квадрат составные объекты
    result.push_back(Sqr(x));
  }

  return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value) {
  map<K, V> result;
  for (const auto& element : value) {
    result[element.first] = Sqr(element.second);
  }
  return result;
}

template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value) {
  return {Sqr(value.first), Sqr(value.second)};

}
*/
