C_K_R_DIR=$HOME/K-R-language-c &&

cc $C_K_R_DIR/lib/stack.c $C_K_R_DIR/lib/array_utils.c $C_K_R_DIR/lib/test/stack.test.c -o main &&
./main &&
rm -rf ./main