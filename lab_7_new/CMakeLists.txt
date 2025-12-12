cmake_minimum_required(VERSION 3.16)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(include)


add_executable(game 
    src/main.cpp
    src/npc.cpp
    src/entities.cpp
    src/factory.cpp
    src/map.cpp
    src/battle.cpp
    src/movement.cpp
    src/observer.cpp
    src/visitor.cpp
    

    include/defs.h
    include/npc.h
    include/entities.h
    include/factory.h
    include/map.h
    include/battle.h
    include/movement.h
    include/observer.h
    include/visitor.h
    include/coro.h
)


target_link_libraries(game PRIVATE Threads::Threads)