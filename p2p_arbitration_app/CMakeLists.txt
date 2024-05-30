# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.5)

# Set the project name and version
project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Enable automatic handling of UI, MOC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt and required components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Sql)
find_package(CURL REQUIRED)

# Project sources
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
)

# Include directories
include_directories(/opt/homebrew/include)

# Add the executable
if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
    qt_add_executable(p2p_arbitration_app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icons/ADAUSDT.png icons/ATOMUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/ETHUSDT.png icons/SOLUSDT.png icons/XRPUSDT.png
        resources.qrc
        icons/exit.png
        icons/ADAUSDT.png icons/ATOMUSDT.png icons/AVAXUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/DOTUSDT.png icons/ETHUSDT.png icons/exit.png icons/ICPUSDT.png icons/LTCUSDT.png icons/MATICUSDT.png icons/NEARUSDT.png icons/SHIBUSDT.png icons/SOLUSDT.png icons/TRXUSDT.png icons/UNIUSDT.png icons/XRPUSDT.png
        icons/ADAUSDT.png icons/APTUSDT.png icons/ARUSDT.png icons/ATOMUSDT.png icons/AVAXUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/DOTUSDT.png icons/ETHUSDT.png icons/exit.png icons/ICPUSDT.png icons/IMXUSDT.png icons/LTCUSDT.png icons/MATICUSDT.png icons/NEARUSDT.png icons/RNDRUSDT.png icons/SHIBUSDT.png icons/SOLUSDT.png icons/TRXUSDT.png icons/UNIUSDT.png icons/WIFUSDT.png icons/XLMUSDT.png icons/XRPUSDT.png
        icons/ADAUSDT.png icons/APTUSDT.png icons/ARUSDT.png icons/ATOMUSDT.png icons/AVAXUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/DOTUSDT.png icons/ETHUSDT.png icons/exit.png icons/FLOKIUSDT.png icons/FTMUSDT.png icons/ICPUSDT.png icons/IMXUSDT.png icons/INJUSDT.png icons/LTCUSDT.png icons/MATICUSDT.png icons/NEARUSDT.png icons/OPUSDT.png icons/RNDRUSDT.png icons/RUNEUSDT.png icons/SEIUSDT.png icons/SHIBUSDT.png icons/SOLUSDT.png icons/TAOUSDT.png icons/TRXUSDT.png icons/UNIUSDT.png icons/WIFUSDT.png icons/XLMUSDT.png icons/XRPUSDT.png icons/SUIUSDT.png
        hoverbutton.h hoverbutton.cpp
        icons/hoverbuttonicon.png
        proxies.txt
        icons/logout.png
        icons/interface.png
        icons/logout_1.png
        icons/icon_of_app.png
        icons/icon_of_app_1.png
        icons/dark.png
        icons/light.png
        icons/light.png
    )
else()
    if(ANDROID)
        add_library(p2p_arbitration_app SHARED ${PROJECT_SOURCES})
    else()
        add_executable(p2p_arbitration_app ${PROJECT_SOURCES})
    endif()
endif()

# Link against Qt and CURL libraries
target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql CURL::libcurl)

# Installation directories
include(GNUInstallDirs)
install(TARGETS p2p_arbitration_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(p2p_arbitration_app)
endif()
