#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <string>

#include "index.h"

using namespace std;

class SearchServer {
 public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

 private:
  InvertedIndex index;
};
