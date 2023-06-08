//
// Created by Administrator on 2023/6/8.
//

#include <iostream>

using namespace std;

void TestArgs(const std::string&);
int main()
{
        const std::string *str;
        std::string s1 = "s1";
        str = &s1;
        cout << str << endl;
        std::string s2 = "s2";
        str = &s2;
}

void TestArgs(const std::string& args)
{
    cout << args << endl;
    std::string str = "change";
}
