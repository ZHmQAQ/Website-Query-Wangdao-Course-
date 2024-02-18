#pragma once

#include "../include/Configuration.hpp" 
#include "../include/SplitToolCppJieba.hpp"
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::set;

class DictProducer {
public:
    explicit DictProducer(Configuration& conf, SplitToolCppJieba& cuttor);

    // 生成词典库
    void create();

    // 将生成的词典库和索引库存储到文件
    void storeDict(const string& filename);
    void storeIndex(const string& filename);

    
private:
    // 创建停用词词集
    void addToStopWordList(const string &filename);

    // 读取文件路径
    void readFilePath();

    // 处理每个文件，将单词添加到词典库
    void addToDict(const string& filename);

    // 对每行内容进行处理
    vector<string> processLine(string& line);

    // 对每个单词进行处理
    void processWord(string& word);

    // 将单词添加到索引库
    void addToIndex(const string &word, int lineNumber);

private:
    SplitToolCppJieba & _cuttor; // 初始化的时候需要传入 cuttor 对象
    Configuration& _conf; // 配置类实例引用
    vector<string> _path; // 存储语料库文件路径
    vector<string> _stop_word_path; // 停用词文件路径
    unordered_set<string> _stop_word; // 停用词词集
    unordered_map<string, int> _dict; // 词典库，存储单词及其出现次数
    unordered_map<string, set<int>> _index; // 索引库，存储单词字母及其所在行号
};

