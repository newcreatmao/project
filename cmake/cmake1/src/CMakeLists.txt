aux_source_directory (. SRC_LIST)

include_directories (../include)


# 查找WiringPi库
find_library(WIRINGPI_LIB wiringPi)

# 添加可执行文件
add_executable(use main.cpp)

# 链接WiringPi库
target_link_libraries(use ${WIRINGPI_LIB})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)