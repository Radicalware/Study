cmake_minimum_required(VERSION 3.10)

SET(THIS EXECUTABLE)

# -------------------------- PRE-CONFIG -------------------------------------------------

if(WIN32)
    set(RADICAL_PATH "C:/Source/CMake/Modules")
else()
    set(RADICAL_PATH "/opt/Radicalware/CMake_Modules")
endif()

include("${RADICAL_PATH}/Radical-App-Config.cmake")

project (${THIS} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../Algo")

list(APPEND CMAKE_MODULE_PATH "D:/AIE/Qt/Tools/CMake_64/share/cmake-3.19/Modules")
list(APPEND CMAKE_MODULE_PATH "D:/AIE/Qt/6.1.0/msvc2019_64/lib/cmake/Qt6Widgets")

# note: set your system/env var "QT" to "D:\AIE\Qt\6.1.0\msvc2019_64\bin"

# -------------------------- BUILD ------------------------------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

find_package(
    Qt6  COMPONENTS 
        Widgets 
        Qml 
        Quick 
        QuickControls2
        QuickTemplates2
    REQUIRED
)

SET(SOLUTION "${CMAKE_SOURCE_DIR}/Solution")

add_definitions(
    ${Qt6Widgets_DEFINITIONS} 
    ${QtQml_DEFINITIONS} 
    ${Qt6Quick_DEFINITIONS}
    ${Qt6Network_DEFINITIONS}
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt6Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_program_files(SOLUTION_FILES "${SOLUTION}")

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
find_package(Timer)

find_package(Algo)

find_package(Vulkan)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

include("D:/AIE/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_LIB_DIR "D:/AIE/vcpkg/installed/x64-windows/lib")

target_include_directories(${THIS} PRIVATE
        ${installed_projects}
)

include_directories(
    ${SOLUTION}/controller/include
    ${Qt6Widgets_INCLUDE_DIRS} 
    ${QtQml_INCLUDE_DIRS}
    "${ALGO_DIR}/include"
)

target_link_libraries(${THIS} 
    
    
    Radical::Nexus
    Radical::xvector
    Radical::xstring
    Radical::xmap

    Example::Algo
    
    Radical_Mod::re2
    
    Qt6::Widgets
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QuickTemplates2

    OpenSSL::SSL 
    OpenSSL::Crypto
)

qt_import_plugins(${THIS}
    INCLUDE  Qt6::QtLabsPlatformPlugin
)

# -------------------------- POST-CONFIG ------------------------------------------------

include("${RADICAL_PATH}/Radical-App-Install.cmake")
INSTALL_VISUAL_STUDIO_SOLUTION(${SOLUTION_FILES})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------- END --------------------------------------------------------
