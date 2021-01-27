#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>

#include "profile.h"
#include "test_runner.h"

using namespace std;

class Learner {
 private:
    set<string> dict;

 public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (dict.insert(word).second)
                ++newWords;
        }
        return newWords;
    }

    vector<string> KnownWords() {
        return { dict.begin(), dict.end() };
    }
};


void TestSpeed() {
    vector<string> v;

    for (int i = 5000; i >= -5000; --i)
        v.push_back(to_string(i));
    {
        LOG_DURATION("Learning");
        Learner l;
        ASSERT_EQUAL(l.Learn(v), 10'001); {
            LOG_DURATION("Knowing");
            ASSERT_EQUAL(l.KnownWords().size(), 10'001u);
        }
    }
}

int main() {
    TestRunner t;
    RUN_TEST(t, TestSpeed);
}
