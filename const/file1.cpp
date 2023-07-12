//
// Created by Administrator on 2023/7/6.
//

#include<iostream>
using namespace std;
extern int ext;
extern const int const_e;
int main(){
    std::cout << ext + 12 << std::endl;
    std::cout << const_e << std::endl;

    int a = 2;
    const int* ptr1 = &a; //
    cout << &ptr1;
//    *ptr1 = 1;
    ptr1 = nullptr;
    cout << &ptr1;
}