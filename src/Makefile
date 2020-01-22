test1 : fcts_test_image.c header_image.h test_image.c
	gcc -c fcts_test_image.c -lm
	gcc -c test_image.c -lm
	gcc -o test_image.out test_image.o test_image.c -lm
	./test_image.out
