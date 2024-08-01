#ifndef Q2_H
#define Q2_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

namespace q2 {
    struct Patient {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    std::vector<Patient> read_file (const std::string& filename);
    bool cmp (const Patient& x, const Patient& y);
    void sort (std::vector<Patient>& patients);
}

inline std::vector<q2::Patient> q2::read_file (const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open this file!");
    
    std::string line;
    std::vector<q2::Patient> patients{};
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream sstream(line);
        std::string name, surname, age, smokes, area_q, alkhol;
        std::getline(sstream, name, ',');
        std::getline(sstream, surname, ',');
        std::getline(sstream, age, ',');
        std::getline(sstream, smokes, ',');
        std::getline(sstream, area_q, ',');
        std::getline(sstream, alkhol);

        if (name.back() == ' ') name.pop_back();
        patients.push_back(q2::Patient{name + " " + surname, std::stoul(age), std::stoul(smokes), std::stoul(area_q), std::stoul(alkhol)});
    }

    return patients;
}

inline bool q2::cmp (const q2::Patient& x, const q2::Patient& y) {
    return (x.age * 3 + x.smokes * 5 + x.area_q * 2 + x.alkhol * 4) > (y.age * 3 + y.smokes * 5 + y.area_q * 2 + y.alkhol * 4);
}

inline void q2::sort (std::vector<Patient>& patients) {
    std::sort(patients.begin(), patients.end(), q2::cmp);
}

#endif //Q2_H