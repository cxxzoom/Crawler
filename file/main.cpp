//
// Created by Administrator on 2023/6/8.
//

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    std::string file_path = "h\\2.html";
    FILE* file = fopen(file_path.c_str(), "w");
    if (file != nullptr) {
        std::string myString = "123asl;edkjlojdl;fjakls;dmf';laskjdf";
        fwrite(myString.c_str(), sizeof(char), myString.size(), file);
        fclose(file);
        printf("Write successful.\n");
    } else {
        printf("Failed to open file.\n");
    }
    return 0;
}

