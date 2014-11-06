cmake_minimum_required(VERSION 2.8)
project(IGTLMobile)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "IGTLMobile.")
endif ()

find_package(OpenIGTLink REQUIRED)
find_library(OpenIGTLink_LIBRARY NAMES ${OpenIGTLink_LIBRARIES} PATHS ${OpenIGTLink_DIR})

set(OpenIGTLink_INCLUDES "${OpenIGTLink_DIR}/../../include/igtl")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libs/${ANDROID_NDK_ABI_NAME})
add_subdirectory(jni)

# find android
find_program(ANDROID_EXECUTABLE
  NAMES android
  DOC   "The android command-line tool")
if(NOT ANDROID_EXECUTABLE)
  message(FATAL_ERROR "Can not find android command line tool: android")
endif()

set(ANDROID_TARGET "android-19"
  CACHE STRING "The Android API to target")

set(CMAKE_CXX_FLAGS "-std=c++11")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/AndroidManifest.xml"
  "${CMAKE_CURRENT_BINARY_DIR}/AndroidManifest.xml"
  COPYONLY)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/ant.properties.in"
  "${CMAKE_CURRENT_BINARY_DIR}/ant.properties"
  @ONLY)

add_custom_target(IGTLMobile-ant-configure ALL
  COMMAND "${ANDROID_EXECUTABLE}"
          update project
          --name IGTLMobile
          --path "${CMAKE_CURRENT_SOURCE_DIR}"
          --target "${ANDROID_TARGET}"
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/build.xml"
          "${CMAKE_CURRENT_BINARY_DIR}/build.xml"
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/local.properties"
          "${CMAKE_CURRENT_BINARY_DIR}/local.properties"
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/project.properties"
          "${CMAKE_CURRENT_BINARY_DIR}/project.properties"
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "${CMAKE_CURRENT_SOURCE_DIR}/proguard-project.txt"
          "${CMAKE_CURRENT_BINARY_DIR}/proguard-project.txt"
  COMMAND "${CMAKE_COMMAND}" -E remove
          "${CMAKE_CURRENT_SOURCE_DIR}/build.xml"
          "${CMAKE_CURRENT_SOURCE_DIR}/local.properties"
          "${CMAKE_CURRENT_SOURCE_DIR}/project.properties"
          "${CMAKE_CURRENT_SOURCE_DIR}/proguard-project.txt"
  WORKING_DIRECTORY
          "${CMAKE_CURRENT_BINARY_DIR}")

add_dependencies(IGTLMobile-ant-configure IGTLMobile)

#find ant
find_program(ANT_EXECUTABLE
  NAMES ant
  DOC   "The ant build tool")
if(NOT ANT_EXECUTABLE)
  message(FATAL_ERROR "Can not find ant build tool: ant")
endif()

#find adb
find_program(ADB_EXECUTABLE
  NAMES adb
  DOC   "The adb install tool")
if(NOT ADB_EXECUTABLE)
  message(FATAL_ERROR "Can not find ant build tool: adb")
endif()

add_custom_target(IGTLMobile-apk-debug ALL
  COMMAND ${ANT_EXECUTABLE}
          -file "${CMAKE_CURRENT_BINARY_DIR}/build.xml"
          debug)
add_dependencies(IGTLMobile-apk-debug
  IGTLMobile-ant-configure
  IGTLMobile)

add_custom_target(IGTLMobile-apk-uninstall ALL
        COMMAND ${ADB_EXECUTABLE} uninstall "com.ircad.test"
    )
add_dependencies(IGTLMobile-apk-uninstall
  IGTLMobile-apk-debug
  IGTLMobile-ant-configure
  IGTLMobile)
#Install current version on the device/emulator
add_custom_target(IGTLMobile-install ALL
    COMMAND ${ADB_EXECUTABLE} install -r bin/IGTLMobile-debug.apk )

add_dependencies(IGTLMobile-install
  IGTLMobile-apk-uninstall
  IGTLMobile-apk-debug
  IGTLMobile-ant-configure
  IGTLMobile)

