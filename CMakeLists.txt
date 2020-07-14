cmake_minimum_required(VERSION 3.8.2)

project(FormulaEngine VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# ------------------------ FILES ------------------------

set(SOURCES
  ${PROJECT_SOURCE_DIR}/src/token.cc
  ${PROJECT_SOURCE_DIR}/src/lexer.cc
  ${PROJECT_SOURCE_DIR}/src/scanner.cc
  ${PROJECT_SOURCE_DIR}/src/ast-node.cc
  ${PROJECT_SOURCE_DIR}/src/parser.cc
)

set(HEADERS
  ${PROJECT_SOURCE_DIR}/src/token.h
  ${PROJECT_SOURCE_DIR}/src/lexer.h
  ${PROJECT_SOURCE_DIR}/src/scanner.h
  ${PROJECT_SOURCE_DIR}/src/ast-node.h
  ${PROJECT_SOURCE_DIR}/src/parser.h
)

set(LIB_NAME engine)

# ------------------------ BUILD ------------------------

# LIBRARY
add_library(${LIB_NAME} "")

target_sources(
  ${LIB_NAME}
  PUBLIC
    ${HEADERS}
  PRIVATE
    ${SOURCES}
)

target_include_directories(
  ${LIB_NAME}
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/
)

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)


# EXECUTABLE
add_executable(main app/main.cc)

target_link_libraries(main PRIVATE ${LIB_NAME})

# ------------------------ PROPERTIES ------------------------

set_target_properties(
  ${LIB_NAME} main
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
)

# ------------------------ TESTS ------------------------

enable_testing()

add_subdirectory(tests)
