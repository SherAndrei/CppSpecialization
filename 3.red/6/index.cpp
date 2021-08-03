#include "index.h"

#include <algorithm>
#include <utility>

#include "parse.h"

void WordIndex::Sort() {
    sort(doc_indices.begin(), doc_indices.end(),
    [counts = &doc_to_hitcount] (const DocidType& lhs, const DocidType& rhs) {
        const auto lhs_docid = static_cast<int64_t>(lhs);
        const auto rhs_docid = static_cast<int64_t>(rhs);
        return make_pair(counts[lhs], -lhs_docid) > make_pair(counts[rhs], -rhs_docid);
    });
}

InvertedIndex::InvertedIndex() {
  docs.reserve(DOCUMENT_AMOUNT);
}

void InvertedIndex::Add(string&& document) {
  const auto& doc = docs.emplace_back(move(document));
  const auto current_id = docs.size() - 1;
  for (const auto& word : SplitIntoWords(doc)) {
    auto& idx = word_to_idxs[word];
    auto& hitcount = idx.doc_to_hitcount[current_id];
    if (hitcount == 0)
        idx.doc_indices.push_back(current_id);
    hitcount++;
  }
}

WordIndex InvertedIndex::Lookup(string_view word) const {
    if (auto it = word_to_idxs.find(word); it != word_to_idxs.end())
        return it->second;
    return {};
}
