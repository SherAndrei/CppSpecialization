#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <random>

#include "profile.h"
#include "test_runner.h"

using namespace std;

class ReadingManager {
 public:
    ReadingManager()
        : lagging_people(MAX_PAGE_COUNT + 1) {}

    void Read(int id, int page) {
        if (users.count(id)) {
            const int last = users[id];
            users[id] = page;

            for (int i = last + 1; i <= page; ++i) {
                lagging_people[i]--;
            }
        } else {
            users[id] = page;
            for (int i = page + 1; i <= MAX_PAGE_COUNT; ++i) {
                lagging_people[i]++;
            }
        }
    }
    double Cheer(int id) {
        if (!users.count(id))
            return 0.0;

        return (users.size() == 1u)
            ? 1.0
            : lagging_people[users[id]] * 1. / (users.size() - 1);
    }

 private:
    static constexpr int MAX_PAGE_COUNT = 1'000;

    map<int, int> users;
    vector<int> lagging_people;
};

#if TEST

void TestReadPage() {
    {
        ReadingManager m;
        m.Read(1, 1);
        m.Read(2, 2);
        ASSERT_EQUAL(m.Cheer(1), 0.0);
        ASSERT_EQUAL(m.Cheer(2), 1.0);
        m.Read(5, 5);
        ASSERT_EQUAL(m.Cheer(1), 0.0);
        ASSERT_EQUAL(m.Cheer(2), 1.0 / 2.0);
        ASSERT_EQUAL(m.Cheer(5), 1.0);
        m.Read(3, 3);
        ASSERT_EQUAL(m.Cheer(1), 0.0);
        ASSERT_EQUAL(m.Cheer(2), 1.0 / 3.0);
        ASSERT_EQUAL(m.Cheer(3), 2.0 / 3.0);
        ASSERT_EQUAL(m.Cheer(5), 1.0);
        m.Read(4, 4);
        ASSERT_EQUAL(m.Cheer(1), 0.0);
        ASSERT_EQUAL(m.Cheer(2), 1.0 / 4.0);
        ASSERT_EQUAL(m.Cheer(3), 2.0 / 4.0);
        ASSERT_EQUAL(m.Cheer(4), 3.0 / 4.0);
        ASSERT_EQUAL(m.Cheer(5), 1.0);
    }
    {  // add user
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {  // add user but cheer not existed
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
    {  // read twice
        ReadingManager manager;
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {  // better than third
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
    }
    {  // better than 2 third
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {  // read zero
        ReadingManager manager;
        manager.Read(1, 0);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(2, 0);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
        manager.Read(3, 1);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
        ASSERT_EQUAL(manager.Cheer(3), 1.0);
        manager.Read(4, 2);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
    }
    {  // all read the same
        ReadingManager manager;
        manager.Read(1, 5);
        manager.Read(2, 5);
        manager.Read(3, 5);
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
    }
    {  // reverse order
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(2, 3);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {  // two users read two times
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(4, 6);
        manager.Read(3, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        manager.Read(10, 2);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
    }
    {  // only one user
        ReadingManager manager;
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 6);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 100);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        ASSERT_EQUAL(manager.Cheer(5), 0.0);
    }
    {  // ten users
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        manager.Read(4, 4);
        manager.Read(5, 5);
        manager.Read(6, 6);
        manager.Read(7, 7);
        manager.Read(8, 8);
        manager.Read(9, 9);
        manager.Read(100, 10);
        manager.Read(111, 11);

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.1);
        ASSERT_EQUAL(manager.Cheer(3), 0.2);
        ASSERT_EQUAL(manager.Cheer(4), 0.3);
        ASSERT_EQUAL(manager.Cheer(5), 0.4);
        ASSERT_EQUAL(manager.Cheer(6), 0.5);
        ASSERT_EQUAL(manager.Cheer(7), 0.6);
        ASSERT_EQUAL(manager.Cheer(8), 0.7);
        ASSERT_EQUAL(manager.Cheer(9), 0.8);
        ASSERT_EQUAL(manager.Cheer(100), 0.9);
        ASSERT_EQUAL(manager.Cheer(111), 1.0);
        ASSERT_EQUAL(manager.Cheer(12), 0.0);
    }
    {  // cheer twice
        ReadingManager manager;

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);

        ASSERT_EQUAL(manager.Cheer(2), 0);
    }
    {  // max ID
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {  // max page
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1000);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {  // max ID and max page
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1000);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {  // zero ID
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(0), 0.0);
        manager.Read(0, 1000);
        ASSERT_EQUAL(manager.Cheer(0), 1.0);
    }
    {
    // from coursera (https://www.coursera.org/learn/c-plus-plus-red/programming/e72ST/eliektronnaia-knigha/discussions/threads/hLK3cT0AEemHtRKqiMW_lA)
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(1, 3);
        manager.Read(2, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
}

void TestSpeed() {
    // Q < 10^6
    // ID < 10^5
    // page_num < 10^3
    mt19937 gen;
    uniform_int_distribution<> id(0, 100'000);
    uniform_int_distribution<> num(0, 1000);
    {
        ReadingManager r;
        {
            LOG_DURATION("Read");

            for (size_t q = 0; q < 100'000; ++q) {
                auto a = id(gen);
                auto b = num(gen);
                r.Read(a, b);
            }
        }
        {
            LOG_DURATION("Cheer");

            for (size_t q = 0; q < 1'000'000; ++q) {
                auto c = id(gen);
                r.Cheer(c);
            }
        }
    }
}

#endif  // TEST

int main() {
#if TEST
    TestRunner tr;
    RUN_TEST(tr, TestReadPage);
    RUN_TEST(tr, TestSpeed);
#else
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if  (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
#endif
}
