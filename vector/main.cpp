//
// Created by Administrator on 2023/6/12.
//

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

vector<int> test();
int main()
{
    auto res = test();
    cout << res.size() << res.empty() <<  endl;
    res.erase(res.begin() + 2);

    auto it = std::find(res.begin(), res.end(), 3);
    cout << *it << endl;
    //res.clear();
    res.erase(res.begin(), std::find(res.begin(), res.end(), 3));

    res.insert(res.begin(),9);
    for (int i = 0; i < res.size();++i) {
        cout << i << "::::" << res[i] << endl;
    }

    return 0;
}

vector<int> test()
{
    return {1,2,3,4,5};
}

list<int> ls()
{
    list<int> numbers(7);
}

