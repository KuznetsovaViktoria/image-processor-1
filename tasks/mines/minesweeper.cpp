#include "minesweeper.h"

#include <random>
#include <algorithm>
#include <queue>

void Minesweeper::MakeSystemFields(const size_t width, const size_t height) {
    field_.resize(height);
    player_field_.resize(height);
    flag_field_.resize(height);
    std::vector<int> zeros(width, 0);
    for (size_t i = 0; i < height; ++i) {
        field_[i] = zeros;
        player_field_[i] = zeros;
        flag_field_[i] = zeros;
    }
}

void Minesweeper::CountMinesNearbyWholeField() {
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (field_[i][j] == -1) {
                if (i > 0 && field_[i - 1][j] != -1) {
                    ++field_[i - 1][j];
                }
                if (j > 0 && field_[i][j - 1] != -1) {
                    ++field_[i][j - 1];
                }
                if (i < height_ - 1 && field_[i + 1][j] != -1) {
                    ++field_[i + 1][j];
                }
                if (j < width_ - 1 && field_[i][j + 1] != -1) {
                    ++field_[i][j + 1];
                }

                if (j > 0 && i > 0 && field_[i - 1][j - 1] != -1) {
                    ++field_[i - 1][j - 1];
                }
                if (i < height_ - 1 && j > 0 && field_[i + 1][j - 1] != -1) {
                    ++field_[i + 1][j - 1];
                }
                if (j < width_ - 1 && i < height_ - 1 && field_[i + 1][j + 1] != -1) {
                    ++field_[i + 1][j + 1];
                }
                if (i > 0 && j < width_ - 1 && field_[i - 1][j + 1] != -1) {
                    ++field_[i - 1][j + 1];
                }
            }
        }
    }
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    width_ = width;
    height_ = height;
    start_ = 0;
    finish_ = 0;
    mines_count_ = mines_count;
    MakeSystemFields(width, height);
    status_ = GameStatus::NOT_STARTED;
    open_count_ = 0;
    std::vector<size_t> numbers(width * height);
    for (size_t i = 0; i < width * height; ++i) {
        numbers[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);
    for (size_t i = 0; i < mines_count; ++i) {
        size_t x = numbers[i] % width;
        size_t y = numbers[i] / width;
        field_[y][x] = -1;
    }
    CountMinesNearbyWholeField();
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    width_ = width;
    height_ = height;
    status_ = GameStatus::NOT_STARTED;
    open_count_ = 0;
    start_ = 0;
    finish_ = 0;
    mines_count_ = cells_with_mines.size();
    MakeSystemFields(width, height);
    for (const Cell& cell : cells_with_mines) {
        field_[cell.y][cell.x] = -1;
    }
    CountMinesNearbyWholeField();
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

std::vector<Minesweeper::Cell> Minesweeper::CheckWhichCellsToOpen(size_t y, size_t x) {
    std::vector<Cell> ans;
    if (field_[y][x] != 0) {
        return ans;
    }
    if (y > 0 && field_[y - 1][x] != -1 && player_field_[y - 1][x] == 0 && flag_field_[y - 1][x] == 0) {
        ans.push_back({.x = x, .y = y - 1});
    }
    if (x > 0 && field_[y][x - 1] != -1 && player_field_[y][x - 1] == 0 && flag_field_[y][x - 1] == 0) {
        ans.push_back({.x = x - 1, .y = y});
    }
    if (y < height_ - 1 && field_[y + 1][x] != -1 && player_field_[y + 1][x] == 0 && flag_field_[y + 1][x] == 0) {
        ans.push_back({.x = x, .y = y + 1});
    }
    if (x < width_ - 1 && field_[y][x + 1] != -1 && player_field_[y][x + 1] == 0 && flag_field_[y][x + 1] == 0) {
        ans.push_back({.x = x + 1, .y = y});
    }

    if (y > 0 && x > 0 && field_[y - 1][x - 1] != -1 && player_field_[y - 1][x - 1] == 0 &&
        flag_field_[y - 1][x - 1] == 0) {
        ans.push_back({.x = x - 1, .y = y - 1});
    }
    if (x > 0 && y < height_ - 1 && field_[y + 1][x - 1] != -1 && player_field_[y + 1][x - 1] == 0 &&
        flag_field_[y + 1][x - 1] == 0) {
        ans.push_back({.x = x - 1, .y = y + 1});
    }
    if (x < width_ - 1 && y < height_ - 1 && field_[y + 1][x + 1] != -1 && player_field_[y + 1][x + 1] == 0 &&
        flag_field_[y + 1][x + 1] == 0) {
        ans.push_back({.x = x + 1, .y = y + 1});
    }
    if (y > 0 && x < width_ - 1 && field_[y - 1][x + 1] != -1 && player_field_[y - 1][x + 1] == 0 &&
        flag_field_[y - 1][x + 1] == 0) {
        ans.push_back({.x = x + 1, .y = y - 1});
    }
    return ans;
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (status_ == GameStatus::DEFEAT || status_ == GameStatus::VICTORY) {
        return;
    }
    if (open_count_ == 0) {
        start_ = std::time(nullptr);
        status_ = GameStatus::IN_PROGRESS;
    }
    if (flag_field_[cell.y][cell.x] == 1 || player_field_[cell.y][cell.x] == 1) {
        return;
    }
    if (field_[cell.y][cell.x] == -1) {
        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = 0; j < width_; ++j) {
                player_field_[i][j] = 1;
            }
        }
        status_ = GameStatus::DEFEAT;
        finish_ = std::time(nullptr);
        return;
    }
    std::queue<Minesweeper::Cell> cells_to_open;
    cells_to_open.push(cell);
    while (!cells_to_open.empty()) {
        auto el = cells_to_open.front();
        if (flag_field_[el.y][el.x] == 1 || player_field_[el.y][el.x] == 1) {
            cells_to_open.pop();
            continue;
        }
        player_field_[el.y][el.x] = 1;
        open_count_++;
        std::vector<Minesweeper::Cell> to_add = Minesweeper::CheckWhichCellsToOpen(el.y, el.x);
        for (auto i : to_add) {
            cells_to_open.push(i);
        }
        cells_to_open.pop();
    }
    if (open_count_ + mines_count_ == width_ * height_) {
        status_ = GameStatus::VICTORY;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (status_ == GameStatus::DEFEAT || status_ == GameStatus::VICTORY) {
        return;
    }
    flag_field_[cell.y][cell.x] = 1 - flag_field_[cell.y][cell.x];
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return status_;
}

time_t Minesweeper::GetGameTime() const {
    return finish_ - start_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField ans(height_, "");
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (flag_field_[i][j]) {
                ans[i] += "?";
            } else if (player_field_[i][j] == 0) {
                ans[i] += "-";
            } else if (field_[i][j] == -1) {
                ans[i] += "*";
            } else if (field_[i][j] == 0) {
                ans[i] += ".";
            } else {
                ans[i] += static_cast<char>('0' + field_[i][j]);
            }
        }
    }
    return ans;
}
