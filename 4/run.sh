gcc -std=c17 -Wall -Wextra -pedantic -O3 -pthread -o OUTFILE threads.c
echo Run singlethreaded
./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 0
echo Run multithreaded
./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 4