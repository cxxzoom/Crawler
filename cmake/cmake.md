# log cmake
## tutorial1
```text
目录文件：
tutorial1/
         main.cpp
         CMakeLists.txt

配置CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(tutorial1)
add_executable(main main.cpp)

编译前准备(现在和tutorial1同级)
mkdir cmake1
cd cmake1
cmake ../tutorial1
cmake --build .

// 上面的构建方式是为了，将构建的文件放在一个文件夹里面，而非当前文件同级
总结：
设置cmake最低版本要求
设置项目名
设置编译的文件


// 配置c++的版本

set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True)

// 设置cxx的版本
// 是否要求cxx的版本

note: 设置版本一定要放在 add_executable() 的前面
```

