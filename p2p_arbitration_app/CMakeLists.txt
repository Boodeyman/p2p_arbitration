cmake_minimum_required(VERSION 3.5)

project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)
find_package(CURL REQUIRED)

set(PROJECT_SOURCES
        binance.h
        binance.cpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        scraper.h
        scraper.cpp
)

include_directories(/opt/homebrew/include)

if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
    qt_add_executable(p2p_arbitration_app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icons/ADAUSDT.png icons/ATOMUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/ETHUSDT.png icons/SOLUSDT.png icons/XRPUSDT.png
        resources.qrc
        icons/exit.png
        icons/ADAUSDT.png icons/ATOMUSDT.png icons/AVAXUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/DOTUSDT.png icons/ETHUSDT.png icons/exit.png icons/ICPUSDT.png icons/LTCUSDT.png icons/MATICUSDT.png icons/NEARUSDT.png icons/SHIBUSDT.png icons/SOLUSDT.png icons/TRXUSDT.png icons/UNIUSDT.png icons/XRPUSDT.png
    )
else()
    if(ANDROID)
        add_library(p2p_arbitration_app SHARED ${PROJECT_SOURCES})
    else()
        add_executable(p2p_arbitration_app ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network CURL::libcurl)

include(GNUInstallDirs)
install(TARGETS p2p_arbitration_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(p2p_arbitration_app)
endif()










# cmake_minimum_required(VERSION 3.5)

# project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# set(PROJECT_SOURCES
#         binance.h
#         binance.cpp
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#         mainwindow.ui
# )

# include_directories(/opt/homebrew/include)

# if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
#     qt_add_executable(p2p_arbitration_app
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#         icons/ADAUSDT.png icons/ATOMUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/ETHUSDT.png icons/SOLUSDT.png icons/XRPUSDT.png
#         resources.qrc
#         icons/exit.png
#         scraper.h scraper.cpp

#     )
# else()
#     if(ANDROID)
#         add_library(p2p_arbitration_app SHARED ${PROJECT_SOURCES})
#     else()
#         add_executable(p2p_arbitration_app ${PROJECT_SOURCES})
#     endif()
# endif()

# target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

# include(GNUInstallDirs)
# install(TARGETS p2p_arbitration_app
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(p2p_arbitration_app)
# endif()
