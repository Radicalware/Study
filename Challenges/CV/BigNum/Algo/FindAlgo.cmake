cmake_minimum_required(VERSION 3.16)

set(LIB Algo)

# -------------------------- PRE-CONFIG ---------------------------------------
set(ALGO_DIR ${CMAKE_CURRENT_LIST_DIR}/Project)
set(INC      ${ALGO_DIR}/include)
set(SRC      ${ALGO_DIR}/src)
# -------------------------- BUILD --------------------------------------------

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

UNSET(PROJECT_FILES)
find_program_files(PROJECT_FILES "${ALGO_DIR}")

add_library(${LIB} SHARED ${PROJECT_FILES})
add_library(Example::${LIB} ALIAS ${LIB})

target_include_directories(${LIB} PUBLIC
    ${ALGO_DIR}/include
    ${EXT_HEADER_PATH}
)

target_link_libraries(${LIB} Radical::Nexus)
target_link_libraries(${LIB} Radical::xvector)
target_link_libraries(${LIB} Radical::xstring)
target_link_libraries(${LIB} Radical::xmap)

target_link_libraries(${LIB} Radical_Mod::re2)

# -------------------------- POST-CONFIG --------------------------------------
set(PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -------------------------- END ----------------------------------------------