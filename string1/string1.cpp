//
// Created by Administrator on 2023/6/5.
//

#include "string1.h"
#include <vector>
#include <random>
#include <algorithm>
int GetRandom(std::vector<int>&);
void FindSuffix();
void StrReplace(std::string&);
using namespace std;
int main() {
    std::string str = "//tb1.bdstatic.com/??/tb/_/voice_efe9e00.css,/tb/_/tbshare_aa97892.css,/tb/_/aside_float_bar_a9f1cb0.css,/tb/_/app_download_7ac9367.css";
    StrReplace(str);
    cout << str;
}

// find hyperlink suffix whatever with resource
void FindSuffix()
{
    std::string str = "https://pic1.zhimg.com/v2-8334b702e42ba8bff03e69ba323f96fb_l.jpg?source=5a24d060";
    auto pos = str.find_last_of('.');
    auto sub = str.substr(pos + 1);
    auto pos1 = sub.find_last_of('?');
    auto suffix = sub.substr(0, pos1);
    cout << suffix << endl;
}

// substr file_name and replace random_int
void StrReplace(std::string &str) {
    auto begin_sub = str.length() % std::numeric_limits<int>::max();
    str = str.substr(str.length() - begin_sub);
    std::vector<std::string> vector1 = {"/", "\\", "?", ":", "|", "\"", "*"};
    std::vector<int> vector2 = {1,9};
    for (std::string &v: vector1) {
        std::string random_int = std::to_string(GetRandom(vector2));
        std::string::size_type start = 0;
        while((start = str.find(v, start)) != std::string::npos){
            str.replace(start,1, random_int);
            ++start;
        }
    }

    str = str.substr(min(0,static_cast<int>(str.length() - 10)));
    str = str.substr(min(0,*str.end()-10));
}

int GetRandom(std::vector<int>& vector2) {
    // choose random engine
    std::random_device rd;
    std::mt19937 gen(rd());
    int max_int = max(vector2[0],vector2[1]);
    int min_int = min(vector2[0],vector2[1]);

    // 创建随机数分布
    std::uniform_int_distribution<> dis(min_int, max_int);

    // 生成随机数
    return dis(gen);
}