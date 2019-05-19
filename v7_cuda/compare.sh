echo "4: 1 x 1"
time ./find.exe 1 1 "7eb0d9c6fccbeba44affc15430bb3723" # ;;zzzz

echo "5: 1 x 64"
time ./find.exe 1 64 "cb43ad2579d2a663c01643fc6270a77e" # ;zzzzz

echo "5: 64 x 1"
time ./find.exe 64 1 "5aa209effec9b352c986957bfcb2326c" # z;zzzz

echo "6: 64 x 64"
time ./find.exe 64 64 "453e41d218e071ccfb2d1c99ce23906a" # zzzzzz
