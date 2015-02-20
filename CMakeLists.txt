cmake_minimum_required(VERSION 2.8)

project(tungsten)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost COMPONENTS
    program_options system unit_test_framework python thread)
find_package(GMP)
find_package(MPFR)
find_package(Readline)
find_package(PythonLibs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

include_directories(src)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${GMP_INCLUDE_DIR})
include_directories(SYSTEM ${MPFR_INCLUDES})
include_directories(SYSTEM ${READLINE_INCLUDE_DIR})
include_directories(SYSTEM ${PYTHON_INCLUDE_DIRS})

aux_source_directory(src/ast          SRC_AST_SOURCES)
aux_source_directory(src/eval         SRC_EVAL_SOURCES)
aux_source_directory(src/eval/builtin SRC_EVAL_BUILTIN_SOURCES)
aux_source_directory(src/io           SRC_IO_SOURCES)
aux_source_directory(src/io/graphics  SRC_IO_GRAPHICS_SOURCES)
aux_source_directory(src/math         SRC_MATH_SOURCES)
aux_source_directory(src/util         SRC_UTIL_SOURCES)

aux_source_directory(ut                UT_ROOT_SOURCES)
aux_source_directory(ut/ast            UT_AST_SOURCES)
aux_source_directory(ut/eval           UT_EVAL_SOURCES)
aux_source_directory(ut/eval/builtin   UT_EVAL_BUILTIN_SOURCES)
aux_source_directory(ut/io             UT_IO_SOURCES)
aux_source_directory(ut/io/graphics    UT_IO_GRAPHICS_SOURCES)
aux_source_directory(ut/math           UT_MATH_SOURCES)
aux_source_directory(ut/util           UT_UTIL_SOURCES)

aux_source_directory(html              HTML_SOURCES)

aux_source_directory(bin               BIN_SOURCES)

set(SRC_SOURCES
    ${SRC_AST_SOURCES}
    ${SRC_EVAL_SOURCES}
    ${SRC_EVAL_BUILTIN_SOURCES}
    ${SRC_IO_SOURCES}
    ${SRC_IO_GRAPHICS_SOURCES}
    ${SRC_MATH_SOURCES}
    ${SRC_UTIL_SOURCES})

set(UT_SOURCES
    ${UT_ROOT_SOURCES}
    ${UT_AST_SOURCES}
    ${UT_EVAL_SOURCES}
    ${UT_EVAL_BUILTIN_SOURCES}
    ${UT_IO_SOURCES}
    ${UT_IO_GRAPHICS_SOURCES}
    ${UT_MATH_SOURCES}
    ${UT_UTIL_SOURCES})

add_executable(tungsten ${SRC_SOURCES} ${BIN_SOURCES})
target_link_libraries(tungsten
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    ${Boost_LIBRARIES}
    ${READLINE_LIBRARY})

add_executable(unitTest ${SRC_SOURCES} ${UT_SOURCES})
target_link_libraries(unitTest
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    ${Boost_LIBRARIES}
    ${READLINE_LIBRARY})

add_library(pytungsten SHARED ${SRC_SOURCES} ${HTML_SOURCES})
target_link_libraries(pytungsten
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    ${Boost_LIBRARIES}
    ${READLINE_LIBRARY}
    ${PYTHON_LIBRARIES})

