rm 2105112.cpp 2105112.out > /dev/null 2>&1

flex -o 2105112.cpp 2105112.l

g++ 2105112.cpp -lfl -o 2105112.out

./2105112.out input.txt