//
// Created by Administrator on 2023/6/9.
//
#include "main.h"
#include <mutex>

void add(int &);

void mainT();

void viceT();

int counter = 1000;

std::mutex mtx;

void mainT() {
    std::thread t1(add, std::ref(counter));
    std::thread t2(add, std::ref(counter));
    t1.join();
    t2.join();

}

void add(int &count) {
    std::lock_guard<std::mutex> lock(mtx);
    int i = 0;
    while (i < 1000) {
        ++count;
        ++i;
    }
}

int main() {
    mainT();
    cout << counter;
}
