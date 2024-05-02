cmake_minimum_required(VERSION 3.22)
project(p2p_arbitration_cpp)

set(CMAKE_CXX_STANDARD 14)

# Include directories for nlohmann-json headers
include_directories(/opt/homebrew/include)

# Add executable target
add_executable(p2p_arbitration_cpp binance_cpp.cpp)

# Find and link with libcurl
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(p2p_arbitration_cpp ${CURL_LIBRARIES})
endif()
