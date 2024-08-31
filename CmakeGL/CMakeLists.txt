#
cmake_minimum_required(VERSION 3.12)


# set(PROJECT_PATH, ${PROJECT_SOURCE_DIR}/..)
#projects name 
project(OpenGLCmake)

# 添加 src 文件夹中的源码
add_subdirectory(src)

# 添加第三方库
include_directories(lib)

#set C++ version
set(CMAKE_CXX_STANDARD_VERSION 17)

#设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_PATH}/output)

include_directories(path/to/include/dir)

# set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
# 添加着色器路径
add_definitions(-DSHADERS_PATH="${CMAKE_SOURCE_DIR}/shaders")

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

# 设置动态库的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# 设置静态库的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)



# 将CMake生成的中间文件放入cmakedir目录中
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cmakedir)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 重新定义默认的CMake输出目录
set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_SOURCE_DIR})
set()


#set output file name
add_executable(glStudy main.cpp)


set_property(TARGET ${PROJECT_NAME} PROPERTY ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
set_property(TARGET ${PROJECT_NAME} PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# install(TARGETS MyLib
#         EXPORT MyLibTargets 
#         LIBRARY DESTINATION lib  # 动态库安装路径
#         ARCHIVE DESTINATION lib  # 静态库安装路径
#         RUNTIME DESTINATION bin  # 可执行文件安装路径
#         PUBLIC_HEADER DESTINATION include  # 头文件安装路径
#         )
#         PROJECT_SOURCE_DIR：工程的根目录
 
#         PROJECT_BINARY_DIR：运行cmake命令的目录，通常为${PROJECT_SOURCE_DIR}/build
         
#         PROJECT_NAME：返回通过 project 命令定义的项目名称
         
#         CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
         
#         CMAKE_CURRENT_BINARY_DIR：target 编译目录
         
#         CMAKE_CURRENT_LIST_DIR：CMakeLists.txt 的完整路径
         
#         EXECUTABLE_OUTPUT_PATH：重新定义目标二进制可执行文件的存放位置
         
#         LIBRARY_OUTPUT_PATH：重新定义目标链接库文件的存放位置



# #设置变量
# set(OPENCV_DLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/OpenCV/bin)
# # 设置输出目录
# set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMakeProjectTestDebug/")
# set(EXECUTABLE_OUTPUT_PATH "${OUTPUT_PATH}/bin/")
# set(LIBRARY_OUTPUT_PATH "${OUTPUT_PATH}/lib/")   
# # 拷贝文件到exe所在的目录
# # 1 拷贝文件夹里的文件
# file(COPY ${OPENCV_DLL_DIR}/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})
# # 2 拷贝bin文件
# file(COPY ${OPENCV_DLL_DIR} DESTINATION ${EXECUTABLE_OUTPUT_PATH})