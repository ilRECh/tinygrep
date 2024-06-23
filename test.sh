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
# Create the $BUILD_DIR directory
ensure_success mkdir -p $BUILD_DIR
# Enter the $BUILD_DIR directory, essentially the tests will run here
ensure_success cd $BUILD_DIR
# Build the program
ensure_success cmake -DCMAKE_BUILD_TYPE=Release ..
ensure_success make

# Create a temporary directory for testing
TEST_DIR="test_grep"
ensure_success mkdir -p $TEST_DIR

# Create some text files
ensure_success echo "Hello World" > $TEST_DIR/file1.txt
ensure_success echo "Hello Bash" > $TEST_DIR/file2.txt
ensure_success echo -e '\x00\x01\x02Hello\x03\x04\x05' > $TEST_DIR/file3.bin

# Create nested directories with more files
ensure_success mkdir -p $TEST_DIR/nested
ensure_success echo "Nested Hello World" > $TEST_DIR/nested/file4.txt
ensure_success echo -e '\x00\x01\x02NestedHello\x03\x04\x05' > $TEST_DIR/nested/file5.bin

# Create a large file
ensure_success base64 /dev/urandom | head -c 1000000 > $TEST_DIR/largefile.txt

# Create files with special characters
ensure_success echo -e "Hello\nWorld" > $TEST_DIR/file_with_newline.txt
ensure_success echo -e "Hello\tWorld" > $TEST_DIR/file_with_tab.txt

# Create files with varying permissions
ensure_success echo "This is a readable file." > $TEST_DIR/readable_file.txt
ensure_success echo "This file has restricted access." > $TEST_DIR/restricted_file.txt
ensure_success chmod 000 $TEST_DIR/restricted_file.txt

# Create directories with varying permissions
ensure_success mkdir -p $TEST_DIR/restricted_dir
ensure_success echo "File in restricted directory." > $TEST_DIR/restricted_dir/file_in_restricted_dir.txt
ensure_success chmod 000 $TEST_DIR/restricted_dir

# Additional base cases
touch $TEST_DIR/empty_file.txt                          # Empty file
echo "     " > $TEST_DIR/whitespace_file.txt            # File with only whitespace
echo "!@#$%^&*()_+" > $TEST_DIR/special_chars.txt       # File with special characters

# Valid regex patterns
valid_patterns=(
    "Hello"
    "^start"
    "end$"
    "a.b"
    "[0-9]"
    "[a-z]"
    "[^a-z]"
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
    echo >> $output_file
    echo "Testing: $pattern" >> $output_file
    $grep_cmd "$pattern" $TEST_DIR &>> $output_file 2>&1
}

# Files to store the results
STANDARD_GREP_RESULTS="output_std_grep_results.txt"
TINYGREP_RESULTS="output_tinygrep_results.txt"

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

# Trying to valgrind if available
echo "Trying valgrind."
valgrind=$(which valgrind)
VALGRIND_OUTPUT=output_valgrind.txt
> $VALGRIND_OUTPUT

if [ $? -eq 0 ]
then
    echo "Valgrind found, testing."

    $valgrind $TINYGREP "a" "Makefile" &>> $VALGRIND_OUTPUT

    no_leaks=$($TINYGREP "All heap blocks were freed -- no leaks are possible" $VALGRIND_OUTPUT | wc -l)

    if [ $no_leaks -eq 1 ]
    then
        echo "Valgrind didn't find any leaks."
    else
        echo "Leaks found, Valgrind output:"
        cat $VALGRIND_OUTPUT
    fi
else
    echo "Valgrind not found."
    echo "Valgrind not found." &>> $VALGRIND_OUTPUT
fi

# Compare the results
diff $STANDARD_GREP_RESULTS $TINYGREP_RESULTS > diff_results.txt
line_count=$(wc -l diff_results.txt | awk '{print $1}')

exit_code=0

# Print the comparison result if diff_results.txt not empty
if [ $line_count -ne 0 ]
then
    echo "Comparison result (diff $STANDARD_GREP_RESULTS $TINYGREP_RESULTS):"
    cat diff_results.txt
    exit_code=1
else
    echo The $STANDARD_GREP_RESULTS and the $TINYGREP_RESULTS files are identical
fi

# Clean up
echo -e "Cleaning up test files"
chmod 700 $TEST_DIR/restricted_file.txt
chmod 700 $TEST_DIR/restricted_dir
rm -rf $TEST_DIR

echo "Test completed"
echo "Find outputs in the $STANDARD_GREP_RESULTS, $TINYGREP_RESULTS and $VALGRIND_OUTPUT files."

exit $exit_code
