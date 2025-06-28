rm text.cpp test.out > /dev/null 2>&1

flex -o test.cpp test.l

g++ test.cpp -lfl -o test.out

./test.out input.txt