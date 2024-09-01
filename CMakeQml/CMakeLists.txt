cmake_minimum_required(VERSION 3.16)

project(CMakeQml VERSION 0.1 LANGUAGES CXX)


#  设置QT find qt脚本的路径
set(Qt6_DIR "D:/qt/6.8.0/msvc2022_64/lib/cmake/Qt6")
# 如果采用非Qt Creator开发，需要通过告知Qt的安装路径，建议把Qt的安装路径设置到环境变量
# 例如：QT_DIR=D:\Qt\6.1.2\msvc2019_64
set(CMAKE_PREFIX_PATH "D:/qt/6.8.0/msvc2022_64")

# 有些项目会动态生成头文件，项目中需要引入它，因此需要将output目录也include进来
# 等同于INCLUDE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt6 对C++版本推荐至少17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt特有的编译器需要打开，默认是关闭的
set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

find_package(Qt6 REQUIRED COMPONENTS Quick Core Qml LinguistTools )

# 集成源码以及资源并打包
aux_source_directory(src SRC_LIST)
qt6_add_resources(QML_QRC qml.qrc)

set(PROJECT_SOURCES ${SRC_LIST} ${QML_QRC})

# qt_add_executable(${CMAKE_PROJECT_NAME} 
#     src/main.cpp
# )
add_executable(${PROJECT_NAME} "src/main.cpp" ${PROJECT_SOURCES})

# #Qt 6 中用于将 QML 模块添加到 CMake 项目中的一个命令。它简化了 QML 文件的集成，
# #使得 QML 文件可以像 C++ 文件一样被管理和构建。
qt_add_qml_module(${CMAKE_PROJECT_NAME} 
    URI CMakeQml
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/qml
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Core
)


# 加入新qml文件能自动扫描到并集成到项目
qt_import_qml_plugins(${CMAKE_PROJECT_NAME})