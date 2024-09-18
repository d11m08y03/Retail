gcc main.c navbar.c -Lexternal -lraygui -lraylib -o bin

export LD_LIBRARY_PATH=./external/:$LD_LIBRARY_PATH && ./bin
