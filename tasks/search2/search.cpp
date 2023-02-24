#include "search.h"

#include <math.h>
#include <cctype>

const std::string_view CHARS = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
const double EPS = 10e-5;

bool CompareSv(const std::string_view& a, const std::string_view& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower(a[i]) != std::tolower(b[i])) {
            return false;
        }
    }
    return true;
}

std::vector<std::string_view> SplitForWords(std::string_view query) {
    std::vector<std::string_view> words;
    while (query.find_first_not_of(CHARS) == 0) {
        query.remove_prefix(1);
    }
    size_t ind = query.find_first_not_of(CHARS);
    while (ind != std::string_view::npos && ind != query.size()) {
        words.push_back(query.substr(0, ind));
        query.remove_prefix(ind + 1);
        while (query.find_first_not_of(CHARS) == 0) {
            query.remove_prefix(1);
        }
        ind = query.find_first_not_of(CHARS);
    }
    if (!query.empty()) {
        words.push_back(query);
    }
    return words;
}

std::vector<std::string_view> SplitByEnd(std::string_view text) {
    std::vector<std::string_view> vec_of_text;
    while (text.find('\n') == 0) {
        text.remove_prefix(1);
    }
    size_t ind = text.find('\n');
    while (ind != std::string_view::npos && ind != text.size()) {
        for (size_t i = 0; i < ind; ++i) {
            if (std::isalpha(text[i])) {
                vec_of_text.push_back(text.substr(0, ind));
                break;
            }
        }
        text.remove_prefix(ind + 1);
        while (text.find('\n') == 0) {
            text.remove_prefix(1);
        }
        ind = text.find('\n');
    }
    if (!text.empty()) {
        vec_of_text.push_back(text);
    }
    return vec_of_text;
}

double SearchEngine::TF(std::string_view word, const std::vector<std::string_view>& line) {
    if (line.empty()) {
        return 0;
    }
    int64_t cnt = 0;
    for (std::string_view word_in_line : line) {
        if (CompareSv(word, word_in_line)) {
            cnt += 1;
        }
    }
    return static_cast<double>(cnt) / static_cast<double>(line.size());
}

void SearchEngine::BuildIndex(std::string_view text) {
    lines_ = SplitByEnd(text);
    std::vector<std::vector<std::string_view>> words_lines;
    all_words_.clear();
    for (auto& line : lines_) {
        std::vector<std::string_view> words_in_line = SplitForWords(line);
        words_lines.push_back(words_in_line);
        for (auto& w : words_in_line) {
            all_words_.insert(w);
        }
    }
    std::unordered_map<std::string_view, size_t> idfs;
    std::vector<std::unordered_map<std::string_view, double>> tfs_table(words_lines.size());
    for (auto& word : all_words_) {
        for (size_t i = 0; i < lines_.size(); ++i) {
            double tf_now = TF(word, words_lines[i]);
            if (tf_now > 0) {
                tfs_table[i][word] = tf_now;
                ++idfs[word];
            }
        }
    }
    tf_idf_table_.clear();
    tf_idf_table_.resize(lines_.size());
    for (size_t i = 0; i < lines_.size(); ++i) {
        for (auto& word : all_words_) {
            tf_idf_table_[i][word] = tfs_table[i][word] * log(lines_.size() / idfs[word]);
        }
    }
}

bool Cmp(const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) {
    if (std::abs(a.first - b.first) < EPS) {
        return a.second < b.second;
    }
    return a.first > b.first;
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<std::string_view> q = SplitForWords(query);
    std::unordered_set<std::string_view> words(q.begin(), q.end());
    std::vector<std::pair<double, size_t>> suitable_tf_idf;
    for (size_t i = 0; i < lines_.size(); ++i) {
        double ind_total = 0;
        for (const auto& word : words) {
            for (const auto& [w, ind] : tf_idf_table_[i]) {
                if (CompareSv(word, w)) {
                    ind_total += ind;
                }
            }
        }
        if (ind_total == 0) {
            continue;
        }
        suitable_tf_idf.push_back(std::make_pair(ind_total, i));
    }
    std::stable_sort(suitable_tf_idf.begin(), suitable_tf_idf.end(), Cmp);
    std::vector<std::string_view> ans;
    for (size_t i = 0; i < std::min(suitable_tf_idf.size(), results_count); ++i) {
        ans.push_back(lines_[suitable_tf_idf[i].second]);
    }
    return ans;
}