set(TARGET_NAME SpinLockExample)

message("CMAKE_PREFIX_PATH =  ${CMAKE_PREFIX_PATH}")

find_package(Boost REQUIRED Timer)

add_executable(${TARGET_NAME}
    src/SimpleDemo.cxx
)

target_link_libraries(${TARGET_NAME} SpinLock ${Boost_LIBRARIES})

target_include_directories(${TARGET_NAME} PUBLIC include)

install(TARGETS SpinLockExample RUNTIME DESTINATION bin)