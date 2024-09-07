This project aims to achieve a comprehensive online retail shop system in C. It focuses on creating functionalities for product catalog management, order processing, and customer feedback integration. The system is designed to efficiently handle real-time transactions, manage product categories, track inventory levels, and generate detailed sales reports, thereby improving both operational efficiency and the overall customer experience.

# Scripts
Bash scripts will be used to setup, build and run C code as many of the compile commands are fairly long.
Run all scripts from  the root directory of this project.

## Setup
Execute _scripts/setup.sh_. It will download and extract [Criterion](https://github.com/Snaipe/Criterion),  a testing framework designed to facilitate writing and running unit tests.

## Testing
All tests should be in the _tests_ directory and bear the same name as their implementation file followed by '__test_'. For example, for '_json.c_', the corresponding test file is '_json_test.c_'. Scripts used to build and run the tests should also bear the same name.

## Building & Running
Scripts used for that purpose will concern themselves with their own module first and there should be only 1 script per logical module. The script should be run with either _build_ or  _run_ as a command line argument.
