//
// Created by Administrator on 2023/7/6.
//

#include <algorithm>
#include "main.h"

void operation()
{
    std::string s = "1984-big-brother-is-watching-you";
    s += '!';
    cout << s << endl;

    std::string sub = s.substr(0,s.length() - 14);
    cout << sub << endl;

    auto fi = s.find_first_of('y');
    cout << fi << endl;
}

int main()
{
    operation();
}

