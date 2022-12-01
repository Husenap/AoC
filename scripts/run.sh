#!/bin/bash

bash $(dirname $0)/build.sh
pushd .build/
env CTEST_OUTPUT_ON_FAILURE=1 ctest . -R day_"$@"