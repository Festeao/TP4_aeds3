clear:	prog_character_match
	rm *.o

prog_character_match:	BoyerMooreHorspool.o	BoyerMooreHorspoolSunday.o	ShiftAndExato.o	ShiftAndAproximado.o	tempo.o	main.o
	gcc BoyerMooreHorspool.o BoyerMooreHorspoolSunday.o ShiftAndExato.o ShiftAndAproximado.o tempo.o main.o -o prog_character_match

tempo.o:	src/tempo.c
	gcc src/tempo.c -c

main.o:	main.c
	gcc main.c -c

BoyerMooreHorspool.o:	src/BoyerMooreHorspool.c
	gcc src/BoyerMooreHorspool.c -c

BoyerMooreHorspoolSunday.o:	src/BoyerMooreHorspoolSunday.c
	gcc src/BoyerMooreHorspoolSunday.c -c

ShiftAndExato.o:	src/ShiftAndExato.c
	gcc src/ShiftAndExato.c -c

ShiftAndAproximado.o:	src/ShiftAndAproximado.c
	gcc src/ShiftAndAproximado.c -c

clean:	
	rm prog_character_match