test1 : descripteur_txt.c descripteur_txt.h FIFO.h FIFO.c main_test.c
	gcc -c FIFO.c
	gcc -c descripteur_txt.c
	gcc -c main_test.c
	gcc -o test1.out FIFO.o descripteur_txt.o main_test.o
	./test1.out

test2 : FIFO.h FIFO.c tst_FIFO.c
	gcc -c FIFO.c
	gcc -c tst_FIFO.c
	gcc -o test2.out FIFO.o tst_FIFO.o
	./test2.out
