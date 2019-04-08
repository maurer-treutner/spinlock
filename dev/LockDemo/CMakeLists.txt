set(TARGET_NAME SpinLock)

add_library(${TARGET_NAME}
    src/SpinLock.cxx
)

target_include_directories(${TARGET_NAME} PUBLIC include)