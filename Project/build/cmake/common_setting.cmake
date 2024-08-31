set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

#设置编译选项
set(WITH_DERoot ON CACHE BOOL "" FORCE)
set(WITH_DEPart ON CACHE BOOL "" FORCE)
set(WITH_DEUIBlock ON CACHE BOOL "" FORCE)
set(WITH_DEMain ON CACHE BOOL "" FORCE)

#QT
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Core Xml Gui)
find_package(Qt5 COMPONENTS Widgets Core Xml Gui REQUIRED)

if(CMAKE_SIZEOF_VOID_P STREQUAL 4)
    set(CKMAK_COMPILER_BITS "x86")
else()
    set(CKMAK_COMPILER_BITS "x64")
endif()

set(OUT_DIR_NAME ${CMAKE_SYSTEM_NAME}_${CMAKE_C_COMPILER_ID}_${CKMAK_COMPILER_BITS})
string(TOLOWER ${OUT_DIR_NAME} OUT_DIR_NAME)
message(STATUS "Out Dir: ${OUT_DIR_NAME}")
#设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DE_ROOT}/out/${OUT_DIR_NAME}_debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${DE_ROOT}/out/${OUT_DIR_NAME}_release/bin)
#设置共享库输出路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${DE_ROOT}/out/${OUT_DIR_NAME}_debug/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${DE_ROOT}/out/${OUT_DIR_NAME}_release/bin)
#设置静态库输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${DE_ROOT}/out/${OUT_DIR_NAME}_debug/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${DE_ROOT}/out/${OUT_DIR_NAME}_release/lib)

add_compile_definitions(_WINDOWS_SOURCE)
add_compile_definitions(QT_DEPRECATED_WARNINIGS)
#允许创建文件夹
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#将cmake创建的target放入CMakeTargets文件夹中
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

#转sln开启多核心编译
if(${CMAKE_GENERATOR} MATCHES "Visual Studio*")
    if(${MSVC_TOOLSET_VERSION} VERSION_LESS "141")
        add_compile_definition($<$<CXX_COMPILER_ID:MSVC>:Gm->) #高版本已经废弃,低版本Gm影响并行
    endif()
    cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
    add_compile_definition($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES})
endif()
