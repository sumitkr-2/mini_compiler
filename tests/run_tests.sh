#!/usr/bin/env bash
set +e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="$DIR/build/minic"

if [ ! -f "$BIN" ]; then
    echo "Compiler binary not found. Building..."
    (cd "$DIR" && make)
fi

echo "========================================"
echo " Running Mini Compiler Test Suite"
echo "========================================"

FAILED=0

run_valid_test() {
    local file="$1"
    local desc="$2"
    echo -n "Test [VALID]: $desc ($file) ... "
    output=$("$BIN" "$file" 2>&1)
    status=$?
    if [ $status -eq 0 ] && echo "$output" | grep -q "=== Three-Address Code ==="; then
        echo "PASS"
    else
        echo "FAIL (exit code: $status)"
        echo "$output"
        FAILED=$((FAILED + 1))
    fi
}

run_error_test() {
    local file="$1"
    local desc="$2"
    local expected_pattern="$3"
    echo -n "Test [ERROR]: $desc ($file) ... "
    output=$("$BIN" "$file" 2>&1)
    status=$?
    if [ $status -ne 0 ] && echo "$output" | grep -E -q "$expected_pattern"; then
        echo "PASS"
    else
        echo "FAIL (status: $status, pattern: $expected_pattern)"
        echo "$output"
        FAILED=$((FAILED + 1))
    fi
}

# Valid cases
run_valid_test "$DIR/examples/01_basic.mc" "Basic arithmetic and print"
run_valid_test "$DIR/examples/02_control_flow.mc" "If and If-Else branches"
run_valid_test "$DIR/examples/03_complex_expr.mc" "Complex and unary expressions"

# Error cases
run_error_test "$DIR/examples/error_undeclared.mc" "Undeclared variable check" "Undeclared variable"
run_error_test "$DIR/examples/error_redeclared.mc" "Redeclared variable check" "Redeclaration of variable"
run_error_test "$DIR/examples/error_syntax.mc" "Syntax error detection" "Syntax Error"
run_error_test "$DIR/examples/error_div_zero.mc" "Division by zero check" "Division by zero"

echo "========================================"
if [ $FAILED -eq 0 ]; then
    echo " All tests passed successfully!"
    echo "========================================"
    exit 0
else
    echo " $FAILED test(s) failed."
    echo "========================================"
    exit 1
fi
