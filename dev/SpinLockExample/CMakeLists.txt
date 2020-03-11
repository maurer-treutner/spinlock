set(TARGET_NAME SpinLockExample)

message("CMAKE_PREFIX_PATH =  ${CMAKE_PREFIX_PATH}")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(${TARGET_NAME}
    src/SimpleDemo.cxx
    src/SpinLock.cxx
)

target_link_libraries(${TARGET_NAME} boost_timer pthread)

target_include_directories(${TARGET_NAME} PUBLIC include)

install(TARGETS SpinLockExample RUNTIME DESTINATION bin)