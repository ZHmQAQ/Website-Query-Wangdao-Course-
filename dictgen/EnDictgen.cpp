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
using std::string;
using std::map;
using std::vector;
using std::set;
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::endl;


// 放在构造函数中，初始化数据成员 _files
void EnDictgen::readFilePath(){
    unordered_map<string, string> & m = _conf.getConfigPathList();
    for(auto it : m){
        _files.push_back(it.second);
    }
}

// 读取 _files ，拿出每个单词，用于创建词典文件 _dict
void EnDictgen::createDict(){
    // 遍历每个路径，提取文件
    for(auto& it : _files){
        addFileWord(it);
    }

}

// 对每个文件，将其加入词典库 _dict
void EnDictgen::addFileWord(const string& filename){
    ifstream ifs(filename);
    if(!ifs)
    {
        cerr << "open file error: " << filename << endl;
        return;
    }

    string line, word;
    while(getline(ifs, line)){
        
    }
}



void EnDictgen::storeDict(const string& filename){

}
void EnDictgen::storeIndex(const string& filename){




}
    string dealWord(const string& word);    //处理单词
    void addIndex(const string & word, int lineNumber); //添加索引
    void dealLine(string& line);        //处理一行


