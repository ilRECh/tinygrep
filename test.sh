#!/bin/bash

# Test previous command
# Used only for the test setup
ensure_success() {
    # Execute the command
    eval $*;

    # Check the exit value
    if [ $? -ne 0 ]
    then
        echo "Something went wrong in: |" $* "|"
        exit 1
    fi
}

# Paths to the standard and custom grep utilities
STANDARD_GREP="grep -r --binary-files=text -e"
TINYGREP="./tinygrep"
BUILD_DIR="Release"

# Build the TINYGREP program
# Delete the $BUILD_DIR directory if exists
ensure_success rm -rf $BUILD_DIR
# Create the $BUILD_DIR directory
ensure_success mkdir $BUILD_DIR
# Enter the $BUILD_DIR directory, essentially the tests will run here
ensure_success cd $BUILD_DIR
# Build the program
ensure_success cmake ..
ensure_success make

# Create a temporary directory for testing
TEST_DIR="test_grep"
ensure_success mkdir -p $TEST_DIR

# Create some text files
ensure_success echo "Hello World" > $TEST_DIR/file1.txt
ensure_success echo "Hello Bash" > $TEST_DIR/file2.txt
ensure_success echo -e '\x00\x01\x02Hello\x03\x04\x05' > $TEST_DIR/file3.bin
ensure_success mkdir -p $TEST_DIR/nested
ensure_success echo "Nested Hello World" > $TEST_DIR/nested/file4.txt
ensure_success echo -e '\x00\x01\x02NestedHello\x03\x04\x05' > $TEST_DIR/nested/file5.bin

# Valid regex patterns
valid_patterns=(
    "hello"
    "^start"
    "end$"
    "a.b"
    "[0-9]"
    "[a-z]"
    "[^a-z]"
    "foo|bar"
    "\\bword\\b"
    ".*"
)

# Invalid regex patterns (for basic regex)
invalid_patterns=(
    "[a-z"
    "foo\\"
)

# Function to run grep command and check the result
run_grep_test() {
    local grep_cmd=$1
    local pattern=$2
    local output_file=$3
    $grep_cmd "$pattern" $TEST_DIR &>> $output_file
}

# Files to store the results
STANDARD_GREP_RESULTS="standard_grep_results.txt"
TINYGREP_RESULTS="TINYGREP_results.txt"

# Clear previous results
> $STANDARD_GREP_RESULTS
> $TINYGREP_RESULTS

# Test just one simple file
echo "Testing search in file directly"
run_grep_test "$STANDARD_GREP" "main.o" "Makefile"
run_grep_test "$TINYGREP" "main.o" "Makefile"

# Test valid patterns with both grep utilities
echo "Testing valid patterns."
for pattern in "${valid_patterns[@]}"; do
    run_grep_test "$STANDARD_GREP" "$pattern" "$STANDARD_GREP_RESULTS"
    run_grep_test "$TINYGREP" "$pattern" "$TINYGREP_RESULTS"
done

# Test invalid patterns with both grep utilities
echo "Testing invalid patterns."
for pattern in "${invalid_patterns[@]}"; do
    run_grep_test "$STANDARD_GREP" "$pattern" "$STANDARD_GREP_RESULTS"
    run_grep_test "$TINYGREP" "$pattern" "$TINYGREP_RESULTS"
done

echo The results for the $STANDARD_GREP in the $STANDARD_GREP_RESULTS and for the $TINYGREP in the $TINYGREP_RESULTS

# Compare the results
diff $STANDARD_GREP_RESULTS $TINYGREP_RESULTS > diff_results.txt

# Print the comparison result
echo "Comparison result (diff):"
cat diff_results.txt

echo "Test completed"
