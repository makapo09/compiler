#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check if alpha executable exists
if [ ! -f "./alpha" ]; then
    echo -e "${RED}Error: alpha executable not found. Run 'make' first.${NC}"
    exit 1
fi

# Check if tests directory exists
if [ ! -d "./test" ]; then
    echo -e "${RED}Error: test directory not found.${NC}"
    exit 1
fi

echo -e "${YELLOW}Running Alpha Compiler Tests${NC}"
echo "=============================="

# Counter for passed/failed tests
passed=0
failed=0

# Run each test file
for testfile in test/*.asc; do
    if [ -f "$testfile" ]; then
        filename=$(basename "$testfile")
        echo -n "Testing $filename... "
        
        # Run the compiler
        if ./alpha "$testfile" > /dev/null 2>&1; then
            # Check if output files were created
            if [ -f "quads.txt" ] && [ -f "alpha.abc" ] && [ -f "alpha.txt" ]; then
                echo -e "${GREEN}PASSED${NC}"
                ((passed++))
                
                # Optional: Save outputs with test name
                mkdir -p tests/output
                cp quads.txt "tests/output/${filename%.asc}_quads.txt"
                cp alpha.abc "tests/output/${filename%.asc}.abc"
                cp alpha.txt "tests/output/${filename%.asc}_target.txt"
            else
                echo -e "${RED}FAILED${NC} (output files missing)"
                ((failed++))
            fi
        else
            echo -e "${RED}FAILED${NC} (compilation error)"
            ((failed++))
        fi
        
        # Clean up for next test
        rm -f quads.txt alpha.abc alpha.txt
    fi
done

echo "=============================="
echo -e "Results: ${GREEN}$passed passed${NC}, ${RED}$failed failed${NC}"

# Return appropriate exit code
if [ $failed -eq 0 ]; then
    exit 0
else
    exit 1
fi