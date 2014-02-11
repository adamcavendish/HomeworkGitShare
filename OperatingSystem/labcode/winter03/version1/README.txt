编译方式1：
    使用Code::Blocks 13.12，打开MemoryManagement.cbp，然后编译运行

编译方式2：
    1. 使用版本大于等于4.7的MinGW/TDM-GCC进行编译。
    2. TDM-GCC链接：http://tdm-gcc.tdragon.net/
    3. 在命令行下输入g++ -std=c++0x helper_functions.cpp main.cpp -o MemoryManagement.exe进行编译

编译方式3：
    1. 使用版本大于等于2012的Visual Studio进行编译。
    2. 新建一个Console Application >> Empty Project
    3. 选择PROJECT->Add Existing Item来添加文件
    4. 添加config.hpp, helper_functions.cpp, helper_functions.hpp, main.cpp
    5. Build->Build Solution即可
