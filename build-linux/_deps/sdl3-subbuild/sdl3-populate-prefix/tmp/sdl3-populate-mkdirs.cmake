# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-src"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-build"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/tmp"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/src"
  "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/Guilherme/Desktop/Projetos/scatify_cpp/build-linux/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
