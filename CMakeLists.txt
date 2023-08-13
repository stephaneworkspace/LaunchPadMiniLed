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

target_link_libraries(launch_pad_mini_led PRIVATE rtmidi)
