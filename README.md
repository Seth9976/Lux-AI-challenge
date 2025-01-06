# Lux AI Season 3 - C Starter Kit

这是 Lux AI S3 比赛的 C 语言版本 starter kit。

## 环境要求

- GCC 编译器 (Windows 用户建议使用 MinGW)
- Make 工具
- json-c 库
- Python 3.7+

## 安装依赖

### Linux
bash
Ubuntu/Debian
sudo apt-get install build-essential
sudo apt-get install libjson-c-dev
CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install json-c-devel


### Windows (使用 MinGW)
1. 下载并安装 MSYS2: https://www.msys2.org/
2. 打开 MSYS2 终端，安装必要的包:
bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-json-c
pacman -S make
## 编译
make
## 运行测试
make test
## 代码结构

- `src/main.c`: 程序入口点
- `src/agent.c`: AI 智能体实现
- `src/lux/`: 核心游戏逻辑和工具函数
- `test/`: 测试文件

## 内存管理

- 所有分配的内存在程序结束时都会被正确释放
- 使用 valgrind 检查内存泄漏:

valgrind --leak-check=full ./agent

## 调试

代码中包含基本的日志功能，日志输出到标准错误流。可以通过重定向来保存日志:

python main.py 2> debug.log