#include <sstream>
#include <fstream>
#include <iostream>
#include "../include/Configuration.hpp"

using std::ifstream;
using std::istringstream;
using std::cerr;
using std::endl;
unordered_map<string, string>& Configuration::getPath(){
    return _paths;
}

Configuration::Configuration(const string& config_path)
    : _config_path(config_path)
{
    readConfig();
}

// 根据 config_path 读配置文件，并且根据配置文件初始化 _paths
void Configuration::readConfig(){
    ifstream ifs(_config_path);
    if(!ifs){ cerr << "open file error: " << _config_path << endl; return; }

    string line;
    while(getline(ifs, line)){
        string filename, filepath;
        istringstream iss(line);
        iss >> filename >> filepath;
            _paths[filename] = filepath;
    }
    ifs.close();
}

