cmake_minimum_required(VERSION 3.5.2 FATAL_ERROR)

project(encryptionLib)

# Download build system
set(CMAKESPARK_VERSION "3.0.2" CACHE STRING "CMakeSpark version")
if(NOT EXISTS "${CMAKE_BINARY_DIR}/buildsys/v${CMAKESPARK_VERSION}")
    message(STATUS "Downloading buildsystem...")

    set(CMAKESPARK_ARCHIVE ${CMAKE_BINARY_DIR}/buildsys/cmakespark-${CMAKESPARK_VERSION}.zip)
    file(DOWNLOAD "https://github.com/cmakespark/cmake/releases/download/v${CMAKESPARK_VERSION}/cmakespark.zip" ${CMAKESPARK_ARCHIVE} SHOW_PROGRESS)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/buildsys/v${CMAKESPARK_VERSION})
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar vxzf ${CMAKESPARK_ARCHIVE}
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/buildsys/v${CMAKESPARK_VERSION} )
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}/buildsys/v${CMAKESPARK_VERSION}")

# Download dependencies automatically when conan is installed
find_program(CONAN NAMES conan)
if (CONAN)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                      "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(CONANFILE conanfile.py
                    BASIC_SETUP CMAKE_TARGETS KEEP_RPATHS
                    BUILD missing)
endif()


# Include common cmake modules
include(CommonConfig)

# Include required Qt libraries and include directories
find_package(Qt6Core REQUIRED)
#find_package(Qt6Network REQUIRED)

if(WIN32)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
    set(ZLIB_USE_STATIC_LIBS TRUE) #??
    find_package(OpenSSL REQUIRED)
    find_package(ZLIB REQUIRED)
endif(WIN32)

add_subdirectory(src)
#add_subdirectory(tests)
