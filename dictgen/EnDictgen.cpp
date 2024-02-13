#include <iostream>
#include "EnDictgen.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include "Configuration.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using std::string;
using std::map;
using std::vector;
using std::set;
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::endl;
using std::ofstream;

// 放在构造函数中，初始化数据成员 _files
void EnDictgen::readFilePath(){
    unordered_map<string, string> & m = _conf.getConfigPathList();
    for(auto it : m){
        _path.push_back(it.second);
    }
}

// 读取 _files ，拿出每个单词，用于创建词典文件 _dict
void EnDictgen::create(){
    // 遍历每个路径，提取文件
    for(auto& path : _path){
        addToDict(path);
    }

}

// 对每个文件，读取每个单词，将其加入词典库 _dict
void EnDictgen::addToDict(const string& filename){
    ifstream ifs(filename);
    if(!ifs)
    {
        cerr << "open file error: " << filename << endl;
        return;
    }

    string line, word;
    int lineNumber = 1;
    while(getline(ifs, line)){
        processLine(line); // 处理行，消除标点符号
        istringstream iss(line);
        while(iss >> word){
            processWord(word); // 处理单词，全化为小写
            ++_dict[word];
            addToIndex(word, lineNumber); // 对每个单词，将其加入索引
        }
        lineNumber ++;
    }
    ifs.close();
}

// 处理行，删去标点符号，用一个 lambda 表达式一行搞定
void EnDictgen::processLine(string& line){
    line.erase(std::remove_if(line.begin(), line.end(), [](unsigned char c) { return std::ispunct(c); }), line.end());
}

// 处理单词，将大写全部转化为小写
void EnDictgen::processWord(string& word){
 std::transform(word.begin(), word.end(), word.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}


// 对于每个单词，把它拆分成若干个 字母-行号 键值对，插入到 _index 中
void EnDictgen::addToIndex(const string & word, int lineNumber){
    for(size_t i = 0; i < word.size(); ++i)
    {
        // 提取第i个字符作为长度为1的字符串
        string letter = word.substr(i, 1);
        _index[letter].insert(lineNumber);
    }
}

// 把生成完毕的 _dict 转化为文件
void EnDictgen::storeDict(const string& filename){
    ofstream ofs(filename);
    if(!ofs){
        cerr << "open file error: " << filename << endl;
        return;
    }

    for(auto& it : _dict){
        ofs << it.first << " " << it.second << endl;
    }
    ofs.close();
}

// 把生成完毕的 _index 转化为文件
void EnDictgen::storeIndex(const string& filename){
    ofstream ofs(filename);
    if(!ofs){
        cerr << "open file error: " << filename << endl;
        return;
    }

    for(auto & it : _index){
        ofs << it.first;
        for(auto& num : it.second){
            ofs << " " << num;
        }
        ofs << endl;
    }
    ofs.close();
}


// test 函数
void test0(const string &confpath){
    Configuration& conf = Configuration::getInstance(confpath);
    conf.readConfig();      // 读取配置文件

    EnDictgen obj(conf);

    obj.create();      // 生成词典库
    obj.storeDict("eng_dict.txt");     //存储词典和生成索引库
    obj.storeIndex("eng_index.txt");   //存储词典库
}



