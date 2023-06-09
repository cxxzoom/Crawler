//
// Created by Administrator on 2023/6/9.
//
#include "main.h"

void T1();
void T2();
void Echo();
std::mutex mtx;
std::condition_variable cv;
bool start = false;
void T1()
{
    std::thread thread1(T2);
    std::this_thread::sleep_for(std::chrono::seconds(6));
    {
        std::lock_guard<std::mutex> lock(mtx);
        start = true;
    }
    cv.notify_all();
    thread1.join();
}

void T2()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock,[&]{
        return start;
    });
    std::thread thread(Echo);
    thread.join();
}

void Echo()
{
    cout << "out" << endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    T1();
}