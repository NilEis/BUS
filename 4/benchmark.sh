TIMEFORMAT=%R
echo "Singlethreaded: "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a_big.txt ./matrizen/b_big.txt 0 >/dev/null 2>&1; done)
echo "Multithreaded: "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a_big.txt ./matrizen/b_big.txt 12 >/dev/null 2>&1; done)
