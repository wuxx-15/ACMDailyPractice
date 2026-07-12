#!/bin/bash
#此路径下在macOS上使用Apple Clang编译(macOS下GCC不能链接到ASAN)，在Linux下使用GCC编译
#example:test.sh sol.cpp brute.cpp gen.cpp 20
#适用于答案唯一的一般性问题
sol=$1;brute=$2;gen=$3;loops=$4
trap 'rm -f sol brute gen' EXIT

CMP="g++ -g3 -O2 -Wall -Wextra -fsanitize=address,undefined"
$CMP $sol -o sol 2> debug.log #待验证的解
$CMP $brute -o brute 2>> debug.log #暴力解
$CMP $gen -o gen 2>> debug.log #数据生成器

if [ ! -f sol ] || [ ! -f brute ] || [ ! -f gen ]; then
    echo "Compile Error!"
    exit 1
fi

IS_AC=1

for ((i=1;i<=loops;++i)); do
    ./gen > data.in
    ./brute < data.in > std.out
    timeout 1s ./sol < data.in > sol.out 2> debug.log
    exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo -e "TLE on test $i!"
        IS_AC=0
        break
    elif [ $exit_code -ne 0 ]; then
        echo -e "RE on test $i"
        IS_AC=0
        echo "Detailed log saved to debug.log"
        break
    elif ! diff -w std.out sol.out > /dev/null; then
        echo -e "WA on test $i!\n"
        IS_AC=0
        {
            sdiff -w 60 std.out sol.out | head -n 50
        } > debug.log
        echo "Detailed log saved to debug.log"
        break
    fi
done

if [ $IS_AC -eq 1 ]; then
    echo "Accepted!"
fi

