gcc -std=c17 -Wall -Wextra -pedantic -fsanatize=address,undefined -pthread -o OUTFILE threads.c
echo Run singlethreaded
./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 0
echo Run multithreaded
./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 4