#TARGET="74b87337454200d4d33f80c4663dc5e5" # aaaa
#TARGET="b870c68f509d670e3eb032349cb2a71a" # ;;;;

TARGET="02c425157ecd32f259548b33402ff6d3" # zzzz

time ./find.exe $TARGET
echo
time ./findO1.exe $TARGET
echo
time ./findO2.exe $TARGET
echo
time ./findO3.exe $TARGET
