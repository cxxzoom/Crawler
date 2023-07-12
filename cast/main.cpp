//
// Created by Administrator on 2023/7/6.
//

#include "main.h"
using namespace std;
struct B
{
    int m = 0;
    void hello()
    {
        std::cout << "Hello world B\n";
    }
};

struct D : B
{
    void hello()
    {
        std::cout << "Hello world D\n";
    }
};

enum E{O,P,Q};

int main() {
    D d;
    B& br = d;
    d.hello();
    D& down = static_cast<D&>(br);
    down.hello();



    vector<int> v1{1,2,3};
    vector<int> v2 = static_cast<vector<int>&&>(v1);
    cout << v1.size() << endl;
    cout << v2.size() << endl;
    for (auto n : v1) {
        cout << n << endl;
    }

    cout << "=====" << endl;

    int n = static_cast<int>(3.14);
    cout << n << endl;

    vector<int> vv = static_cast<vector<int>>(10);
    cout << vv.size() << endl;

    static_cast<void>(v2.size());

    cout << "=====" << endl;
    for (auto n1:v2) {
        cout << n1 << endl;
    }

    // 5. 隐式转换的逆转换
    void* nv = &n;
    cout << nv <<endl;
    int* ni = static_cast<int*>(nv);
    std::cout << "*ni = " << *ni << '\n';

    int nn = 1;
    void* n1 = &nn;
    int* n2 = static_cast<int*>(n1);
    cout << *n2 << endl;

    E e = E::O;

    try {
        vector<int> n = {1,2,3,4};
        for (auto aa:n) {
            cout << aa << endl;
        }
        cout << "size:" << n.size() << "=>" << n.at(9) << endl;

    }catch (exception& e){
        cout << e.what() << endl;
    }

    return 0;
}

class  A final {

};

class H : A{

};