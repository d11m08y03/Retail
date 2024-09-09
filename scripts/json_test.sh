#!/bin/bash

set -e

if [ "$#" -lt 1 ]; then
  echo "Usage: ./$0 option[build | run]"
  exit 1
fi

case "$1" in
  build)
    gcc src/json.c tests/json_test.c -Iexternal/criterion-2.4.2/include/ -Lexternal/criterion-2.4.2/lib/ -lcriterion -lcurl -o build/json_test 
    echo "Built json_test."
    ;;
  run)
    echo "Running json_test."
    export LD_LIBRARY_PATH=./external/criterion-2.4.2/lib/:$LD_LIBRARY_PATH && ./build/json_test
    ;;
  *)
    echo "Invalid argument: $1"
    echo "Usage: ./$0 option[build | run]"
    exit 1
    ;;
esac
