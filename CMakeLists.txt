cmake_minimum_required(VERSION 3.10)
project(casino_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(Casino ${SOURCES})

#add_executable(Casino main.cpp ${SOURCES} src/BigText.cpp)
#Immer erst neue Datei hier einfügen, dann aktualisieren und dann wieder nur noch Sources starten.

