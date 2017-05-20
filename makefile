main : main.cpp HugeInt.h
	g++ -o main main.cpp --std=c++11

test : main.cpp HugeInt.h
	g++ -o test main.cpp --std=c++11 -DTEST
