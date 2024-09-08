#!/bin/bash

set -e

if [ "$#" -lt 1 ]; then
  echo "Usage: ./$0 option[build | run]"
  exit 1
fi

case "$1" in
  build)
    gcc src/server.c src/handlers.c src/json.c -Wall -Wextra -Wpedantic -Werror -o build/server
    echo "Built server."
    ;;
  run)
    echo "Running server."
    ./build/server
    ;;
  *)
    echo "Invalid argument: $1"
    echo "Usage: ./$0 option[build | run]"
    exit 1
    ;;
esac
