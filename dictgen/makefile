# 定义编译器
CXX = g++

# 定义编译选项，-I 用于指定头文件目录
CXXFLAGS = -Wall -Iinclude -std=c++11

# 指定源文件目录和目标文件目录
SRC_DIR = src
BIN_DIR = bin

# 可执行文件名
TARGET = $(BIN_DIR)/DictProducer

# 源文件列表
SRCS = $(SRC_DIR)/DictProducer.cpp $(SRC_DIR)/Configuration.cpp

# 对象文件列表，替换源文件目录和扩展名
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# 默认目标
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 通用规则生成对象文件
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(BIN_DIR)/*.o $(TARGET)

# 防止文件名与目标冲突
.PHONY: all clean

