#pragma once
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
// 读取配置文件
// 配置文件每行为 string, string ，对应 参数名 路径 
class Configuration
{
public:
    ~Configuration() {}
    Configuration(const string& config_path);
    unordered_map<string, string>& getPath();
private:
    void readConfig();
private:
    const string _config_path; // 配置文件存放路径
    unordered_map<string, string> _paths; // 语料库 参数名-路径
};

