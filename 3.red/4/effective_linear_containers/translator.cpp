#include <string>
#include <string_view>
#include <map>
#include <set>
#include <vector>

#include "test_runner.h"

class Translator {
 public:
    void Add(std::string_view source, std::string_view target) {
        auto [source_it, source_success] = _words.emplace(std::string(source));
        auto [target_it, target_success] = _words.emplace(std::string(target));
        _translate_forward[*source_it] = *target_it;
        _translate_backward[*target_it] = *source_it;
    }
    std::string_view TranslateForward(std::string_view source) const {
        return TranslateImpl(_translate_forward, source);
    }
    std::string_view TranslateBackward(std::string_view target) const {
        return TranslateImpl(_translate_backward, target);
    }

 private:
    std::string_view TranslateImpl(
        const std::map<std::string_view, std::string_view>& dict,
        std::string_view word) const {
        if (!dict.count(word))
            return {};
        return dict.at(word);
    }

 private:
    std::set<std::string> _words;
    std::map<std::string_view, std::string_view> _translate_forward;
    std::map<std::string_view, std::string_view> _translate_backward;
};

void TestSimple() {
  Translator translator;
  translator.Add(std::string("okno"), std::string("window"));
  translator.Add(std::string("stol"), std::string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
