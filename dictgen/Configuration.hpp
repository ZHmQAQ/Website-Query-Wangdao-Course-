#pragma once
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
// 读取配置文件，读取语料库文件转化为数据成员
// 配置文件每行为 string, string ，对应 文件名 路径 
// 如果文件名以 “stop_words” 开头，将其加入 _stop_word_path_list
// 否则，将其加入 _path_list 语料库
class Configuration
{
public:
    ~Configuration() {}

    // 获取单例，该单例不是线程安全的，不过离线模式不需要多线程，因此简写
    static Configuration& getInstance(const string& config_path);

    // 获取语料库文件列表
    unordered_map<string, string>& getConfigPathList();

    // 获取停用词文件列表
    unordered_map<string, string>& getStopWordPathList();

    // 读取配置文件
    void readConfig();
private:
    // 因为是单例模式 所以构造函数私有化
    Configuration(const string& config_path);

private:
    const string _config_path; // 配置文件存放路径
    unordered_map<string, string> _path_list; // 语料库 文件名-路径
    unordered_map<string, string> _stop_word_path_list; // stopword 的路径
};

