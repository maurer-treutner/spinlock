set(TARGET_NAME SpinLockExample)

add_executable(${TARGET_NAME}
    src/SimpleDemo.cxx
)

target_link_libraries(${TARGET_NAME} SpinLock)

target_include_directories(${TARGET_NAME} PUBLIC include)