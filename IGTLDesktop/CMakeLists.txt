cmake_minimum_required(VERSION 2.8)
project(IGTLDesktop)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "IGTLDesktop.")
endif ()

find_package(OpenIGTLink REQUIRED)
find_library(OpenIGTLink_LIBRARY NAMES ${OpenIGTLink_LIBRARIES} PATHS ${OpenIGTLink_DIR})

set(OpenIGTLink_INCLUDES "${OpenIGTLink_DIR}/../../include/igtl")

include_directories(
  "${OpenIGTLink_INCLUDES}"
)

set(sources
  Src/main.cxx
  Src/myUtils.h
  Src/igtlClient.h
  Src/igtlServer.h
)

add_executable(IGTLDesktop ${sources})
target_link_libraries(IGTLDesktop
  ${OpenIGTLink_LIBRARY}

)



