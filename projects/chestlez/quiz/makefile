all : testme.c
	gcc -o testme testme.c -coverage -fpic -lm
	-./testme
	gcov testme.c

grader: testme.c
	gcc -o testme testme.c -coverage -fpic -lm
	./testme

testme : testme.c
	gcc -o testme testme.c -coverage -fpic -lm

run :
	./testme

coverage :
	./testme
	gcov testme.c

clean :
	rm testme testme.gcno testme.gcda testme.c.gcov