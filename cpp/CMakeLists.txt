message( "awv/cpp" )
message( "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH} " )


add_executable(awave
               main.cpp
               amainwindow.cpp
               namedialog.cpp
               parmstore.cpp
               modelbuilder.cpp
               layeredbuilder.cpp
               faultbuilder.cpp
               buildermanager.cpp
               typedialog.cpp
               parmdialog.cpp
               materialdialog.cpp
               materialstore.cpp
)

add_executable(btest
               bmain.cpp
               bmainwindow.cpp
)
add_executable(ctest
               cmain.cpp
               cmainwindow.cpp
)

message( "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR} " )

#target_include_directories( awave PRIVATE ${CMAKE_SOURCE_DIR}/include Qt6::Widgets)
#target_include_directories( btest PRIVATE ${CMAKE_SOURCE_DIR}/include Qt6::Widgets)
#target_link_directories(awave PRIVATE Qt6:Widgets)
#target_link_directories(btest PRIVATE Qt6:Widgets)
target_link_libraries(awave PUBLIC Qt6::Widgets)
target_link_libraries(btest PUBLIC Qt6::Widgets)
target_link_libraries(ctest PUBLIC Qt6::Widgets)
