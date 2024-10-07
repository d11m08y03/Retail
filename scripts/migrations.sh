#!/bin/bash

set -e

if [ "$#" -lt 1 ]; then
  echo "Usage: ./$0 option[build | run]"
  exit 1
fi

case "$1" in
  build)
    gcc migrations/migrations.c -Wall -Wextra -Wpedantic -Werror -o build/migrations -lsqlite3
    echo "Built migrations."
    ;;
  run)
    echo "Running json_test."
    ./build/migrations
    ;;
  *)
    echo "Invalid argument: $1"
    echo "Usage: ./$0 option[build | run]"
    exit 1
    ;;
esac
