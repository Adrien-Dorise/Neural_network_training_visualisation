default : ANN

clean :
	rm *.o mainDiag

ANN : mainDiag.o neuralNetwork.o  interface.o 
	gcc -Wall main.o neuralNetwork.o interface.o -lm -lSDL2main -lSDL2_ttf -lSDL2 -o ANN 

%.o : %.c 
	gcc -Wall -c  $< 

neuralNetwork.o : neuralNetwork.h interface.h
interface.o : interface.h 


