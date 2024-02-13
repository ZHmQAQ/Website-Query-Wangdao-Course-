#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include "Configuration.hpp"
using std::string;
using std::map;
using std::vector;
using std::set;
// 读取英文 txt 文件，生成词典文件 EnDict.txt 和索引文件 EnDictIndex.txt
// 通过单例对象 Configuration 读取配置文件
// 词典文件格式：
// word(string) frequency(int)
// 词典索引文件格式：
// letter(string) set(包含该字母的所有单词的集合)
class EnDictgen
{
public:
    // 需要用配置类 Configuration 来初始化
    EnDictgen(Configuration& conf)
    :_conf(conf)
    {
        readFilePath();
    }

    void storeDict(const string& filename);        //将词典库写入到文件中
    void storeIndex(const string& filename);    //将索引库写入到文件
    void create();      // 生成 _dict 和 _index 对象

private:
    void readFilePath();    // 从 _conf 读取文件路径
    void addToDict(const string& filename);     //添加文章单词
    void addToIndex(const string & word, int lineNumber); //添加索引
    void processLine(string& line);   //处理一行
    void processWord(string& word);   //处理单词

private:
    Configuration& _conf;       //配置文件
    vector<string> _path;      //语料库文件路径集合
    map<string, int> _dict;     //英文词典库
    map<string, set<int>> _index; //英文索引库
};

