cmake_minimum_required(VERSION 3.30)

project(textify_project)

# Including FetchContent
include(FetchContent)

# Declaring FetchContent
FetchContent_Declare(
    PDCurses
    GIT_REPOSITORY https://github.com/scivision/PDCurses.git
    GIT_TAG cmake
)

# Fetching PDCurses
FetchContent_MakeAvailable(PDCurses)



# Setting Executable sources
set(SOURCES
    src/main.cpp
    src/global_func.cpp
    src/editor.cpp
)

# Creating the executable
add_executable(textify ${SOURCES})

# Linking Libraries and Includes
target_link_libraries(textify PRIVATE pdcurses)
target_include_directories(textify PRIVATE ${PDCURSES_INCLUDE_DIRS})

