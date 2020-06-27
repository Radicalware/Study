cmake_minimum_required(VERSION 3.16)

SET(THIS EXECUTABLE)

# -------------------------- PRE-CONFIG -------------------------------------------------

SET(RADICAL_BASE "${CMAKE_CURRENT_SOURCE_DIR}/../../Cmake/Radicalware")
set(RADICAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../Cmake/Modules")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Algo")

include("${RADICAL_PATH}/Radical-App-Config.cmake")

# -------------------------- BUILD ------------------------------------------------------

project (${THIS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

SET(SOLUTION "${CMAKE_CURRENT_SOURCE_DIR}/Solution")
SUBDIRLIST(SOLUTION_FILES "${SOLUTION}")

add_executable(${THIS} ${SOLUTION_FILES})

find_package(re2)

find_package(Nexus)
find_package(xvector)
find_package(xstring)
find_package(xmap)
find_package(OS)
find_package(SYS)
find_package(Timer)

find_package(Algo)

target_link_libraries(${THIS}
    
    Radical_Mod::re2

    Radical::Nexus
    Radical::xvector
    Radical::xstring
    Radical::xmap
    Radical::OS
    Radical::SYS
    Radical::Timer

    Example::Algo
)


# -------------------------- POST-CONFIG ------------------------------------------------

#include("${RADICAL_PATH}/Radical-App-Install.cmake")
CONFIGURE_VISUAL_STUDIO_SOLUTION(${SOLUTION_FILES})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------- END --------------------------------------------------------
