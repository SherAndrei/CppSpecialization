#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

namespace {

template<typename ContainerOfPairs>
void DumpToStream(ostream& output, string_view query, const ContainerOfPairs& c) {
    output << query << ':';
    for (const auto& [docid, hitcount] : Head(c, 5)) {
      output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    output << '\n';
}

}  // namespace

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  for (string current_query; getline(query_input, current_query); ) {
    vector<pair<size_t, size_t>> query_cont;
    for (const auto word : SplitIntoWords(current_query)) {
        auto word_idx = index.Lookup(word);
        word_idx.Sort();
        const auto range = Head(word_idx.doc_indices, 5);
        copy(range.begin(), range.end())
    }
    DumpToStream(
      search_results_output,
      current_query,
      query_cont
    );
  }
}
