//
// Created by doff on 2023/5/21.
//

#include "main.h"

using namespace std;
int max_level;
int threads_int = 0;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    const char *base_file = "html/1.html";
    char *url;
    cout << "input url:" << endl;
    cin >> url;
    cout << "input max level:";
    cin >> max_level;
    Request(url, base_file);
}

int Request(const char *url, const char *base_file) {
    if(url == nullptr || base_file == nullptr){
        return -1;
    }

//    cout << "this url is : " << url << endl;
    cout << "base_file is : " << base_file << endl << endl;

    if (threads_int >= max_level) {
        return 0;
    }

    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    FILE *file = fopen(base_file, "wb");  // 打开文件用于写入
    if (file == nullptr) {
        std::cerr << "Request function open " << base_file << "with error" << std::strerror(errno);
    }

    res = CURLRequest(url, file);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//        return -1;
        // if error continue;
    }

    ThreadGets(base_file);
    return 1;
}

CURLcode CURLRequest(const char *url, FILE *file) {
    cout << "request url is : " <<  url << endl;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    std::string receivedData;
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,
                     "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackFunction);
    //        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &receivedData);  // 将文件指针传递给回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Write2File);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    res = curl_easy_perform(curl);

    fclose(file);

    curl_easy_cleanup(curl);

    return res;
}

void ExtractContent(const char *file_name, std::string &content) {
    cout << "in ExtractContent >> " << file_name << endl;
    std::ifstream file(file_name);
    std::string line;
    if (!file.is_open()) {
        cout << "fail to open file" << endl;
        return;
    }

    while (std::getline(file, line)) {
        // 创建一个string 的 迭代器
        std::string::const_iterator iterator(line.cbegin());
        std::regex pattern("<(li|p|span|div)([^>]*)\">([^<]*)");
        std::smatch match;
        cout << "match-begin" << endl;
        while (std::regex_search(iterator, line.cend(), match, pattern)) {
            std::string match3 = match[3];
            if (!std::all_of(match3.cbegin(), match3.cend(), [](unsigned char c) {
                return std::isspace(c);
            })) {
                content += match3;
            }
            iterator = match.suffix().first;
        }
    }
}

void ThreadGet(const std::vector<std::string> &vector, const std::string &path, int current) {
    // 遍历这个数组，然后根据个数创建线程，然后执行 抓取，解析，多线程，下载，的重复操作。
    for (auto &v: vector) {
        std::thread();
    }
}

void ThreadGets(const char *file_name) {
    cout << "TreadGets` file_name = " << file_name << endl;
    std::vector<std::string> hyperlinks;
    std::vector<std::thread> threads;
    //Task2 parse hyperlink and download
    ParseHyperLink(file_name, hyperlinks);
    // TODO 过滤
    std::vector<std::string> img;
    FilterHyperLink(hyperlinks, img);

//    创建线程去download img
//    for (const std::string &v: img) {
//        threads.emplace_back(DownloadImg2, v);
//    }



    // 创建线程去fetch 这些超连接
    for (const std::string &v: hyperlinks) {
        cout << v << endl;
        ++threads_int;
        std::string save_path = "html/";
        save_path.append(to_string(GetRandom()));
        save_path.append(".html");
        threads.emplace_back(Request, v.c_str(), save_path.c_str());
    }

    for (auto &thread: threads) {
        thread.join();
    }
}

size_t callbackFunction(char *data, size_t size, size_t nmemb, std::string *result) {
    size_t totalSize = size * nmemb;
    result->append(data, totalSize);
    return totalSize;
}

int GetRandom() {
    // choose random engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // 创建随机数分布
    std::uniform_int_distribution<> dis(1e0, 1e4);

    // 生成随机数
    return dis(gen);
}

size_t Write2File(char *data, size_t size, size_t nmemb, FILE *file) {
    return fwrite(data, size, nmemb, file);
}

