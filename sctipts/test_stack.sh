PROJECT_DIR=$HOME/K-R-language-c &&

cc $PROJECT_DIR/lib/stack.c $PROJECT_DIR/lib/array_utils.c $PROJECT_DIR/lib/test/stack.test.c -o main &&
./main &&
rm -rf ./main