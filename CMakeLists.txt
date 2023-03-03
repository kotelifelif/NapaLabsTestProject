# CMakeList.txt : CMake project for NapaLabsTestProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("NapaLabsTestProject")

# Add source to this project's executable.
add_executable (NapaLabsTestProject "main.cpp" "DNSCache.h" )
target_link_libraries(NapaLabsTestProject PUBLIC pthread)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NapaLabsTestProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
