cmake_minimum_required(VERSION 3.14)

#set project name
project(StockFetch)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_OSX_ARCHITECTURES arm64)

#Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(Jansson_DIR "/usr/local/lib")


#add additional include directories
include_directories(/opt/**, /opt/local/libexec/qt6/lib/QtWidgets.framework/Versions/A
                    , /opt/local/include, /usr/local/include)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${JANSSON_INCLUDE_DIRS})

#Find the QtWidgets library
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
#find_package(Jansson REQUIRED)
find_library(JANSSON_LIBRARY NAMES jansson PATHS /usr/local/lib)
if(NOT JANSSON_LIBRARY)
    message(FATAL_ERROR "Jansson library not found")
endif()

#Tell Cmake to create the executable executable
add_executable(StockFetch order.cpp json_read_stocks.c
               SQL_create.c SQL_read.c free.c
               Stock_Data.c interface.cpp)

#Link the Widgets module from Qt6 
link_directories(/usr/local/lib)
target_link_libraries(StockFetch Qt6::Widgets ${CURL_LIBRARIES} ${JANSSON_LIBRARY} ${SQLite3_LIBRARIES})
message(STATUS "Jansson library: ${JANSSON_LIBRARY}")