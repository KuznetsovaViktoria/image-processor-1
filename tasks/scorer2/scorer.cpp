#include "scorer.h"

using StudentName = std::string;
using TaskName = std::string;
using ScoreTable = std::map<StudentName, std::set<TaskName>>;

void Scorer::OnCheckSuccess(const StudentName &student_name, const TaskName &task_name) {
    table_check_[student_name].insert(task_name);
}

void Scorer::OnCheckFailed(const StudentName &student_name, const TaskName &task_name) {
    table_check_[student_name].erase(task_name);
    if (table_check_[student_name].empty()) {
        table_check_.erase(student_name);
    }
}

void Scorer::OnMergeRequestOpen(const StudentName &student_name, const TaskName &task_name) {
    table_merge_[student_name].insert(task_name);
}

void Scorer::OnMergeRequestClosed(const StudentName &student_name, const TaskName &task_name) {
    table_merge_[student_name].erase(task_name);
    if (table_merge_[student_name].empty()) {
        table_merge_.erase(student_name);
    }
}

void Scorer::Reset() {
    table_check_ = {};
    table_merge_ = {};
}

ScoreTable Scorer::GetScoreTable() const {
    ScoreTable ans;
    for (auto const &[student, problems] : table_check_) {
        for (auto &task : problems) {
            if (!table_merge_.contains(student) ||
                table_merge_.at(student).find(task) == table_merge_.at(student).end()) {
                ans[student].insert(task);
            }
        }
    }
    return ans;
}