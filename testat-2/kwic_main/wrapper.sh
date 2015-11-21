#!/bin/sh

# Run like this:
#
#   $ ./wrapper.sh < test_input.txt

DYLD_LIBRARY_PATH=../kwic/Debug:../word/Debug Debug/kwic_main
