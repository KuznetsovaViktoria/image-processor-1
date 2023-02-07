#include "tests_checking.h"
#include <vector>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> ans;
    std::vector<std::string> order;
    for (auto& act : student_actions) {
        if (act.side == Side::Top) {
            order.insert(order.begin(), act.name);
        } else {
            order.push_back(act.name);
        }
    }
    for (size_t x : queries) {
        ans.push_back(order[x - 1]);
    }
    return ans;
}
