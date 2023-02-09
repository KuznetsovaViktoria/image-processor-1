#include "scorer.h"
#include <map>
#include <vector>
#include <set>
#include <string>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<std::string, std::set<std::string>> ans;
    std::map<std::string, std::map<std::string, std::vector<Event>>> event_list;
    std::vector<std::string> people;
    std::vector<std::string> tasks;
    for (const Event& event : events) {
        if (event_list[event.student_name].empty()) {
            people.push_back(event.student_name);
        }
        if (event_list[event.student_name][event.task_name].empty()) {
            tasks.push_back(event.task_name);
        }
        event_list[event.student_name][event.task_name].push_back(event);
    }
    for (const std::string& person : people) {
        for (const std::string& task : tasks) {
            std::sort(event_list[person][task].begin(), event_list[person][task].end(),
                      [](const Event& a, const Event& b) -> bool { return a.time < b.time; });
            bool if_ci_success = false;
            bool if_merge_closed = true;
            for (const Event& event : event_list[person][task]) {
                if (event.time > score_time) {
                    break;
                }
                if (event.event_type == EventType::CheckFailed) {
                    if_ci_success = false;
                } else if (event.event_type == EventType::CheckSuccess) {
                    if_ci_success = true;
                } else if (event.event_type == EventType::MergeRequestOpen) {
                    if_merge_closed = false;
                } else {
                    if_merge_closed = true;
                }
            }
            if (if_ci_success && if_merge_closed) {
                ans[person].insert(task);
            }
        }
    }
    return ans;
}
