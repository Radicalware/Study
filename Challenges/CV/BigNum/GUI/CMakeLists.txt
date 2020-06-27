cmake_minimum_required(VERSION 3.10)

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

find_package(Qt5 COMPONENTS Widgets Qml Quick QuickControls2 QuickTemplates2 REQUIRED)
include_directories(
    ${SOLUTION}/controller/include
    ${Qt5Widgets_INCLUDE_DIRS} 
    ${QtQml_INCLUDE_DIRS}
)
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${Qt5Quick_DEFINITIONS})
qt5_add_resources(QT_RESOURCES "${SOLUTION}/files.qrc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

SUBDIRLIST(SOLUTION_FILES "${SOLUTION}")

# Build the app!
add_executable(${THIS}
    ${SOLUTION_FILES}
    ${QT_RESOURCES}
    ${SOLUTION}/resource/exe/pic.rc
)


# Link the app!
find_package(re2)
find_package(Nexus)
find_package(xvector)
find_package(xstring)
find_package(xmap)
# find_package(OS)
# find_package(SYS)
find_package(Timer)

find_package(Algo)

target_link_libraries(${THIS}

    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::QuickTemplates2
    
    Radical_Mod::re2
    Radical::Nexus
    Radical::xvector
    Radical::xstring
    Radical::xmap
    # Radical::OS
    # Radical::SYS
    Radical::Timer

    Example::Algo
)

# -------------------------- POST-CONFIG ------------------------------------------------

#include("${RADICAL_PATH}/Radical-App-Install.cmake")
CONFIGURE_VISUAL_STUDIO_SOLUTION(${SOLUTION_FILES})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------- END --------------------------------------------------------
