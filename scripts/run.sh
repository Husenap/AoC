#!/bin/bash

bash $(dirname $0)/build.sh
if [ $? -ne 0 ]; then
  exit $?
fi
pushd .build/
env CTEST_OUTPUT_ON_FAILURE=1 ctest . -R day_"$@"