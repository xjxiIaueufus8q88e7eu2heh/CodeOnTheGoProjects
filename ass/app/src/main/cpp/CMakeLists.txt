cmake_minimum_required(VERSION 3.10.2)

project("ndkactivitykotlin")

add_library(native-lib SHARED
    android/JNI.cpp
    core/Engine.cpp
    event/EventLoop.cpp
    thread/Worker.cpp
)

# OpenSSL
add_library(crypto SHARED IMPORTED)
set_target_properties(crypto PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libcrypto.so
)

add_library(ssl SHARED IMPORTED)
set_target_properties(ssl PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libssl.so
)

# libuv
add_library(uv STATIC IMPORTED)
set_target_properties(uv PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libuv/lib/${ANDROID_ABI}/libuv.a
)

target_include_directories(native-lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/openssl/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libuv/include
)

find_library(log-lib log)
find_library(dl-lib dl)
find_library(m-lib m)
find_library(log-lib log)

target_link_libraries(native-lib
    uv
    crypto
    ssl
    ${log-lib}
    ${dl-lib}
    ${m-lib}
    ${log-lib}
)