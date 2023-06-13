//
// Created by Administrator on 2023/6/12.
//

#include <iostream>
#include <vector>
using namespace std;

vector<int> test();
int main()
{
    auto res = test();
    for(auto n : res){
        cout << n << endl;
    }

    return 0;
}

vector<int> test()
{
    return {-1,-1};
}