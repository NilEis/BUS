TIMEFORMAT=%R
echo "0"
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 0 >/dev/null 2>&1; done)
echo "1 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 1 >/dev/null 2>&1; done)
echo "2 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 2 >/dev/null 2>&1; done)
echo "3 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 3 >/dev/null 2>&1; done)
echo "4 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 4 >/dev/null 2>&1; done)
echo "6 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 6 >/dev/null 2>&1; done)
echo "8 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 8 >/dev/null 2>&1; done)
echo "12 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 12 >/dev/null 2>&1; done)
echo "16 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 16 >/dev/null 2>&1; done)
echo "24 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 24 >/dev/null 2>&1; done)
echo "32 "
time (for i in {1..2000}; do ./OUTFILE ./matrizen/a.txt ./matrizen/b.txt 32 >/dev/null 2>&1; done)
