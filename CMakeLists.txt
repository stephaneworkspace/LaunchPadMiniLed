cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LaunchPadMiniLed)

include(FetchContent)

FetchContent_Declare(
  rtmidi
  URL https://github.com/thestk/rtmidi/archive/refs/tags/6.0.0.tar.gz
)

FetchContent_MakeAvailable(rtmidi)

#add_executable(launch_pad_mini_led Sources/Main.cpp
#        Sources/LedController.cpp
#        Sources/LedController.h
#        )
add_library(launch_pad_mini_led SHARED Sources/LedController.cpp)

# Spécifie le chemin d'inclusion pour cette bibliothèque lorsqu'elle est utilisée par d'autres projets.
target_include_directories(launch_pad_mini_led PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Include
        )

target_link_libraries(launch_pad_mini_led PRIVATE rtmidi)
