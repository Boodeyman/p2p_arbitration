cmake_minimum_required(VERSION 3.5)


project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(MACOSX_BUNDLE TRUE)
set(MACOSX_BUNDLE_BUNDLE_NAME "p2p_arbitration_app")
set(MACOSX_BUNDLE_ICON_FILE "icon_of_app.ico")

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon_of_app.ico")
set(proxies_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/proxies.txt")
set(database_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/users.db")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${proxies_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${database_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Sql)
find_package(CURL REQUIRED)


message(STATUS "Using Qt version: ${Qt${QT_VERSION_MAJOR}_VERSION}")
message(STATUS "CURL found: ${CURL_FOUND}")


set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)



set(PROJECT_SOURCES
    binance.h
    binance.cpp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    scraper.h
    scraper.cpp
    hoverbutton.h
    hoverbutton.cpp
    login_dialog.h
    login_dialog.cpp
    login_dialog.ui
    buycrypto.h
    buycrypto.cpp
    buycrypto.ui
    stylehelper.h
    stylehelper.cpp
    ${app_icon_macos}
    ${proxies_macos}
    ${database_macos}
)




include_directories(/opt/homebrew/include)


if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
    qt_add_executable(p2p_arbitration_app
        MACOSX_BUNDLE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        icons/exit.png
        hoverbutton.h hoverbutton.cpp
        proxies.txt
        icons/icon_of_app.png
        icons/icon_of_app_1.png
        icons/dark.png
        icons/light.png
        icons/hooverDarkStatic.png icons/hooverLightStatic.png
        icons/arrowBlack.png icons/arrowWhite.png
        icons/logoutBlack.png icons/logoutWhite.png
        icons/homeBlack.png icons/homeWhite.png
        icons/searchHover.png
        icons/light.png
        resources/icon_of_app.ico
        resources/users.db
        resources/proxies.txt
    )
else()
    if(ANDROID)
        add_library(p2p_arbitration_app SHARED ${PROJECT_SOURCES})
    else()
        add_executable(p2p_arbitration_app ${PROJECT_SOURCES})
    endif()
endif()


target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql CURL::libcurl)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

install(TARGETS p2p_arbitration_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)


install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/proxies.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/users.db
    DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/p2p_arbitration_app.app/Contents/Resources"
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(p2p_arbitration_app)
endif()
