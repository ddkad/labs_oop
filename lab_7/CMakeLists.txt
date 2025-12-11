cmake_minimum_required(VERSION 3.15)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(WIN32)
    if(MSVC)
        add_compile_options(/std:c++latest)
        add_compile_options(/await)
    endif()
endif()


if(UNIX)
    add_compile_options(-fcoroutines)
endif()


set(SOURCES
    src/main.cpp
    src/npc.cpp
    src/npc_factory.cpp
    src/visitor.cpp
    src/observer.cpp
    src/fight_manager.cpp
    src/game_world.cpp
    src/coroutine_npc.cpp  
)


set(HEADERS
    include/npc.h
    include/npc_factory.h
    include/observer.h
    include/fight_manager.h
    include/game_world.h
    include/coroutine_npc.h  
    include/visitor.h
)

add_executable(lab7 ${SOURCES} ${HEADERS})


if(WIN32)
    target_compile_options(lab7 PRIVATE /EHsc)
endif()


if(UNIX AND NOT APPLE)
    target_compile_options(lab7 PRIVATE -pthread)
    target_link_libraries(lab7 pthread)
endif()