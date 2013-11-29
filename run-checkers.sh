#!/bin/bash

TARGET_DIR=build

./cpplint.py --filter=-legal,-build/namespaces,-whitespace/labels,-build/include_what_you_use,-runtime/int,-readability/streams,-build/include_order `find concordia concordia-console -type f -regextype posix-extended -regex '.*\.(cpp|hpp|h|c)' ! -regex '.*\./build.*' ! -regex '.*concordia/common/config.hpp' ! -regex '.*/(t|tests)/.*'` 2> cpplint-result.txt

cppcheck -D__cplusplus -D__GNUC__=3 -f  --enable=all echo `find . -type d ! -path './.git*' ! -path "./${TARGET_DIR}"'*' | perl -ne 'chomp; print "-I$_ "'` `find . -type f -regextype posix-extended -regex '.*\.(cpp|hpp)' ! -regex '.*\./build.*'` 2> cppcheck-result.txt
