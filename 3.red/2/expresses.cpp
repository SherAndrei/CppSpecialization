#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

#include <random>

using namespace std;

// Q 10^5
// numbrers 10^9

class RouteManager {
 public:
  // LogN
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish);
    reachable_lists_[finish].insert(start);
  }

  void PrintRoutes(ostream& os) const {
      for (const auto& [start, finishes] : reachable_lists_) {
          os << start << ": ";
          for (auto it = finishes.begin(); it != finishes.end(); ++it)
              os << *it << (it == prev(finishes.end()) ? '\n' : ' ');
      }
  }
  size_t Size() const {
      return reachable_lists_.size();
  }

  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish);
    // LogQ
    if (reachable_lists_.count(start) < 1)
        return result;

    const set<int>& reachable_stations = reachable_lists_.at(start);
    const auto finish_pos = reachable_stations.lower_bound(finish);
    if (finish_pos != end(reachable_stations)) {
        result = min(result, abs(finish - *finish_pos));
    }
    if (finish_pos != begin(reachable_stations)) {
        result = min(result, abs(finish - *prev(finish_pos)));
    }
    return result;
  }

 private:
  map<int, set<int>> reachable_lists_;
};
/*
void TestGo() {
   {
       RouteManager r;
       r.AddRoute(2, 5);
       r.AddRoute(10, 4);
       r.AddRoute(5, 8);

       ASSERT_EQUAL(r.FindNearestFinish(4, 10), 0);
       ASSERT_EQUAL(r.FindNearestFinish(4, -2), 6);
       ASSERT_EQUAL(r.FindNearestFinish(5, 0), 2);
       ASSERT_EQUAL(r.FindNearestFinish(5, 100), 92);
   }
   {
       RouteManager r;
       r.AddRoute(-100, -1);
       r.AddRoute(1, 100);

       ASSERT_EQUAL(r.FindNearestFinish(-100, 0), 1);
       ASSERT_EQUAL(r.FindNearestFinish(0, -100), 100);

       ASSERT_EQUAL(r.FindNearestFinish(-100, 100), 101);
       ASSERT_EQUAL(r.FindNearestFinish(100, -100), 101);

       ASSERT_EQUAL(r.FindNearestFinish(-50, 100), 150);
       ASSERT_EQUAL(r.FindNearestFinish(100, -50), 51);

       ASSERT_EQUAL(r.FindNearestFinish(50, 0), 50);
       ASSERT_EQUAL(r.FindNearestFinish(0, 50), 50);

       ASSERT_EQUAL(r.FindNearestFinish(3, 100), 97);
       ASSERT_EQUAL(r.FindNearestFinish(100, 3), 2);

       r.AddRoute(-100, -50);
       ASSERT_EQUAL(r.FindNearestFinish(-100, 0), 1);
       ASSERT_EQUAL(r.FindNearestFinish(0, -100), 100);

       r.AddRoute(-50, 50);
       ASSERT_EQUAL(r.FindNearestFinish(-50, 100), 50);
       ASSERT_EQUAL(r.FindNearestFinish(100, -50), 51);

       r.AddRoute(-100, 100);
       ASSERT_EQUAL(r.FindNearestFinish(-100, 100), 0);
       ASSERT_EQUAL(r.FindNearestFinish(100, -100), 0);
   }
}
void TestAdd() {
   {
       RouteManager r;
       for (int i = 1; i < 11; ++i)
           r.AddRoute(0, i);

       ostringstream lhs;
       r.PrintRoutes(lhs);

       ostringstream rhs;
    
       rhs << 0 << ": ";
       for (int i = 1; i < 11; ++i)
           rhs << i << (i == 10 ? '\n' : ' ');
       for (int j = 1; j < 11; ++j)
           rhs << j << ": " << 0 << '\n';

       ASSERT_EQUAL(lhs.str(), rhs.str());
   }
   {
       RouteManager r;
       for (int i = 1; i < 11; ++i)
           r.AddRoute(11 - i, i);

       for (int i = 1; i < 11; ++i)
           r.AddRoute(i, 11 - i);

       ostringstream lhs;
       r.PrintRoutes(lhs);

       ostringstream rhs;
       for (int i = 1; i < 11; ++i) {
           rhs << i << ": ";
           rhs << (11 - i) << '\n';
       }

       ASSERT_EQUAL(lhs.str(), rhs.str());
   }
   {
       RouteManager r;
       for (int i = 1; i < 11; ++i)
           r.AddRoute(0, i);
       ASSERT_EQUAL(r.Size(), 11u);

       for (int i = 1; i < 11; ++i)
           r.AddRoute(i, 0);
       ASSERT_EQUAL(r.Size(), 11u);
   }
}

void TestSpeed() {
   RouteManager r;
   mt19937 gen;
   uniform_int_distribution<> unif (-1000'000'000, 1000'000'000);

   {
       LOG_DURATION("ADD");
       for (size_t q = 0; q < 100'000; ++q) {
           auto a = unif (gen);
           r.AddRoute(a, -a);
       }
   }
   {
       int goes;
       LOG_DURATION("GO");
       for (size_t q = 0; q < 100'000; ++q) {
           auto a = unif (gen);
           goes = r.FindNearestFinish(- a, a);
       }
   }
   {
       LOG_DURATION("ADD and GO");
       int goes;
       for (size_t q = 0; q < 1'000'000; ++q) {
           auto a = unif (gen);
           if (q % 2 == 0) {
               r.AddRoute(a, -a);
           } else {
               auto b = unif (gen);
               goes = r.FindNearestFinish(-b, b);
           }
       }
   }
}
*/

int main() {
  RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  }

  return 0;
}
