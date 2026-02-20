cmake_minimum_required(VERSION 3.20)
project(scatify LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)


FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)

FetchContent_MakeAvailable(SDL3)

add_executable(scatify src/main.cpp)

target_link_libraries(scatify PRIVATE SDL3::SDL3)
target_include_directories(scatify PRIVATE src)
