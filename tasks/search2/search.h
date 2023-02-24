#pragma once

#include <string_view>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class SearchEngine {
public:
    void BuildIndex(std::string_view text);
    std::vector<std::string_view> Search(std::string_view query, size_t results_count) const;

private:
    double TF(std::string_view word, const std::vector<std::string_view>& line);
    std::vector<std::string_view> lines_;
    std::unordered_set<std::string_view> all_words_;
    std::vector<std::unordered_map<std::string_view, double>> tf_idf_table_;
};
