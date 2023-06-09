//
// Created by Administrator on 2023/6/9.
//

#include <iostream>
#include <thread>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;
void Write(const std::string& file_name);
void TreadTest(const std::vector<std::string>&);
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::vector<std::string> vector1 = {"./html/1.log","2.log","3.log","4.log"};
    TreadTest(vector1);
}

void Write(const std::string& file_name)
{
    std::fstream file(file_name, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << file_name << std::endl;
        return;
    }

    file << file_name << std::endl;
    file.close();
}

void TreadTest(const std::vector<std::string>& vector1)
{
    std::vector<std::thread> threads;
    for (const auto &v : vector1){
        threads.emplace_back(Write,v);
    }

    for (auto &thread : threads) {
        thread.join();
    }
}