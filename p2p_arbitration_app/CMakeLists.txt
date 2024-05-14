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

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(p2p_arbitration_app
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# # Define target properties for Android with Qt 6 as:
# #    set_property(TARGET p2p_arbitration_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# else()
#     if(ANDROID)
#         add_library(p2p_arbitration_app SHARED
#             ${PROJECT_SOURCES}
#         )
# # Define properties for Android with Qt 5 after find_package() calls as:
# #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(p2p_arbitration_app
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()

# find_package(CURL REQUIRED)
# if(CURL_FOUND)
#     include_directories(${CURL_INCLUDE_DIRS})
#     target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${CURL_LIBRARIES})
# else()
#     target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# endif()

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# if(${QT_VERSION} VERSION_LESS 6.1.0)
#   set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.p2p_arbitration_app)
# endif()
# set_target_properties(p2p_arbitration_app PROPERTIES
#     ${BUNDLE_ID_OPTION}
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# include(GNUInstallDirs)
# install(TARGETS p2p_arbitration_app
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(p2p_arbitration_app)
# endif()


# cmake_minimum_required(VERSION 3.5)

# project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Ensuring that Qt Widgets and Network are found
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

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(p2p_arbitration_app
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#         icons/ADA.png icons/ATOM.png icons/BNB.png icons/BTC.png icons/DOGE.png icons/ETH.png icons/SOL.png icons/XRP.png
#     )
# else()
#     if(ANDROID)
#         add_library(p2p_arbitration_app SHARED
#             ${PROJECT_SOURCES}
#         )
#     else()
#         add_executable(p2p_arbitration_app
#             ${PROJECT_SOURCES}
#         )
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

set(PROJECT_SOURCES
        binance.h
        binance.cpp
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

include_directories(/opt/homebrew/include)

if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
    qt_add_executable(p2p_arbitration_app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icons/ADAUSDT.png icons/ATOMUSDT.png icons/BNBUSDT.png icons/BTCUSDT.png icons/DOGEUSDT.png icons/ETHUSDT.png icons/SOLUSDT.png icons/XRPUSDT.png
        resources.qrc
    )
else()
    if(ANDROID)
        add_library(p2p_arbitration_app SHARED ${PROJECT_SOURCES})
    else()
        add_executable(p2p_arbitration_app ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

include(GNUInstallDirs)
install(TARGETS p2p_arbitration_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(p2p_arbitration_app)
endif()


