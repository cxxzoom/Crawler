//
// Created by Administrator on 2023/6/13.
//

#include <iostream>
#include <windows.h>
#include <vector>
#include "t1config.h.in"
#include <cmath>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc,char* argv[]){
    cout << "hello cmake" << endl;
    std::vector<int> vector1 = {1};
    std::string message = "Hello, world!";
    cout << message << endl;
    char strings[] = {'1','2','3','5','7','9'};
    for(const auto &v : strings){
        //cout << v << endl;
    }

    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                << Tutorial_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    return 0;
}