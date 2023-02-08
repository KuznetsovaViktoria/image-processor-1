#include "admission.h"
#include <string>
#include <vector>
#include <unordered_map>

AdmissionTable FillUniversities(const std::vector<University> &universities, const std::vector<Applicant> &applicants) {
    std::vector <const Applicant*> sorted_applicants;
    for (const auto& person : applicants){
        sorted_applicants.push_back(&person);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), [](const Applicant* a, const Applicant* b) -> bool {
        const int minus_a_points = -a->points;
        const int minus_b_points = -b->points;
        return std::tie(minus_a_points, a->student.birth_date.year, a->student.birth_date.month, a->student.birth_date.day,
                        a->student.name) < std::tie(minus_b_points, b->student.birth_date.year,
                                                   b->student.birth_date.month, b->student.birth_date.day,
                                                   b->student.name);
    });
    std::unordered_map<std::string, size_t> universities_map;
    for (const auto &uni : universities) {
        universities_map[uni.name] = uni.max_students;
    }
    AdmissionTable ans;
    for (const auto *person : sorted_applicants) {
        for (const auto &uni : person->wish_list) {
            if (ans[uni].size() < universities_map[uni]) {
                ans[uni].push_back(&person->student);
                break;
            }
        }
    }
    for (auto &uni : ans) {
        std::sort(uni.second.begin(), uni.second.end(),
                  [](const Student *a, const Student *b) -> bool { return a->name < b->name; });
    }
    return ans;
}
