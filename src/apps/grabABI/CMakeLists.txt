# minimum cmake version supported
cmake_minimum_required (VERSION 2.6)

# application project
project (grabABI)

# The sources to be used
file(GLOB SOURCE_FILES "*.cpp")

# Output
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")

# Define the executable to be generated
set(TOOL_NAME "grabABI")
set(PROJ_NAME "apps")
add_executable(${TOOL_NAME} ${SOURCE_FILES})

# Add the project static libs at linking
target_link_libraries (${TOOL_NAME} ${BASE_LIBS})

# Testing
# Define paths to test folder and gold folder
set(TEST_EXE "${EXECUTABLE_OUTPUT_PATH}/${TOOL_NAME}")
set(TEST_PATH "${TEST_PATH}/${PROJ_NAME}/${TOOL_NAME}")
set(GOLD_PATH "${GOLD_PATH}/${PROJ_NAME}/${TOOL_NAME}")

# Additional target to make the README.md
build_readme(${CMAKE_CURRENT_SOURCE_DIR} ${TOOL_NAME})

# To run only specific tests we define a test configuration named "test_all"
add_custom_target(test-all COMMAND ${CMAKE_CTEST_COMMAND} -C test_all)

# Copy a test file we need for the case where the ABI is a local file
file(COPY "data/0x314159265dd8dbb310642f98f50c066173c1259c.json" DESTINATION "${GOLD_PATH}" FILE_PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ)

# Function to run an special or slow test case
function(run_special_test testName)
    run_the_special_test(${TEST_PATH} ${GOLD_PATH} ${testName} ${TEST_EXE} ${ARGN})
endfunction(run_special_test)

# Function to run an individual test case
function(run_test testName)
     run_the_test(${TEST_PATH} ${GOLD_PATH} ${testName} ${TEST_EXE} ${ARGN})
endfunction(run_test)

# Enter one line for each individual test
run_test("grabABI_README"                        "-th")
run_test("grabABI_verbose1"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -v")
run_test("grabABI_verbose2"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -v")
run_test("grabABI_noconst"                       "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -v" " -n")
run_test("grabABI_verbose3"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -vn")
run_test("grabABI_encoding"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -v" " -n" " -e")
run_test("grabABI_encoding_nv"                   "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -n" " -e")
run_test("grabABI_verbose4"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -vne")
run_test("grabABI_generation"                    "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -v" " -n" " -e" " -g" " code")
run_test("grabABI_verbose5"                      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " -vng" " code")
run_test("grabABI_invalid_1"                     "0x00001")
run_test("grabABI_not_found"                    "0x1728039ce0d18a799c081c5c7fa2090dd365a8d0" " -o")

run_test("grabABI_no_abi1"                      "0x1728039ce0d18a799c081c5c7fa2090dd365a8d0" " --raw")
run_test("grabABI_no_abi2"                       "0x1728039ce0d18a799c081c5c7fa2090dd365a8d0" " --json")

run_test("grabABI_known_prev_bug1"               "0x5901deb2c898d5dbe5923e05e510e95968a35067" " --raw")
run_test("grabABI_known_prev_bug2"               "0x5f742383b6d1298980030d6af943b76cdd902143" " --raw")
run_test("grabABI_known_prev_json_bug1"         "0x5901deb2c898d5dbe5923e05e510e95968a35067" " --json")
run_test("grabABI_known_prev_json_bug2"          "0x5f742383b6d1298980030d6af943b76cdd902143" " --json")
run_test("grabABI_local_fail"                    "0x314159265dd8dbb310642f98f50c066173c1259b")
run_test("grabABI_local_file"                    "0x314159265dd8dbb310642f98f50c066173c1259c")

run_special_test("grabABI_known_prev_bug3"       "0x6090a6e47849629b7245dfa1ca21d94cd15878ef" " --raw")
run_special_test("grabABI_known_prev_bug4"       "0x6810e776880c02933d47db1b9fc05908e5386b96" " --raw")
run_special_test("grabABI_known_prev_bug5"       "0x851b7f3ab81bd8df354f0d7640efcd7288553419" " --raw")
run_special_test("grabABI_known_prev_bug6"       "0xa68780dd261cfea0d479728db3ed318940bfa9f9" " --raw")
run_special_test("grabABI_known_prev_bug7"       "0xaaaf91d9b90df800df4f55c205fd6989c977e73a" " --raw")
run_special_test("grabABI_known_prev_bug8"       "0xe94327d07fc17907b4db788e5adf2ed424addff6" " --raw")
run_special_test("grabABI_known_prev_bug9"       "0xef638b4305b8a1620f4e0e562e127f1181ae16d2" " --raw")
run_special_test("grabABI_known_prev_bug10"      "0x012233b3c8177f0778d910ed88170b82de3bfe57" " --raw")
run_special_test("grabABI_known_prev_bug11"      "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " --raw")
run_special_test("grabABI_known_prev_json_bug3"  "0x6090a6e47849629b7245dfa1ca21d94cd15878ef" " --json")
run_special_test("grabABI_known_prev_json_bug4"  "0x6810e776880c02933d47db1b9fc05908e5386b96" " --json")
run_special_test("grabABI_known_prev_json_bug5"  "0x851b7f3ab81bd8df354f0d7640efcd7288553419" " --json")
run_special_test("grabABI_known_prev_json_bug6"  "0xa68780dd261cfea0d479728db3ed318940bfa9f9" " --json")
run_special_test("grabABI_known_prev_json_bug7"  "0xaaaf91d9b90df800df4f55c205fd6989c977e73a" " --json")
run_special_test("grabABI_known_prev_json_bug8"  "0xe94327d07fc17907b4db788e5adf2ed424addff6" " --json")
run_special_test("grabABI_known_prev_json_bug9"  "0xef638b4305b8a1620f4e0e562e127f1181ae16d2" " --json")
run_special_test("grabABI_known_prev_json_bug10" "0x012233b3c8177f0778d910ed88170b82de3bfe57" " --json")
run_special_test("grabABI_known_prev_json_bug11" "0xbb9bc244d798123fde783fcc1c72d3bb8c189413" " --json")

# Installation steps
install(TARGETS ${TOOL_NAME} RUNTIME DESTINATION bin)
