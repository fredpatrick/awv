message( "wrk/awv/CMakeLists.txt " )
cmake_minimum_required(VERSION 3.16)

project(awave VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /home/fredpatrick/Qt/6.5.0/gcc_64)
set(VERBOSE=1)
set(CMAKE_VERBOSE_MAKEFILE=1)

message( " CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR} " )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory( cpp)
#add_subdirectory( include)

target_include_directories( awave PRIVATE ${CMAKE_SOURCE_DIR}/include )
target_include_directories( btest PRIVATE ${CMAKE_SOURCE_DIR}/include )


target_link_libraries(awave  PRIVATE Qt6::Widgets)

#set_target_properties(awave PROPERTIES
#    WIN32_EXECUTABLE ON
#    MACOSX_BUNDLE ON
#)
