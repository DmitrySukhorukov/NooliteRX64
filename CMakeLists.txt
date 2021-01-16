cmake_minimum_required(VERSION 2.8.4)
project(NooLiteRX64)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (LINUX)
    link_libraries(usb-1.0)
else()
    include_directories(/usr/local/Cellar/libusb/1.0.21/include)
    link_libraries(/usr/local/Cellar/libusb/1.0.21/lib/libusb-1.0.0.dylib)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sources/main.cpp)
add_executable(NooLiteRX64 ${SOURCE_FILES} sources/NLSensor.cpp sources/NLSensor.h sources/NLRx64Service.cpp sources/NLRx64Service.h sources/NLServiceException.h)
