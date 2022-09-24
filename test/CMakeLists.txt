PROJECT(GOOFY_TEST)

# 设置和兼容 cmake 版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
CMAKE_POLICY(VERSION 3.0)

# 设置兼容 gtest 版本所需的宏
# ADD_DEFINITIONS(-D_GLIBCXX_USE_CXX11_ABI=0)

# 添加头文件目录
INCLUDE_DIRECTORIES(
    ${GTEST}/include
    ${GMOCK}/include
    ${LEVELDB}/include
    ${SPDLOG}/include
    ${UUID}/include
    ${URING}/inlcude
    ${EC}/include
    ${SRC}/include
    ${SRC}/common
    ${SRC}/util
)

# 添加依赖库目录
LINK_DIRECTORIES(
    ${GTEST}/lib
    ${GMOCK}/lib
    ${LEVELDB}/lib
    ${SPDLOG}/lib
    ${UUID}/lib
    ${URING}/lib
    ${EC}/lib
)

# 添加 ut 所需源文件目录
AUX_SOURCE_DIRECTORY("ut/" UT_SOURCE)
AUX_SOURCE_DIRECTORY("${SRC}/common/" UT_SOURCE)
AUX_SOURCE_DIRECTORY("${SRC}/util/" UT_SOURCE)

# 生成 ut
ADD_EXECUTABLE(goofy_ut ${UT_SOURCE})

# 为 ut 链接动态库
TARGET_LINK_LIBRARIES(goofy_ut
    gtest
    gmock
    leveldb
    spdlog
    uuid
    uring
    ec
)

# 添加 demo 所需源文件目录
AUX_SOURCE_DIRECTORY("demo/" DEMO_SOURCE)

# 生成 demo
ADD_EXECUTABLE(goofy_demo ${DEMO_SOURCE})

# 为 demo 链接动态库
TARGET_LINK_LIBRARIES(goofy_demo
    leveldb
    spdlog
    uuid
    uring
    ec
)
