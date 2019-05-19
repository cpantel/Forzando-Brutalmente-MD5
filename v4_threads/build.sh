gcc -ggdb -Wall md5.c  -o md5.exe -lpthread
gcc -ggdb -Wall find.c  -o find.exe -lpthread
gcc -Wall find.c -O1 -o findO1.exe -lpthread
gcc -Wall find.c -O2 -o findO2.exe -lpthread
gcc -Wall find.c -O3 -o findO3.exe -lpthread
