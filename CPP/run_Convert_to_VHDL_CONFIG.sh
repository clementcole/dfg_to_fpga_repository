#!/bin/sh
#clang++ -std=c++11 -stdlib=libc++ -Weverything main.cpp
#xcrun clang++ -std=c++11 -stdlib=libc++ -Weverything main.cpp
#clang++ -Wall -Wno-c++14-extensions -std=c++0x convert_to_VHD_Config_test.cpp
#clang -Wall -Wno-c++14-extensions -std=libc++ convert_to_VHD_Config_test.cpp
#clang -Wall -Wno-c++14-extensions -std=c++0x convert_to_VHD_Config_test.cpp
#g++ convert_to_VHD_Config_test.cpp
g++ -std=c++14 convert_to_VHD_Config_test.cpp -o test 
./test
#clang++ convert_to_VHD_Config_test.cpp test.exe -std=c++14

#clang++ -Wall -Wno-c++14-extensions -std=c++0x Decorator_X86_test.cpp
#./a.out