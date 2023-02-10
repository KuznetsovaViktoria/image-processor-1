#include "scorer.h"
#include <map>
#include <vector>
#include <set>
#include <string>
#include <unordered_set>

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    std::map<std::string, std::set<std::string>> ans;
    using Timeline = std::vector<std::pair<const time_t*, const EventType*>>;
    std::map<std::string, std::map<std::string, Timeline>> event_list;
    std::unordered_set<std::string> people;
    std::unordered_set<std::string> tasks;
    for (const Event& event : events) {
        people.insert(event.student_name);
        tasks.insert(event.task_name);
        if (event.time <= score_time) {
            const time_t* event_time = &event.time;
            const EventType* event_type = &event.event_type;
            event_list[event.student_name][event.task_name].push_back(std::make_pair(event_time, event_type));
        }
    }
    for (const std::string& person : people) {
        for (const std::string& task : tasks) {
            bool if_last_ci_success = false;
            time_t time_last_ci = 0;
            bool if_merge_closed = true;
            time_t time_last_merge = 0;
            for (const std::pair<const time_t*, const EventType*>& event : event_list[person][task]) {
                if (*event.second == EventType::CheckSuccess && *event.first >= time_last_ci) {
                    if_last_ci_success = true;
                    time_last_ci = *event.first;
                } else if (*event.second == EventType::CheckFailed && *event.first >= time_last_ci) {
                    if_last_ci_success = false;
                    time_last_ci = *event.first;
                } else if (*event.second == EventType::MergeRequestClosed && *event.first >= time_last_merge) {
                    if_merge_closed = true;
                    time_last_merge = *event.first;
                } else if (*event.second == EventType::MergeRequestOpen && *event.first >= time_last_merge) {
                    if_merge_closed = false;
                    time_last_merge = *event.first;
                }
            }
            if (if_last_ci_success && if_merge_closed) {
                ans[person].insert(task);
            }
        }
    }
    return ans;
}
