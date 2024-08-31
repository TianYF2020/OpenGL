#cmake版本
cmake_minimum_required(VERSION 3.5.1)

#项目名称
project(OpenGLTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#采用C++11标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#添加所有的源文件
SET(Minesweeper_SOURCES 
	dialog.cpp	
	main.cpp 
	mainwindow.cpp 
	minemap.cpp
	myitem.cpp
	myscene.cpp
	setpro.cpp
)

#添加所有的头文件
SET(Minesweeper_HEADERS 
	dialog.h
	mainwindow.h
	minemap.h
	myitem.h
	myscene.h
	setpro.h
)

#添加所有的.ui文件
SET(Minesweeper_FORMS 
	dialog.ui
	mainwindow.ui
	setpro.ui
)

#添加资源文件
SET(Minesweeper_RESOURCES 
	img.qrc
)
#调用预编译器moc，需要使用 QT5_WRAP_CPP宏
QT5_WRAP_CPP(Minesweeper_HEADERS_MOC ${Minesweeper_HEADERS})
#使用uic处理.ui文件
QT5_WRAP_UI(Minesweeper_FORMS_HEADERS ${Minesweeper_FORMS})
#使用rcc处理.qrc文件
QT5_ADD_RESOURCES(Minesweeper_RESOURCES_RCC ${Minesweeper_RESOURCES})

#这些生成的中间文件都会在build目录下，这样的话，编译器则不能定位由uic程序产生的诸如_ui_mainwindow.h等文件。所以，我们需要把build目录添加到包含目录中
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#生成可执行文件
ADD_EXECUTABLE(Minesweeper 
	${Minesweeper_SOURCES} 
	${Minesweeper_HEADERS_MOC} 
    ${Minesweeper_FORMS_HEADERS}
	${Minesweeper_RESOURCES_RCC} 
)

#为target添加需要链接的共享库
TARGET_LINK_LIBRARIES(Minesweeper ${Qt5Widgets_LIBRARIES})
