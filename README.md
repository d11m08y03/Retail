**Project Overview**

This project aims to develop a comprehensive online retail shop system in C, designed to provide a seamless shopping experience for customers while improving operational efficiency for the business. The system encompasses a range of functionalities, including:

- **Product Catalog Management:** Efficiently manage a dynamic catalog of products, allowing for easy addition, modification, and removal of items while categorizing them for better user navigation.
  
- **Order Processing:** Streamlined order management processes that facilitate real-time transactions, ensuring that customer orders are processed quickly and accurately, from selection to payment.
  
- **Inventory Management:** Real-time tracking of inventory levels to prevent stockouts or overstock situations, ensuring that the right products are available for customers when needed.

This system aims to enhance the overall customer experience by providing intuitive navigation and timely order fulfillment while equipping the business with the tools necessary to optimize operations and drive growth.

# Scripts
Bash scripts will be used to setup, build and run C code as many of the compile commands are fairly long.
Run all scripts from  the root directory of this project.

## Setup
Execute _scripts/setup.sh_. It will download and extract [Criterion](https://github.com/Snaipe/Criterion),  a testing framework designed to facilitate writing and running unit tests.

## Testing
All tests should be in the _tests_ directory and bear the same name as their implementation file followed by '__test_'. For example, for '_json.c_', the corresponding test file is '_json_test.c_'. Scripts used to build and run the tests should also bear the same name.

## Building & Running
Scripts used for that purpose will concern themselves with their own module first and there should be only 1 script per logical module. The script should be run with either _build_ or  _run_ as a command line argument.
