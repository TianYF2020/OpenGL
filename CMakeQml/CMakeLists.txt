cmake_minimum_required(VERSION 3.16)

project(CMakeQml VERSION 0.1 LANGUAGES CXX)


# 有些项目会动态生成头文件，项目中需要引入它，因此需要将output目录也include进来
# 等同于INCLUDE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt6 对C++版本推荐至少17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#这些配置需要写在add_subdirectory前边要不然运行时候没有生效
# 如果需要针对 Debug 和 Release 版本分别设置
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


message(STATUS "*************当前构建类型: ${CAMKE_BUILD_TYPE}")
message(STATUS "*************当前构建类型: ${CMAKE_SOURCE_DIR}")
message(STATUS "*************当前构建类型: ${${CMAKE_RUNTIME_OUTPUT_DIRECTORY}}")
add_subdirectory(MainProject)


