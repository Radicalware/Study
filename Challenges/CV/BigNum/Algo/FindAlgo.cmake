cmake_minimum_required(VERSION 3.16)

set(AlgoLIB Algo)

SetLocalInstallDirs()
# -------------------------- PRE-CONFIG ---------------------------------------
set(ALGO_DIR ${CMAKE_CURRENT_LIST_DIR}/Project)
set(INC      ${ALGO_DIR}/include)
set(SRC      ${ALGO_DIR}/src)

list(APPEND InstalledIncludeDirs "${ALGO_DIR}/include")

# -------------------------- BUILD --------------------------------------------

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_SHARED_LIBS ON)

UNSET(ProjectFiles)
FindProgramFiles(ProjectFiles "${ALGO_DIR}")

# should be a MODULE instead of STATIC
# but this is just example code
add_library(${AlgoLIB} MODULE ${ProjectFiles})
add_library(Example::${AlgoLIB} ALIAS ${AlgoLIB})

target_include_directories(${AlgoLIB} PUBLIC ${InstalledIncludeDirs})
target_link_libraries(${AlgoLIB} ${PreStaticLibLst})

# -------------------------- POST-CONFIG --------------------------------------
SetVisualStudioFilters("Projects.${LIB}" "${ProjectFiles}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -------------------------- END ----------------------------------------------