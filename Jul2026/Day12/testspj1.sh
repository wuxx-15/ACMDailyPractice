#!/bin/bash
#此路径下在macOS上使用Apple Clang编译(macOS下GCC不能链接到ASAN)，在Linux下使用GCC编译
#example:testspj1.sh sol.cpp spj.cpp gen.cpp 20
#适用于无需构造暴力解的SPJ问题，如构造题
sol=$1;spj=$2;gen=$3;loops=$4 
trap 'rm -f sol spj gen' EXIT

CMP="g++ -g3 -O2 -Wall -Wextra -fsanitize=address,undefined"
$CMP $sol -o sol 2> debug.log #待验证的解
$CMP $spj -o spj 2>> debug.log #特判程序
$CMP $gen -o gen 2>> debug.log #数据生成器

if [ ! -f sol ] || [ ! -f spj ] || [ ! -f gen ]; then
    echo "Compile Error!"
    exit 1
fi

IS_AC=1

for ((i=1;i<=loops;++i)); do
    ./gen > data.in
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
    elif ! ./spj data.in sol.out 2> debug.log; then
        echo -e "WA on test $i!"
        IS_AC=0
        cat sol.out >> debug.log
        echo "Detailed log saved to debug.log"
        break
    fi
done

if [ $IS_AC -eq 1 ]; then
    echo "Accepted!"
fi

