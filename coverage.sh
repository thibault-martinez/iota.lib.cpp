#!/bin/bash

# Generate initial coverage information
lcov -c -i -d . -o .coverage.base

# Generate coverage based on executed tests
lcov -c -d . -o .coverage.run

# Merge coverage tracefiles
lcov -a .coverage.base -a .coverage.run  -o .coverage.info

# Filtering, extracting project files
lcov -e .coverage.info "`pwd`/source/*" "`pwd`/include/*" -o .coverage.info

# Upload coverage
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
