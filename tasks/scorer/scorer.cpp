#include "scorer.h"
#include <map>
#include <vector>
#include <set>
#include <string>

// bool operator<(const std::pair<time_t, EventType>& a, const std::pair<time_t, EventType>& b) {
//     return a.first < b.first;
// }

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<std::string, std::set<std::string>> ans;
    using Timeline = std::vector<std::pair<const time_t*, const EventType*>>;
    //    std::map<std::string, std::map<std::string, std::set<std::pair<time_t, EventType>,
    //    std::greater<std::pair<time_t, EventType>>>>>
    //        event_list;
    std::map<std::string, std::map<std::string, Timeline>> event_list;
    std::vector<std::string> people;
    std::vector<std::string> tasks;
    for (const Event& event : events) {
        if (event_list[event.student_name].empty()) {
            people.push_back(event.student_name);
        }
        if (event_list[event.student_name][event.task_name].empty()) {
            tasks.push_back(event.task_name);
        }
        if (event.time <= score_time) {
            const time_t* event_time = &event.time;
            const EventType* event_type = &event.event_type;
            event_list[event.student_name][event.task_name].push_back(std::make_pair(event_time, event_type));
        }
    }
    using TimelinePair = std::pair<const time_t*, const EventType*>;
    for (const std::string& person : people) {
        for (const std::string& task : tasks) {
            std::sort(event_list[person][task].begin(), event_list[person][task].end(),
                      [](const TimelinePair& a, const TimelinePair& b) -> bool { return *b.first < *a.first; });
            bool if_ci_success = false;
            bool if_merge_closed = false;
            //            for (auto it = event_list[person][task].begin(); event_list[person][task].end() != it; ++it) {
            for (const TimelinePair& event : event_list[person][task]) {
                if (*event.second == EventType::CheckSuccess) {
                    if_ci_success = true;
                }
                if (*event.second == EventType::CheckFailed && !if_ci_success) {
                    break;
                }
                if (*event.second == EventType::MergeRequestClosed) {
                    if_merge_closed = true;
                }
                if (*event.second == EventType::MergeRequestOpen && !if_merge_closed) {
                    break;
                }
                if (if_ci_success) {
                    ans[person].insert(task);
                    break;
                }
            }
        }
    }
    return ans;
}
