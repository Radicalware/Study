cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

option(san "san" OFF)
# cmake -Dsan=on ..

if(san)
    message("Sanitizing!!!")
endif()

if(san)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -fsanitize=undefined \
        -fsanitize=null \
        -fsanitize=signed-integer-overflow \
        -fsanitize=alignment \
        -fno-sanitize-recover=null \
        -fsanitize-trap=alignment \
        -fno-omit-frame-pointer \
    ")
endif()

if(san)
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} \
        -fsanitize=undefined \
        -fsanitize=null \
        -fsanitize=signed-integer-overflow \
        -fsanitize=alignment \
        -fno-sanitize-recover=null \
        -fsanitize-trap=alignment \
        -fno-omit-frame-pointer \
    ")
endif()


project(re_ex)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(libs STATIC 
    src/re.cpp
    src/ac.cpp
)

target_include_directories(libs
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
# -------------------------------------------------------
# add_library(ac_lib STATIC 
#     src/ac.cpp
# )

# target_include_directories(ac_lib
#     PUBLIC 
#         ${PROJECT_SOURCE_DIR}/include
# )


############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(main_binary 
    src/main.cpp
)

# link the new re_ex lib target with the main_binary target
target_link_libraries(main_binary
    PRIVATE 
        libs
        # ac_lib
)