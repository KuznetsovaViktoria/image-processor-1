#include "unixpath.h"

using Path = std::vector<std::string>;

Path SplitBySlash(std::string_view s) {
    std::string_view str = static_cast<std::string_view>(s);
    Path vec;
    while (str.starts_with('/')) {
        str.remove_prefix(1);
    }
    auto in = str.find_first_of('/');
    while (in != std::string_view::npos && in != str.size()) {
        vec.push_back(static_cast<std::string>(str.substr(0, in)));
        str.remove_prefix(in + 1);
        while (str.starts_with('/')) {
            str.remove_prefix(1);
        }
        in = str.find_first_of('/');
    }
    if (!str.empty()) {
        vec.push_back(static_cast<std::string>(str));
    }
    return vec;
}

std::string NormalizeAbsolutePath(Path path_vec) {
    std::string ans;
    size_t flag = 0;
    for (Path::reverse_iterator it = path_vec.rbegin(); it != path_vec.rend(); ++it) {
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
        ans = "/" + (*it) + ans;
    }
    if (ans[0] != '/') {
        ans = "/";
    }
    return ans;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    dir_initial_ = SplitBySlash(initial_dir);
    dir_initial_ = SplitBySlash(NormalizeAbsolutePath(dir_initial_));
    dir_now_ = {"."};
    is_dir_now_absolute_ = false;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (path[0] == '/') {
        dir_now_ = SplitBySlash(path);
        is_dir_now_absolute_ = true;
        return;
    }
    Path path_vec = SplitBySlash(path);
    dir_now_.insert(dir_now_.end(), path_vec.begin(), path_vec.end());
}

std::string UnixPath::GetAbsolutePath() const {
    Path path;
    if (!is_dir_now_absolute_) {
        path = dir_initial_;
        path.insert(path.end(), dir_now_.begin(), dir_now_.end());
    } else {
        path = dir_now_;
    }
    return NormalizeAbsolutePath(path);
}

std::string UnixPath::GetRelativePath() const {
    std::string ans;
    Path combined;
    if (!is_dir_now_absolute_) {
        Path path = dir_initial_;
        path.insert(path.end(), dir_now_.begin(), dir_now_.end());
        combined = SplitBySlash(NormalizeAbsolutePath(path));
    } else {
        combined = SplitBySlash(NormalizeAbsolutePath(dir_now_));
    }

    size_t i = 0;
    while (i < dir_initial_.size() && dir_initial_[i] == combined[i]) {
        ++i;
    }
    if (i == dir_initial_.size()) {
        Path sub_dir_now(combined.begin() + static_cast<int64_t>(i), combined.end());
        std::string normilized = NormalizeAbsolutePath(sub_dir_now);
        if (normilized == "/") {
            return ".";
        }
        return "." + normilized;
    }
    for (size_t j = 1; j < dir_initial_.size() - i; ++j) {
        ans += "../";
    }
    std::string normilized = NormalizeAbsolutePath(dir_now_);
    if (normilized == "/") {
        return ans + "..";
    }
    return ans + ".." + normilized;
}