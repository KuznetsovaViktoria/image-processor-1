#include "sort_students.h"

#include <algorithm>

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) -> bool {
            return std::tie(a.birth_date.year, a.birth_date.month, a.birth_date.day, a.last_name, a.name) <
                   std::tie(b.birth_date.year, b.birth_date.month, b.birth_date.day, b.last_name, b.name);
        });
    } else {
        std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) -> bool {
            return std::tie(a.last_name, a.name, a.birth_date.year, a.birth_date.month, a.birth_date.day) <
                   std::tie(b.last_name, b.name, b.birth_date.year, b.birth_date.month, b.birth_date.day);
        });
    }
}
