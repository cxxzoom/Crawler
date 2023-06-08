//
// Created by doff on 2023/5/21.
//

#ifndef PROBLEM_CURLDEMO_H
#define PROBLEM_CURLDEMO_H

#include <iostream>
#include "../curl/curl.h"
#include <regex>
#include <fstream>
#include <random>
#include <thread>
#include <cerrno>

using namespace std;

#endif //PROBLEM_CURLDEMO_H

int Request(const char*, const char*);
// hava an curl request
CURLcode CURLRequest(const char *url, FILE *file);
//write curl content to file
size_t Write2File(char *data, size_t size, size_t nmemb, FILE *file);
// parseHyperLink
size_t ParseHyperLink(const char *, std::vector<std::string> &);
//download img
void DownloadImg(const std::vector<std::string> &);

// filter hyperlink use 2nd vector
void Filter(std::vector<std::string> &, std::vector<std::string>);
// extract content
void ExtractContent(const char *, std::string &);
// get random int
int GetRandom();

void ThreadGet(const std::vector<std::string>& ,const std::string& ,int );

void ThreadGets(const char *);
// download single img for thread
void DownloadImg2(const std::string&);
// string replace
void StrReplace(std::string &str);
//
void FilterHyperLink(std::vector<std::string>& hyperlink, std::vector<std::string>& img);
// find suffix from path.
void GetSuffix(const std::string& path, std::string& suffix, const std::string find, const std::string relation);

bool FilterMatch(std::string& match);