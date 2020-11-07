#!/bin/bash

echo "Do you want to run:"
echo "[1] Python calculator (Better but slower)"
echo "[2] C++ Calculator (Faster but Worse)"
read -p "Enter choice (1, 2) here: " choice

if [ $choice -eq "2" ] ; then
	#clang++-7 -pthread -std=c++17 -o Calculator cpp/calcFuncs.cpp cpp/Calculator.cpp
	./cpp/Calculator
fi

if [ $choice -eq "1" ] ; then
	python3 python3/Calculator.py
fi