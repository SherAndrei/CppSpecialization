#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <algorithm>

#include "profile.h"
#include "test_runner.h"

using namespace std;

// Q 10^5
// time −10^18 до 10^18
// hotel_name 12 chars
// client_id 10^9
// room_count 10^3

class BookingManager {
 public:
    void Book(int64_t time, const string& hotel_name, size_t client_id, uint16_t room_count) {
        last_time = time;
        auto& current_hotel   = hotels[hotel_name];
        UpdateHotel(hotel_name);
        current_hotel.clients.insert(client_id);
        current_hotel.rooms += room_count;
        current_hotel.reservations.push({time, client_id, room_count});
    }

    size_t Clients(const string& hotel_name) {
        UpdateHotel(hotel_name);
        return hotels[hotel_name].clients.size();
    }
    size_t Rooms(const string& hotel_name) {
        UpdateHotel(hotel_name);
        return hotels[hotel_name].rooms;
    }

 private:
    struct Reservation {
        Reservation(int64_t _time, size_t _client_id, uint16_t _room_count)
            : time(_time), client_id(_client_id), room_count(_room_count) {}

        const int64_t  time;
        const size_t   client_id;
        const uint16_t room_count;
    };


    struct Data {
        size_t               rooms = 0;
        set<size_t>           clients;
        queue<Reservation> reservations;
    };


    void UpdateHotel(const string& hotel_name) {
        auto& current_hotel = hotels[hotel_name];
        while (!current_hotel.reservations.empty() &&
               !IsLastDay(current_hotel.reservations.front().time)) {
            current_hotel.rooms -= current_hotel.reservations.front().room_count;
            current_hotel.clients.erase(current_hotel.reservations.front().client_id);
            current_hotel.reservations.pop();
        }
    }
    bool IsLastDay(int64_t another) {
        return (last_time - ONE_DAY < another) && (another <= last_time);
    }
    static const int64_t ONE_DAY = 86400;

 private:
    map<string, Data> hotels;
    int64_t last_time = 0;
};

void TestCoursera() {
    {
        BookingManager manager;
        ASSERT_EQUAL(manager.Clients("Marriott"), 0u);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 0u);
        manager.Book(10, "FourSeasons", 1, 2);
        manager.Book(10, "Marriott", 1, 1);
        manager.Book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 2u);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3u);
        ASSERT_EQUAL(manager.Clients("Marriott"), 1u);
        manager.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1u);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 10u);
    }
    // unique
    {
        BookingManager b;
        b.Book(0, "a", 0, 1);
        b.Book(1, "a", 1, 2);
        b.Book(86400, "a", 1, 3);
        ASSERT_EQUAL(b.Clients("a"), 1);
        ASSERT_EQUAL(b.Rooms("a"), 5);
    }
    {
        BookingManager b;
        b.Book(1, "a", 1, 2);
        b.Book(100'000, "a", 1, 1);
        ASSERT_EQUAL(b.Clients("a"), 1);
        ASSERT_EQUAL(b.Rooms("a"), 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // TestRunner t;
    // RUN_TEST(t, TestCoursera);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            size_t client_id;
            uint16_t room_count;

            cin >> time >> hotel_name >> client_id >> room_count;
            manager.Book(time, hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Clients(hotel_name) << "\n";
        } else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << manager.Rooms(hotel_name) << '\n';
        }
    }

    return 0;
}
