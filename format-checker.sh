#!/bin/bash

status=0
for file in $(find include source test/include test/source -name "*.cpp" -o -name "*.hpp")
do
    output=$(diff <(cat $file) <(clang-format $file))
    if [ $? -ne 0 ]
    then
      echo -e "\nFile \""$file"\" is not compliant with the coding style"
      echo "$output"
      status=1
    fi
done
exit $status
