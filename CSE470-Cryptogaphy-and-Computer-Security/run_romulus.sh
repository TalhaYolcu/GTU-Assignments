

run_romulus() {
    gcc -c main.c romulus.c
    gcc main.o romulus.o -o main
    ./main
}

cd romulus
run_romulus