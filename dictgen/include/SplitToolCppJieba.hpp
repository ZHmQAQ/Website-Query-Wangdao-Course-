#include "./Configuration.hpp"
#include "./cppjieba/Jieba.hpp"
#include "./SplitTool.hpp"
#include <regex>

class SplitToolCppJieba
    : public SplitTool
{
public:
    SplitToolCppJieba(Configuration &conf)
        : _conf(conf),
        _path(_conf.getPath()),
        _jieba(_path["DICT_PATH"].c_str(), 
               _path["HMM_PATH"].c_str(),
               _path["USER_DICT_PATH"].c_str(),
               _path["IDF_PATH"].c_str(),
               _path["STOP_WORD_PATH"].c_str())
    {}

    virtual ~SplitToolCppJieba() {}

    //核心功能：切词，把string分解为词语，存储在vector<string>中并返回
    vector<string> cut(const string &sentence);

private:
    Configuration _conf;      // 配置文件
    unordered_map<string, string> _path; // 用来初始化jieba
    cppjieba::Jieba _jieba;   // 用来调用Jieba中的Cut函数
};

// 将sentence的单词切词，并将其存入vector<string>中，返回vector
inline vector<string> SplitToolCppJieba::cut(const string &sentence)
{
    vector<string> words;
    _jieba.Cut(sentence, words, true);
    return words;
}
