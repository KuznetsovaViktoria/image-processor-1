#include <algorithm>
#include <iostream>
#include <vector>

#include "bmp.cpp"
#include "grayscale.cpp"
#include "negative.cpp"
#include "sharpening.cpp"
#include "edgeDetection.cpp"
#include"matrixFilter.cpp"
#include"filter.cpp"

int main(int argc, char* argv[]) {
    Bmp bmp;
    const char* read_file = nullptr;
    const char* export_file = nullptr;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << '\n';
        if (i == 1) {
            read_file = argv[i];
        }
        if (i == 2) {
            export_file = argv[i];
        }
        // later need to add checking for errors and incorrect data
    }
    bmp.Read(read_file);
    std::vector<Filter*> filters;
    //    filters.emplace_back(new Grayscale());
    //    std::cout<<"eenter in main!";
    //    filters[0]->ApplyFilter(bmp);
    //    std::cout<<"exit in main";
    //    delete filters[0];
//    std::cout<<"enter\n";
//    EdgeDetection g;
    Grayscale gr;
    gr.ApplyFilter(bmp);
//    g.ApplyFilter(bmp);
//    g.CorrectColors(bmp);
//    std::cout<<"exit\n";
    bmp.Export(export_file);
    return 0;
}
