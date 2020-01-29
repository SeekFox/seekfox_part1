testall : descripteur_txt.c descripteur_txt.h File_mots.c File_mots.h MOT.h MOT.c main_test.c
	gcc -c MOT.c
	gcc -c File_mots.c
	gcc -c descripteur_txt.c
	gcc -c main_test.c
	gcc -o testall.out Mot.o File_mots.o descripteur_txt.o main_test.o
	./testall.out

test2 : FIFO.h FIFO.c tst_FIFO.c
	gcc -c FIFO.c
	gcc -c tst_FIFO.c
	gcc -o test2.out FIFO.o tst_FIFO.o
	./test2.out

testmot : MOT.h MOT.c testMot.c
	gcc -c MOT.c
	gcc -c testMot.c
	gcc -o testmot.out MOT.o testMot.o
	./testmot.out

testfile : MOT.h MOT.c File_mots.h File_mots.c testFileMot.c
	gcc -c MOT.c
	gcc -c File_mots.c
	gcc -c testFileMot.c
	gcc -o testfile.out MOT.o File_mots.o testFileMot.o
	./testfile.out