# Указание минимальной версии CMake
cmake_minimum_required(VERSION 3.5)

# Установка имени и версии проекта
project(p2p_arbitration_app VERSION 0.1 LANGUAGES CXX)

# Включение автоматической обработки UI, MOC и RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройки для создания macOS-бандла
set(MACOSX_BUNDLE TRUE)
set(MACOSX_BUNDLE_BUNDLE_NAME "p2p_arbitration_app")
set(MACOSX_BUNDLE_ICON_FILE "icon_of_app.ico")

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon_of_app.ico")
set(proxies_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/proxies.txt")
set(database_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/users.db")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${proxies_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
set_source_files_properties(${database_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Поиск Qt и необходимых компонентов
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network Sql)
find_package(CURL REQUIRED)

# Проверка найденных версий
message(STATUS "Using Qt version: ${Qt${QT_VERSION_MAJOR}_VERSION}")
message(STATUS "CURL found: ${CURL_FOUND}")

set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# Источники проекта
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
    # ${CMAKE_CURRENT_SOURCE_DIR}/resources/proxies.txt
    # ${CMAKE_CURRENT_SOURCE_DIR}/resources/users.db

)

# Указание директорий для include
include_directories(/opt/homebrew/include)

# Проверка версии Qt и добавление исполняемого файла
if(${QT_VERSION_MAJOR} VERSION_GREATER_EQUAL 6)
    qt_add_executable(p2p_arbitration_app
        MACOSX_BUNDLE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        icons/exit.png
        hoverbutton.h hoverbutton.cpp
        icons/hoverbuttonicon.png
        icons/logout.png
        icons/interface.png
        icons/logout_1.png
        icons/icon_of_app.png
        icons/icon_of_app_1.png
        icons/dark.png
        icons/light.png
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

# Линковка с библиотеками Qt и CURL
target_link_libraries(p2p_arbitration_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Sql CURL::libcurl)

# Директории для установки
# include(GNUInstallDirs)
#[[set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE)]] #"/Users/Admin/Desktop/HSE/p2p_fullparsing/build-p2p_arbitration_app-Desktop_arm_darwin_generic_mach_o_64bit-Release")]]

install(TARGETS p2p_arbitration_app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
)

# Копирование файлов ресурсов в пакет приложения
# install(FILES
#     ${CMAKE_CURRENT_SOURCE_DIR}/resources/proxies.txt
#     ${CMAKE_CURRENT_SOURCE_DIR}/resources/users.db
#     DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/p2p_arbitration_app.app/Contents/Resources"
# )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(p2p_arbitration_app)
endif()
