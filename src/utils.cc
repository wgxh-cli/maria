#include "includes/utils.h"
#include <map>
#include <vector>
using namespace std;

template <typename K, typename V>
vector<K> keys(map<K, V> m) {
  vector<K> res = {};
  for (const auto [key, value]: m) {
    res.push_back(key);
  }
  return res;
}
