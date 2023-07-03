//
// Created by Administrator on 2023/6/12.
//

#include <iostream>
#include <vector>
#include <list>
using namespace std;

vector<int> test();
int main()
{
    auto res = test();
    cout << res.size() << res.empty() <<  endl;
    res.erase(res.begin() + 2);
    //res.clear();
    //res.erase(res.begin(), res.end());
//    for(auto n : res){
//        cout << n << endl;
//    }
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

