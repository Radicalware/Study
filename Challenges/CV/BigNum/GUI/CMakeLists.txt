cmake_minimum_required(VERSION 3.17)

if(WIN32)
    set(RADICAL_PATH "C:/Source/CMake/Modules")
else()
    set(RADICAL_PATH "/opt/Radicalware/CMake_Modules")
endif()
include("${RADICAL_PATH}/Radical-App-Build-Qt6.cmake")

set(AlgoPath "${CMAKE_SOURCE_DIR}/../Algo")
list(APPEND CMAKE_MODULE_PATH    "${AlgoPath}")
list(APPEND InstalledIncludeDirs "${AlgoPath}/Project/include")


set(THIS ${ArgProjectName})
project(${THIS})

set(PrivateLibs "")
find_package(re2 CONFIG REQUIRED)
list(APPEND PrivateLibs "Nexus")
list(APPEND PrivateLibs "xvector")
list(APPEND PrivateLibs "xstring")
list(APPEND PrivateLibs "Macros")
list(APPEND PrivateLibs "xmap")

set(PublicLibs "")
list(APPEND PublicLibs "Timer")

find_package(Vulkan)
find_package(OpenSSL REQUIRED)

BuildRadicalQt6Solution(PrivateLibs PublicLibs)

find_package(Algo)
link_libraries(${THIS} 
    re2::re2
    OpenSSL::SSL 
    OpenSSL::Crypto
)
LinkDynamic(${THIS} "Algo")