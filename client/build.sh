gcc main.c components/navbar.c components/card.c pages/products.c -Lextern -lraygui -lraylib -Iextern -lm -o bin

export LD_LIBRARY_PATH=./extern/:$LD_LIBRARY_PATH && ./bin
