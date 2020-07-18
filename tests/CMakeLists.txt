cmake_minimum_required(VERSION 3.8.2)

# ------------------------ FETCH GTEST LIBRARY ------------------------

include(${PROJECT_SOURCE_DIR}/cmake/googletest.cmake)
fetch_googletest(
  ${PROJECT_SOURCE_DIR}/cmake
  ${PROJECT_BINARY_DIR}/googletest
)

# ------------------------ FILES ------------------------

set(TEST_FILES
  lexer-test.cc
  parser-test.cc
  engine-test.cc
)

# ------------------------ TESTS ------------------------

add_executable(
  unit_tests
  ${TEST_FILES}
)

target_link_libraries(
  unit_tests
  gtest_main
  ${LIB_NAME}
)


add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)