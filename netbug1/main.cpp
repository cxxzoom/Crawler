//
// Created by doff on 2023/5/21.
//

#include "main.h"

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

// download images
void DownloadImg(const std::vector <std::string> &vector) {
    for (const auto &path: vector) {
        // auto const 和 const auto 有什么区别
        const char *cpath = path.c_str();
        if (path.size() < 5) {
            continue;
        }

        std::string suffix;

        auto pos = path.find_last_of('.');
        auto leafs = path.substr(pos + 1);

        auto qm = leafs.find_last_of('?');
        if (qm) {
            suffix = leafs.substr(0, qm);
        } else {
            suffix = leafs;
        }


        if (suffix == "png" || suffix == "jpg" || suffix == "jpeg") {
            std::stringstream ss;
            const char *save_path = "img/";
            int rand_int = GetRandom();
            ss << save_path << std::time(nullptr) << rand_int << "." << suffix;
            std::string str = ss.str();
            char *file_name = const_cast<char *>(str.c_str());

            FILE *file = fopen(file_name, "wb+");
            cout << "file_name:" << file_name << endl;
            auto res = CURLRequest(cpath, file);
            if (res != CURLE_OK) {
                cout << cpath << "download fail";
            }
        }
    }

}

void DownloadImg2(const std::string& path)
{
    // auto const 和 const auto 有什么区别
    const char *cpath = path.c_str();
    if (path.size() < 5) {
        return;
    }

    std::string suffix;

    auto pos = path.find_last_of('.');
    auto leafs = path.substr(pos + 1);

    auto qm = leafs.find_last_of('?');
    if (qm) {
        suffix = leafs.substr(0, qm);
    } else {
        suffix = leafs;
    }


    if (suffix == "png" || suffix == "jpg" || suffix == "jpeg") {
        std::stringstream ss;
        const char *save_path = "img/";
        int rand_int = GetRandom();
        ss << save_path << std::time(nullptr) << rand_int << "." << suffix;
        std::string str = ss.str();
        char *file_name = const_cast<char *>(str.c_str());

        FILE *file = fopen(file_name, "wb+");
        cout << "file_name:" << file_name << endl;
        auto res = CURLRequest(cpath, file);
        if (res != CURLE_OK) {
            cout << cpath << "download fail";
        }
    }
}

size_t ParseHyperLink(const char *file_name, std::vector <std::string> &vector) {
    cout << "in ParseHyperLink" << endl;
    std::ifstream file(file_name);
    std::string line;
    if (!file.is_open()) {
        cout << "fail to open file" << endl;
        return -1;
    }

    std::regex pattern("(href|src)=\"([^\"]*)\"");

    while (std::getline(file, line)) {
        std::smatch match;
        std::string::const_iterator iterator(line.cbegin());
        while (std::regex_search(iterator, line.cend(), match, pattern)) {
            vector.push_back(match[2].str());
            cout << "match" << match[2].str() << endl;
            iterator = match.suffix().first;
        }
    }
    file.close();
    return 0;
}

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

int Request(const char* url, const char* base_file) {
    if(threads_int >= max_level){
        return 0;
    }

    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    FILE *file = fopen(base_file, "wb");  // 打开文件用于写入
    res = CURLRequest(url, file);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        return -1;
    }

    ThreadGets(base_file);

    // Task3 parse content
//    std::string content;
//    ExtractContent(file_name, content);
//    cout << content << endl;
    return 1;
}

CURLcode CURLRequest(const char *url, FILE *file) {
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

void ThreadGet(const std::vector<std::string>& vector,const std::string& path,int current)
{
    // 遍历这个数组，然后根据个数创建线程，然后执行 抓取，解析，多线程，下载，的重复操作。
    for (auto& v : vector) {
        std::thread();
    }
}

void ThreadGets(const char *file_name)
{
    std::vector <std::string> hyperlinks;
    //Task2 parse hyperlink and download
    ParseHyperLink(file_name, hyperlinks);
    // 创建线程去fetch 这些超连接
    for (const std::string& v : hyperlinks){
        ++threads_int;
        std::string save_path = "html/";
        save_path.append(v);
        std::thread(Request,v.c_str(),save_path.c_str());
    }

    // 创建线程去download img
    for(const std::string& v : hyperlinks){
        std::thread(DownloadImg2,v);
    }
}

