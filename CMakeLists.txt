#v1.0 copyright Comine.com 20201201T2333
cmake_minimum_required(VERSION 3.1.6)

########################################
# Project
########################################
project(Main)
file(GLOB msource "*.h" "*.cpp")
add_executable(MDriveReadWriteZero ${msource} )
install(TARGETS MDriveReadWriteZero DESTINATION bin)


