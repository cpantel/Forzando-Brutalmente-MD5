TARGET="74b87337454200d4d33f80c4663dc5e5" # aaaa
TARGET="b870c68f509d670e3eb032349cb2a71a" # ;;;;
TARGET="d0a1f5cada64a2bb2f701a81c847c64b" # ;;;<
TARGET="ccb3d4e6d3d99dce58247f3a5aecb760" # ;;;=
TARGET="d9552cafb990915b9e5539c199f87873" # ;;;>
TARGET="068738d797d4e434c72c1cd04c6479c8" # ;;;?
TARGET="a2c99b3fb57c8e69e8cd6294e627267b" # ;;;@
TARGET="f878eb21aa2edbf9a3ad38ed616233df" # ;;;A
TARGET="d4acf2997dd1e3fac66bfeabb8a537e8" # ;;;B
TARGET="0899b84ce92734c94eb508aead669cd3" # ;;;C
TARGET="5b2fa95648ef9872c1209ca6fc840a5c" # ;;;a
TARGET="06931a6a37bb7d313bee467eed917c8b" # ;;;b
TARGET="47889a1347a36a108435f16caab4dff7" # ;;;c
TARGET="155a55ab9ce0466170b0b2d254b6b93a" # ;;;z
TARGET="90f33c75dc61a1273c345569c6270e33" # ;;z;
TARGET="02c425157ecd32f259548b33402ff6d3" # zzzz

time ./find.exe $TARGET
echo
time ./findO1.exe $TARGET
echo
time ./findO2.exe $TARGET
echo
time ./findO3.exe $TARGET


