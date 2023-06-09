//
// Created by Administrator on 2023/6/9.
//

#include "t1.h"
#include "main.h"
void hello(std::string&);
void mainT();
void viceT();
void mainT()
{
    std::string s = "mainT";
    hello(s);
    std::thread thread(viceT);
    thread.join();
}

void viceT()
{
    std::string s = "viceT";
    std::thread thread(hello,std::ref(s));
    thread.join();
}

void hello(std::string& s)
{
    cout << "hello " << s << endl;
}

int main()
{
    mainT();
}

