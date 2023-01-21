
run_tinyjambu() {
    gcc -c main.c tinyjambu.c
    gcc main.o tinyjambu.o -o main
    ./main
}

cd tinyjambu
run_tinyjambu