void DownloadImg2(const std::string &path) {
    // auto const 和 const auto 有什么区别
    const char *cpath = path.c_str();
    if (path.size() < 5) {
        return;
    }

    std::string suffix;
    std::string find = ".";
    std::string relation = "?";
    GetSuffix(path, suffix, find, relation);

    if (suffix == "png" || suffix == "jpg" || suffix == "jpeg" || suffix == "pdf" || suffix == "gif") {
        std::stringstream ss;
        const char *save_path = "img/";
        int rand_int = GetRandom();
        ss << save_path << std::time(nullptr) << rand_int << "." << suffix;
        std::string str = ss.str();
        char *file_name = const_cast<char *>(str.c_str());

        FILE *file = fopen(file_name, "wb+");
        auto res = CURLRequest(cpath, file);
        if (res != CURLE_OK) {
            cout << cpath << "download fail" << endl;
        }
    }
}

size_t ParseHyperLink(const char *file_names, std::vector<std::string> &vector) {
    std::string file_name = file_names;
    std::ifstream file(file_name);
    StrReplace(file_name);
    std::string line;
    if (!file.is_open()) {
        cout << "fail to open file in ParseHyperlink: " << file_name << std::strerror(errno) << endl;
        //return -1;
    }

    std::regex pattern("(href|src)=\"([^\"]*)\"");

    while (std::getline(file, line)) {
        std::smatch match;
        std::string::const_iterator iterator(line.cbegin());
        while (std::regex_search(iterator, line.cend(), match, pattern)) {
            // 这里写个filter 的方法，返回bool值，如果满足条件则写入
            std::string match2 = match[2].str();
            if (FilterMatch(match2)) {
                vector.push_back(match2);
//                cout << "match " << match2 << endl;
            }
            iterator = match.suffix().first;
        }
    }
    file.close();
    return 0;
}

void StrReplace(std::string &str) {
    auto begin_sub = str.length() % std::numeric_limits<int>::max();
    str = str.substr(str.length() - begin_sub);
    std::vector<std::string> vector1 = {"/", "\\", "?", ":", "|", "\"", "*"};
    std::vector<int> vector2 = {1, 9};
    for (std::string &v: vector1) {
        std::string random_int = std::to_string(7);
        std::string::size_type start = 0;
        while ((start = str.find(v, start)) != std::string::npos) {
            str.replace(start, 1, random_int);
            ++start;
        }
    }

    str = str.substr(min(0, static_cast<int>(str.length() - 10)));
}

void FilterHyperLink(std::vector<std::string> &hyperlink, std::vector<std::string> &img) {
    // 这里就剔除图片文件以及其他杂项
    auto iter = hyperlink.begin();
    while (iter != hyperlink.end()) {
        std::string suffix;
        std::string find = ".";
        std::string relation = "?";
        GetSuffix(*iter, suffix, find, relation);
        if (suffix == "jpg" || suffix == "png" || suffix == "pdf" || suffix == "ico" || suffix == "gif" ||
            suffix.find_last_of("<") != std::string::npos) {
            // 删除当前迭代器指向的元素，并返回下一个有效的迭代器
            img.push_back(*iter);
            iter = hyperlink.erase(iter);
            continue;
        }
        ++iter;
    }
}

bool FilterMatch(std::string &match) {
    if (match.length() < 5) {
        return false;
    }

    const std::string path = match;
    const std::string find = ".";
    const std::string relation = "?";
    std::string suffix;
    GetSuffix(path, suffix, find, relation);

    if (suffix == "js" || suffix == "css" || suffix == "xml") {
        return false;
    }

    if (match.front() == '/') {
        match = "https://tieba.baidu.com/" + match;
    }

    return true;
}

void GetSuffix(const std::string &path, std::string &suffix, const std::string find, const std::string relation) {
    auto pos = path.find_last_of(find);
    auto leafs = path.substr(pos + 1);

    auto qm = leafs.find_last_of(relation);
    if (qm) {
        suffix = leafs.substr(0, qm);
    } else {
        suffix = leafs;
    }
    return;
}

