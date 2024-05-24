cmake_minimum_required(VERSION 3.14)

#set project name
project(StockFetch)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#add additional include directories
include_directories(/opt/**, /opt/local/libexec/qt6/lib/QtWidgets.framework/Versions/A)

#Find the QtWidgets library
find_package(Qt6Widgets REQUIRED)

#Tell Cmake to create the helloworld executable
add_executable(StockFetch main.cpp json_read_stocks.c
               read_file_implementation.c SQL_create.c 
               SQL_read.c Stock_Data.c)

#Link the Widgets module from Qt6 
target_link_libraries(StockFetch Qt6::Widgets)