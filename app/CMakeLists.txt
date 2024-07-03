cmake_minimum_required(VERSION 3.21.1)

project(StockViewer)

set (CMAKE AUTO_MOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_OSX_ARCHITECTURES arm64)

set (CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set (Jansson_DIR "/usr/local/lib")

#find includes
set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(./libs, /opt/local/libexec/qt6/lib/QtWidgets.framework/Versions/A, 
                    /opt/local/**, /usr/local/lib)
include_directories(${JANSSON_INCLUDE_DIR})
include_directories(./libs/**)

#set app icon
set (MACOSX_BUNDLE_ICON_FILE icon.icns)
set (app_icon_macos "${CMAKE_SOURCE_DIR}/icon.icns")
set_source_files_properties (${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

#find the oacjages
find_package (Qt6 COMPONENTS Widgets REQUIRED)
find_package (CURL REQUIRED)
find_package (SQLite3 REQUIRED)
#find_package (jansson REQUIRED)
#jansson is always special for some reason
#find_library (JANSSON_LIBRARY NAMES jansson PATHS ./libs)
#find_library(JANSSON_LIBRARY NAMES jansson PATHS /usr/local/lib)

add_executable(StockViewer MACOSX_BUNDLE order.cpp json.c
                SQL_CREATE.c SQL_READ.c free.c
                Stock_Data.c app.cpp logger.c
                json_parse_active.c json_parse_sentiment.c
                mainwindow.cpp sidebar.cpp jsonParseCurrencies.c
                ${StockViewer_src} ${app_icon_macos})

set_target_properties(StockViewer PROPERTIES MACOSXBUNDLE ON)

link_directories(/usr/local/lib)

target_link_libraries(StockViewer Qt6::Widgets ${CURL_LIBRARIES} ${JANSSON_LIBRARY} ${SQLite3_LIBRARIES})

get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")
add_custom_command(TARGET StockViewer POST_BUILD COMMAND "${MACDEPLOYQT_EXECUTABLE}"
                    ARGS "StockViewer.app" "-dmg"
                    COMMENT "Execute macdeplyqt to create macos bundle")

set (APP_NAME StockViewer)

set (DIRS ${CMAKE_BINARY_DIR})
set (APPS "${CMAKE_INSTALL_PREFIX}/${APP_NAME}.app")

install(CODE "include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

