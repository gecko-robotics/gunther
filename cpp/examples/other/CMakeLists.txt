cmake_minimum_required(VERSION 3.22.0)
project(test VERSION 0.0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(PROJECT_IS_TOP_LEVEL)
    cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
    cmake_host_system_information(RESULT OSN QUERY OS_NAME)
    cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
    cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

    message(STATUS "-------------------------------------")
    message(STATUS "  Project: ${PROJECT_NAME}")
    message(STATUS "  Version: ${CMAKE_PROJECT_VERSION}")
    message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
    message(STATUS "-------------------------------------")
    message(STATUS " ${HOST}")
    message(STATUS " ${OSN}: ${OS_VERSION}")
    message(STATUS " ${PROC}")
    message(STATUS "-------------------------------------")

    # set(BUILD_EXAMPLES ON)
    # set(BUILD_TESTS ON)
else()
    message(STATUS "-> ${PROJECT_NAME} is submodule")
    # set(BUILD_EXAMPLES OFF)
    # set(BUILD_GTESTS OFF)
endif()

include(FetchContent)

# gunter -----------------
FetchContent_Declare(
    socket
#   GIT_REPOSITORY "https://github.com/gecko-robotics/gunther.git"
  GIT_REPOSITORY "https://github.com/gecko-robotics/socket.git"
  GIT_TAG "origin/main"
)
FetchContent_Declare(
    gunther
  GIT_REPOSITORY "https://github.com/gecko-robotics/gunther.git"
#   GIT_REPOSITORY "https://github.com/gecko-robotics/socket.git"
  GIT_TAG "origin/main"
)

FetchContent_MakeAvailable( gunther socket )

message(STATUS ">> src: ${socket_SOURCE_DIR}")
message(STATUS ">> bin: ${socket_BINARY_DIR}")
message(STATUS ">> populated: ${socket_POPULATED}")
message(STATUS "--------------------------------------")
message(STATUS ">> src: ${gunther_SOURCE_DIR}")
message(STATUS ">> bin: ${gunther_BINARY_DIR}")
message(STATUS ">> populated: ${gunther_POPULATED}")

LIST(APPEND APPS
    main
)

foreach(MAIN ${APPS})
    add_executable(${MAIN} ${MAIN}.cpp)
    # target_include_directories(${MAIN}
    #     INTERFACE
    #         ${gunther_SOURCE_DIR}/src
    #         ${gunther_BINARY_DIR}
    # )
    target_link_libraries(${MAIN} PRIVATE gunther socket)
    # target_link_libraries(${MAIN} PRIVATE socket)
endforeach()
