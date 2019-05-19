gcc -Wall -mavx2 md5.c      -o md5.exe
gcc -Wall -mavx2 find.c     -o find.exe    -lpthread
gcc -Wall -mavx2 find.c -O1 -o findO1.exe -lpthread
gcc -Wall -mavx2 find.c -O2 -o findO2.exe -lpthread
gcc -Wall -mavx2 find.c -O3 -o findO3.exe -lpthread
