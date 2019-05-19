
gcc -c -Wall -mavx2 find.c     -o find.o

gcc -c -Wall -mavx2 find.c -O3 -o findO3.o

ls -l *.o

read -p longitud

objdump -S find.o    | grep ymm

read

objdump -S findO3.o | grep ymm

read 
for sub in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 ; do
   echo "ymm$sub"
   echo -n "   normal "
   objdump -S find.o    | grep "ymm$sub" | wc -l
   echo -n "   optimizado "
   objdump -S findO3.o | grep "ymm$sub" | wc -l
done
