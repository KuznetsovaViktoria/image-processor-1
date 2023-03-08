#include<algorithm>
#include<iostream>

#include "bmp.h"
#include "bmp.cpp"

int main(int argc, char *argv[]) {
    Bmp bmp;
    for (int i=0; i<argc; ++i){
        std::cout << argv[i]<<'\n';
        if (i==1){
            const char* ch = argv[i];
            bmp.Read(ch);
        }
        if (i==2){
            const char* ch = argv[i];
            bmp.Export(ch);
        }
    }
    return 0;
}
