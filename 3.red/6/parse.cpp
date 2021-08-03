#include "parse.h"

void LeftStrip(string_view& sv) {
  while (!sv.empty() && isspace(sv.front())) {
    sv.remove_prefix(1);
  }
}

string_view Strip(string_view s) {
  LeftStrip(s);
  while (!s.empty() && isspace(s.back())) {
    s.remove_suffix(1);
  }
  return s;
}

string_view ReadToken(string_view& sv) {
  LeftStrip(sv);

  auto pos = sv.find(' ');
  auto result = sv.substr(0, pos);
  sv.remove_prefix(pos != sv.npos ? pos : sv.size());
  return result;
}

vector<string_view> SplitIntoWords(string_view s) {
    vector<string_view> result;
    while (!s.empty()) {
        const auto token = ReadToken(s);
        if (token.empty())
            continue;
        result.push_back(token);
    }
    return result;
}

vector<string_view> SplitBy(string_view s, char sep) {
  vector<string_view> result;
  while (!s.empty()) {
    size_t pos = s.find(sep);
    result.push_back(s.substr(0, pos));
    s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
  }
  return result;
}

