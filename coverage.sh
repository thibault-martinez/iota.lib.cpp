#!/bin/bash

# Generate baseline coverage data file
lcov --capture --initial --directory . --output-file coverage_base.info

# Generate coverage based on executed tests
lcov --capture --directory . --output-file coverage_test.info

# Merge coverage tracefiles
lcov --add-tracefile coverage_base.info --add-tracefile coverage_test.info --output-file coverage_merge.info

# Removing unwanted files from coverage
lcov --remove coverage_merge.info "`pwd`/external/*" "`pwd`/test/*" "/include/*" "/usr/*" -o coverage.info

# Upload coverage
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
