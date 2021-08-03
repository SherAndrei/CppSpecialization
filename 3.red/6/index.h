#pragma once

#include <array>
#include <list>
#include <string>
#include <string_view>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <functional>

using namespace std;

using HitcountType = size_t;
using DocidType = size_t;

constexpr size_t DOCUMENT_AMOUNT = 50'000;

#if 0
struct Index {
  DocidType docid;
  HitcountType hitcount = 0;

};
#endif
struct WordIndex {
  array<size_t, DOCUMENT_AMOUNT> doc_to_hitcount{};
  vector<DocidType> doc_indices;

  void Sort();
};

class InvertedIndex {
 public:
  InvertedIndex();
  void Add(string&& document);
  WordIndex Lookup(string_view word) const;

 private:
  map<string_view, WordIndex> word_to_idxs;
  vector<string> docs;
};
