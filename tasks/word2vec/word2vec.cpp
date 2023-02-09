#include "word2vec.h"
#include <string>
#include <vector>

int64_t CountProduct(const std::vector<int>& a, const std::vector<int>& b) {
    int64_t res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        res += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return res;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (words.size() <= 1) {
        return {};
    }
    std::vector<std::string> ans;
    int64_t mx = CountProduct(vectors[0], vectors[1]);
    for (size_t i = 2; i < words.size(); ++i) {
        int64_t cnt = CountProduct(vectors[0], vectors[i]);
        if (cnt > mx) {
            mx = cnt;
            ans = {words[i]};
        } else if (cnt == mx) {
            ans.push_back(words[i]);
        }
    }
    return ans;
}
