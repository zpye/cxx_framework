# export library
find_package(Git QUIET)

macro(git_hash hash)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
            OUTPUT_VARIABLE ${hash}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
    endif(GIT_FOUND)
endmacro()

macro(git_branch branch)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} symbolic-ref -q --short HEAD
            OUTPUT_VARIABLE ${branch}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )
    endif(GIT_FOUND)
endmacro()

string(TIMESTAMP timestamp "%Y-%m-%d %H:%M:%S")
message(STATUS "timestamp is ${timestamp}")

set(hash "")
git_hash(hash)
message(STATUS "Git hash is ${hash}")

set(branch "")
git_branch(branch)
message(STATUS "Git branch is ${branch}")

set(export_h "Export.h")
set(export_cpp "Export.cpp")

# generate export files
configure_file(${export_h}.in ${export_h} @ONLY)
configure_file(${export_cpp}.in ${export_cpp} @ONLY)