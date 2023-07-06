//
// Created by Administrator on 2023/6/12.
//

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <map>
#include <array>
#include <deque>
#include <forward_list>
#include <unordered_map>
#include <ctime>
#include <chrono>

using namespace std;

void test();

void ls();

void s1();

void map1();

void arr1();

void deque1();

void urm();

void forward_list1();
int main() {
//    test();
//    ls();
//    s1();
//    map1();
//    arr1();
//    deque1();
//    forward_list1();
    urm();
    return 0;

}

void test() {
    vector<int> res = {1, 2, 3, 4, 5};
//    cout << res.size() << res.empty() << endl;
//    res.erase(res.begin() + 2);
//
//    auto it = std::find(res.begin(), res.end(), 3);
//    cout << *it << endl;
//    //res.clear();
//    res.erase(res.begin(), std::find(res.begin(), res.end(), 3));
//
//    res.insert(res.begin(), 9);
//    res.push_back(9);
//    for (int i = 0; i < res.size(); ++i) {
//        cout << i << "::::" << res[i] << endl;
//    }
//    cout << "===============================" << endl;
//    res.erase(std::find(res.begin(), res.end(),9999));
//    res.erase(res.begin() + 2);
//    for (int i = 0; i < res.size(); ++i) {
//        cout << res[i] << endl;
//    }
    cout << res.at(1) << endl;
}

void ls() {
    list<int> numbers(7);
    numbers.push_front(1);
    numbers.push_back(2);
    for (auto &n: numbers) {
        cout << n << endl;
    }

    cout << "===============" << endl;
    cout << numbers.front() << endl;
    cout << numbers.back() << endl;
    // 删除元素：迭代器
    numbers.erase(std::find(numbers.begin(), numbers.end(), 2));
}

void s1() {
    set<int> s;
    s.insert(1);
    auto i = s.find(1);
    s.erase(s.find(1));

    for (auto &n: s) {
        cout << n << endl;
    }
    s.clear();
}

void map1() {
    map<std::string, int> m = {
            {"1", 1},
            {"1", 2},
            {"3", 3},
            {"4", 4},
            {"5", 5},
    };

    map<std::string, int> n = {
            {"7", 7},
            {"8", 8},
    };
    m.swap(n);

    for (auto &a: m) {
        cout << a.second << endl;
    }
    cout << "----" << endl;
    for (auto &b: n) {
        cout << b.second << endl;
    }
    cout << "----" << endl;
}

void arr1() {
    std::array<int, 8> a = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << a.empty() << endl;
    cout << a.size() << endl;
    cout << a.max_size() << endl;
    cout << a.front() << endl;
    cout << a.at(3);
};

void deque1() {
    deque<int> deque2 = {1,2,3};
    deque2.push_back(4);
    deque2.push_front(0);
    for (auto n:deque2) {
        cout << n << endl;
    }
}


void forward_list1()
{
    forward_list<int> fl = {1,2,3,};
    fl.push_front(0);
    fl.insert_after(fl.begin(),2);
    fl.erase_after(fl.begin());
//    fl.insert_after(fl.end(),5);
    fl.emplace_front(2);
    for (int n : fl) {
        cout << n << endl;
    }
}

void urm(){
    unordered_map<long int,std::string> myMap{};
    map<long int , std::string> mp{};
    for (long int i = 0; i < 1e7; ++i) {
        myMap[i] = std::to_string(i);
        mp[i] = std::to_string(i);
    }
    // todo
    auto s1 =  std::chrono::high_resolution_clock::now();
    auto myMapIndex = myMap[static_cast<long>(1e6)];
    auto e1 = std::chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::microseconds>(e1 - s1);
    cout << dur.count() << endl;

    auto s2 = std::chrono::high_resolution_clock::now();
    auto myMapIndex2 = mp[static_cast<long>(1e6 + rand())];
    auto e2 = std::chrono::high_resolution_clock::now();

    dur = chrono::duration_cast<chrono::microseconds>(e2 - s2);
    cout << dur.count() << endl;
}


