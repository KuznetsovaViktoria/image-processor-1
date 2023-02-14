#include "unixpath.h"
#include <vector>

std::vector<std::string_view> SplitBySlash(std::string_view str) {
    std::vector<std::string_view> vec;
    while (str.starts_with('/')) {
        str.remove_prefix(1);
    }
    auto in = str.find_first_of('/');
    while (in != std::string_view::npos && in != str.size()) {
        vec.push_back(str.substr(0, in));
        str.remove_prefix(in + 1);
        while (str.starts_with('/')) {
            str.remove_prefix(1);
        }
        in = str.find_first_of('/');
    }
    if (!str.empty()) {
        vec.push_back(str);
    }
    return vec;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string_view> path_vec = SplitBySlash(path);
    if (!path.starts_with('/')) {
        std::vector<std::string_view> cur_dir_vec = SplitBySlash(current_working_dir);
        cur_dir_vec.insert(cur_dir_vec.end(), path_vec.begin(), path_vec.end());
        path_vec = cur_dir_vec;
    }
    std::string ans;
    size_t flag = 0;
    for (std::vector<std::string_view>::reverse_iterator it = path_vec.rbegin(); it != path_vec.rend(); ++it) {
        if (*it == ".") {
            continue;
        }
        if (*it == "..") {
            ++flag;
            continue;
        }
        if (flag > 0) {
            --flag;
            continue;
        }
        ans = "/" + static_cast<std::string>(*it) + ans;
    }
    if (ans[0] != '/') {
        ans = "/";
    }
    return ans;
}
