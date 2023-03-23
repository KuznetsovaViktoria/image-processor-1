#include <algorithm>
#include <iostream>
#include <vector>
#include "filter.h"
#include "bmp.h"
#include "grayscale.h"
#include "negative.h"
#include "crop.h"
#include "sharpening.h"
#include "edgeDetection.h"
#include "gaussianBlur.h"

int main(int argc, char* argv[]) {
    Bmp bmp;
    const char* read_file = nullptr;
    const char* export_file = nullptr;
    std::vector<Filter*> filters;
    std::vector<std::vector<double>> args;
    try {
        for (int i = 0; i < argc; ++i) {
            if (i == 1) {
                read_file = argv[i];
            } else if (i == 2) {
                export_file = argv[i];
            } else {
                std::string f = argv[i];
                if (f == "-crop") {
                    args.push_back({std::stod(argv[i + 1]), std::stod(argv[i + 2])});
                    filters.emplace_back(new Crop());
                    i += 2;
                } else if (f == "-gs") {
                    args.push_back({});
                    filters.emplace_back(new Grayscale());
                } else if (f == "-neg") {
                    args.push_back({});
                    filters.emplace_back(new Negative());
                } else if (f == "-sharp") {
                    args.push_back({});
                    filters.emplace_back(new Sharpening());
                } else if (f == "-edge") {
                    args.push_back({std::stod(argv[i + 1])});
                    filters.emplace_back(new EdgeDetection());
                    ++i;
                } else if (f == "-blur") {
                    args.push_back({std::stod(argv[i + 1])});
                    filters.emplace_back(new Blur());
                    ++i;
                }
            }
        }
        bmp.Read(read_file);
        for (int i = 0; i < static_cast<int>(filters.size()); ++i) {

            filters[i]->ApplyFilter(bmp, args[i]);
        }
        bmp.Export(export_file);
    } catch (const std::runtime_error& e) {
        std::cout << e.what();
    } catch (...) {
        std::cout << "some problem\n";
    }
    for (int64_t i = static_cast<int>(filters.size()) - 1; i >= 0; --i) {
        delete filters[i];
    }
    return 0;
}
