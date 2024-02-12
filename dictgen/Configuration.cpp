#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Configuration.hpp"

using std::string;
using std::unordered_map;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::endl;
// 获取单例对象
Configuration& Configuration::getInstance(const string& config_path){
    static Configuration instance(config_path);
    return instance;
}

unordered_map<string, string>& Configuration::getConfigPathList(){
    return _path_list;
}

unordered_map<string, string>& Configuration::getStopWordPathList(){
    return _stop_word_path_list;
}


Configuration::Configuration(const string& config_path)
    : _config_path(config_path)
    {}

// 根据 config_path 读配置文件，并且根据配置文件初始化 _path_list 和 _stop_word_path_list
void readConfig(){
    ifstream ifs(_config_path);
    if(!ifs){ cerr << "open file error: " << _config_path << endl; return; }

    string line;
    while(getline(ifs, line)){

    }
}

