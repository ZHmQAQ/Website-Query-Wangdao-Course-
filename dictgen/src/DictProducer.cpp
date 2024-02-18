#include "../include/DictProducer.hpp"
#include <iostream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::endl;
using std::ofstream;

DictProducer::DictProducer(Configuration & conf, SplitToolCppJieba& cuttor)
    : _conf(conf), _cuttor(cuttor)
{
    readFilePath();
}


// 放在构造函数中，初始化数据成员 _path 和 _stop_word_path
void DictProducer::readFilePath(){
    unordered_map<string, string> & m = _conf.getPath();
    for(auto it : m){
        // 如果是以 stop_word 开头的文件，将其加入 _stop_word_path
        if(it.first.substr(0, 10) == "stop_words"){
            _stop_word_path.push_back(it.second);
        }
        // 否则，加入 _path
        else{
            _path.push_back(it.second);
        }
    }
}

// 读取 _stop_word_path, 创建停用词 set _stop_word
// 读取 _path ，创建词典 map _dict 和词典索引 _index
void DictProducer::create(){
    // 遍历每个路径，提取文件
    for(auto& path : _stop_word_path){
        addToStopWordList(path);
    }
    for(auto& path : _path){
        addToDict(path);
    }

}

// 创建停用词词集
void DictProducer::addToStopWordList(const string & filename){
    ifstream ifs(filename);
    if(!ifs)
    {
        cerr << "open file error: " << filename << endl;
        return;
    }
    string line; // 一行一个词
    while(getline(ifs, line)){
        _stop_word.insert(line);
    }
}

// 对每个文件，
// 1. 对其中的每行先使用 cuttor 分词，
// 2. 读取每个单词，查看是否停用词，将其加入词典库 _dict
void DictProducer::addToDict(const string& filename){
    ifstream ifs(filename);
    if(!ifs)
    {
        cerr << "open file error: " << filename << endl;
        return;
    }


    string line, word;
    int lineNumber = 1;
    while(getline(ifs, line)){
        vector<string> temp; // 用于存放分词结果
        temp = processLine(line); // 处理行，使用 cuttor 分词，消除标点符号和停用词
        for(auto & word : temp){
            processWord(word); // 处理单词，全化为小写
            ++_dict[word];
            addToIndex(word, lineNumber); // 对每个单词，将其加入索引
        }
        lineNumber ++;
    }
    ifs.close();
}

// 处理行，
vector<string> DictProducer::processLine(string& line){
    // 使用 cuttor 对 line 进行分词
    vector<string> words = _cuttor.cut(line);
    vector<string> result;

    for(auto & word : words){
        // 删除单词中的标点符号
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::ispunct(c); }), word.end());
        // 检查是否停用词
        if(_stop_word.find(word) == _stop_word.end()){
            result.push_back(word);
        }
    }
    return result;
}

// 处理单词，将大写全部转化为小写
void DictProducer::processWord(string& word){
 std::transform(word.begin(), word.end(), word.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}


// 对于每个单词，把它拆分成若干个 字母-行号 键值对，插入到 _index 中
// 中文字符的处理：在 utf-8 编码中，首字节表示字符字节数
void DictProducer::addToIndex(const string & word, int lineNumber){
    size_t i = 0;
    while (i < word.size()){
        size_t len = 1; // 默认为单字节字符
        unsigned char lead = word[i];
        if ((lead >> 3) == 30) { // 11110xxx 4字节字符
            len = 4;
        } else if ((lead >> 4) == 14) { // 1110xxxx 3字节字符
            len = 3;
        } else if ((lead >> 5) == 6) { // 110xxxxx 2字节字符
            len = 2;
        }
        // 提取当前字符（可能是单字节也可能是多字节）
        string character = word.substr(i, len);
        // 将字符（字母或汉字）与行号映射
        _index[character].insert(lineNumber);
        i += len; // 移动到下一个字符的起始位置
    }
}

// 把生成完毕的 _dict 转化为文件
void DictProducer::storeDict(const string& filename){
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
void DictProducer::storeIndex(const string& filename){
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
void test0(const string &confpath, const string &jiebaconfpath){
    // 读取 conf 文件
    Configuration conf(confpath);
    Configuration jiebaconf(jiebaconfpath);
    SplitToolCppJieba cuttor(jiebaconf);
    // 创建 DictProducer 对象
    DictProducer obj(conf, cuttor);

    obj.create();      // 生成词典库
    obj.storeDict("_dict.txt");     //存储词典和生成索引库
    obj.storeIndex("_index.txt");   //存储词典库
}


int main(){
    test0("../conf/art.conf", "../conf/jiebaConf.conf");
    return 0;
}
