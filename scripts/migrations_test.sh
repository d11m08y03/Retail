#!/bin/bash

set -e

if [ "$#" -lt 1 ]; then
  echo "Usage: ./$0 option[build | run]"
  exit 1
fi

case "$1" in
  build)
    gcc migrations/migrations.c tests/migrations_test.c -Iexternal/criterion-2.4.2/include/ -Lexternal/criterion-2.4.2/lib/ -lcriterion -lsqlite3 -o build/migrations_test
    echo "Built migrations_test."
    ;;
  run)
    echo "Running migrations_test."
    export LD_LIBRARY_PATH=./external/criterion-2.4.2/lib/:$LD_LIBRARY_PATH && ./build/migrations_test
    echo "Finished running migrations_test. Removed tests/test.db"
    rm ./tests/test.db
    ;;
  *)
    echo "Invalid argument: $1"
    echo "Usage: ./$0 option[build | run]"
    exit 1
    ;;
esac
