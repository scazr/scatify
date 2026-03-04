cmake_minimum_required(VERSION 3.20)
project(scatify LANGUAGES C CXX)

include(FetchContent)

fetchcontent_declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)

fetchcontent_makeavailable(SDL3)

add_executable(scatify
	src/main.cpp
	src/SourceFoldersManager/SourceFoldersManager.cpp
	src/ErrorHandling/ReturnStatus/ReturnStatus.cpp
	src/ErrorHandling/io.cpp
)

target_compile_features(scatify PUBLIC cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(scatify PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
  )
elseif(MSVC)
  target_compile_options(scatify PRIVATE
    /W4
    /WX
  )
endif()

target_link_libraries(scatify PRIVATE SDL3::SDL3)
target_include_directories(scatify PRIVATE src)
