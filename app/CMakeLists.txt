cmake_minimum_required(VERSION 3.21.1)

#set project name
project(StockFetch)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_OSX_ARCHITECTURES arm64)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g -O1 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1 -fno-omit-frame-pointer")

#Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#add additional include directories
include_directories(/opt/**, /opt/local/libexec/qt6/lib/QtWidgets.framework/Versions/A
                    , /opt/local/include, /usr/local/include)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${JANSSON_INCLUDE_DIRS})
include_directories(./libs, ./libs/**)

#Find the QtWidgets library
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
#find_package(Jansson REQUIRED)
#find_package(JANSSON_LIBRARY NAMES jansson PATHS ./libs)
#find_library(JANSSON_LIBRARY NAMES jansson PATHS /usr/local/lib)

#Tell Cmake to create the executable 
add_executable(StockFetch order.cpp json.c
               SQL_create.c SQL_read.c free.c
               Stock_Data.c app.cpp logger.c
               json_parse_active.c json_parse_sentiment.c
               mainwindow.cpp sidebar.cpp jsonParseCurrencies.c)

#Link the Widgets module from Qt6 
#link_directories(/usr/local/lib)
target_link_libraries(StockFetch Qt6::Widgets ${CURL_LIBRARIES} ${JANSSON_LIBRARY} ${SQLite3_LIBRARIES})
