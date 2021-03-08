#v1.0 copyright Comine.com 20201126R2234
#
#
#   
#       $ mkdir build
#       $ cd build
#       $ cmake <directory>  -DCMAKE_INSTALL_PREFIX=<targetdir>
#       $ cmake --build . --config Release --target install
#

cmake_minimum_required(VERSION 3.16)

########################################
# Project
########################################
project(Main)
file(GLOB msource "*.h" "*.cpp")
add_executable(Main ${msource} )
install(TARGETS Main DESTINATION bin)
set_property(TARGET Main PROPERTY
             MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# add_library(MainLib STATIC ${msource})
# install(TARGETS MainLib DESTINATION lib)

# add_library(MainDll SHARED ${msource})
# install(TARGETS Main MainDll DESTINATION bin)



