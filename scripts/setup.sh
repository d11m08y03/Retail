#!/bin/bash

set -e

mkdir build
mkdir external

echo "Downloading Criterion:"
echo ""
wget https://github.com/Snaipe/Criterion/releases/download/v2.4.2/criterion-2.4.2-linux-x86_64.tar.xz -P ./external

echo "Extracting Criterion."
tar -xf external/criterion-2.4.2-linux-x86_64.tar.xz -C ./external
rm -r ./external/criterion-2.4.2-linux-x86_64.tar.xz

echo "Setting up LD path."
export LD_LIBRARY_PATH=./external/criterion-2.4.2/lib/:$LD_LIBRARY_PATH

echo "Finished."
