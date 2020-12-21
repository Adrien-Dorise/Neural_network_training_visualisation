default : mainDiag

clean :
	rm *.o mainDiag

mainDiag : mainDiag.o neuralNetwork.o  interface.o 
	gcc -Wall mainDiag.o neuralNetwork.o interface.o -lm -lSDL2main -lSDL2_ttf -lSDL2 -o mainDiag 

%.o : %.c 
	gcc -Wall -c  $< 

neuralNetwork.o : neuralNetwork.h interface.h
interface.o : interface.h 


