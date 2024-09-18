gcc main.c navbar.c -L./extern/ -lraygui -lraylib -Iextern -o bin

export LD_LIBRARY_PATH=./extern/:$LD_LIBRARY_PATH && ./bin
