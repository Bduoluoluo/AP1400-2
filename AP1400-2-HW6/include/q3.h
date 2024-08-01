#ifndef Q3_H
#define Q3_H

#include <regex>
#include <queue>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
        size_t sum;

        bool operator< (const Flight& flight) const {
            return (this->duration + this->connection_times + this->price * 3) > (flight.duration + flight.connection_times + flight.price * 3);
        }
    };

    size_t time_conversion (const std::string& str);
    size_t times_conversion (const std::string& str);
    Flight get_flight (const std::string& str);
    std::priority_queue<Flight> gather_flights (const std::string& filename);
}

inline size_t q3::time_conversion (const std::string& str) {
    std::string patten = "(\\d+)h(\\d*)m*";
    std::regex reg(patten);
    std::smatch match;
    size_t time = 0;

    if (std::regex_match(str, match, reg)) {
        time += std::stoul(match[1]) * 60;
        if (match[2].length())
            time += std::stoul(match[2]);
    }
    return time;
}

inline size_t q3::times_conversion (const std::string& str) {
    std::string s = "";
    size_t time = 0;

    for (auto ch : str) {
        if (ch == ',') {
            time += q3::time_conversion(s);
            s = "";
        } else s.push_back(ch);
    }
    time += q3::time_conversion(s);
    return time;
}

inline q3::Flight q3::get_flight (const std::string& str) {
    std::string pattern = "\\d- flight_number:(.+) - duration:(.+) - connections:(\\d+) - connection_times:(.+) - price:(\\d+)";
    std::regex reg(pattern);
    std::smatch match;
    q3::Flight flight;

    if (std::regex_match(str, match, reg)) {
        flight.flight_number = match[1];
        flight.duration = q3::time_conversion(match[2]);
        flight.connections = std::stoul(match[3]);
        flight.connection_times = q3::times_conversion(match[4]);
        flight.price = std::stoul(match[5]);
    }
    return flight;
}

inline std::priority_queue<q3::Flight> q3::gather_flights (const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open this file!");

    std::priority_queue<q3::Flight> flights;
    std::string line;
    while (std::getline(file, line))
        flights.push(q3::get_flight(line));
    return flights;
}

#endif //Q3_H