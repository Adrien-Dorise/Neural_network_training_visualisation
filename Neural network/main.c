#include <stdio.h>
#include "neuralNetwork.h"
#include "interface.h"



#define OUTPUTSIZE 2
#define LAYERNUMBER 4
#define LAYER1 3
#define LAYER2 3
#define LAYER3 3
#define LAYER4 3 
#define ITERATIONS 1000	
#define GRADIENTSIGMA 0.005
#define SKIPITER 10

int main()
{
	int i=0,iteration=0,error=0;
	float fCost[ITERATIONS]={0};
	float fLastCost;
	srand(time(NULL));
	struct ANN nn;
	struct neuron n;

	int iNeuronRepartition[LAYERNUMBER] = {LAYER1,LAYER2,LAYER3,LAYER4};
	int iSigmaTypePerLayer[LAYERNUMBER+1] = {2,2,2,2,2};
	float fInput[INPUTSIZE] = {0.01,5.00};
	float fTarget[OUTPUTSIZE] = {0.1,0.5};
	float fPredict[OUTPUTSIZE] = {0};
	int count = 0;
	
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* text = NULL;
	SDL_Event events;
	


	//initNeuron(&n, 12);
	//TESTNEURON(n);
	//freeNeuron(n);

	initWindow(&window,&renderer,WINDOWHEIGHT,WINDOWWIDTH);
	initANN(&nn, INPUTSIZE, OUTPUTSIZE, LAYERNUMBER, iNeuronRepartition, ITERATIONS, GRADIENTSIGMA,iSigmaTypePerLayer);
	//propagation(&nn, fInput, fPredict);
	
	/*
	nn.neurons[1][0].fWeights[0] = 0;
	nn.neurons[1][0].fWeights[1] = 0;
	nn.neurons[2][1].fWeights[1] = 0;
	nn.neurons[3][1].fWeights[1] = 0;
	*/
	
	//TESTANN(nn);
	
	

	for(iteration=0;iteration<ITERATIONS;iteration++)
	{

		propagation(&nn, fInput, fPredict);
				
		//for (i=0;i<OUTPUTSIZE;i++){printf("RESULTS NEURON %i: %f\n",i,fPredict[i]);}
		
		fCost[iteration] = costFunction(OUTPUTSIZE, fTarget, fPredict);
		//printf("\nCOST %i IS %f\n",i,fCost[iteration]);
		
		//TESTANN(nn);
		/*displayANN(nn,&renderer,&text,fInput,fTarget,fCost[iteration]);
		pause();
		*/
		if (iteration == 0 | iteration == count*SKIPITER | error != 0)
		{
			if(iteration == 0)
				{fLastCost = 0;}
			else
				{fLastCost = fCost[iteration-SKIPITER];}
			error = displayBackpropagation(nn,&renderer,&text,fInput,fTarget,fCost[iteration],fLastCost,iteration,ITERATIONS);
			if(error != 0)
			{printf("ERROR %i",error);break;}
			count++;
		}

		
		/*for(i=0;i<OUTPUTSIZE;i++)
		{printf("\nPredict%i IS %f\n",i,fPredict[i]);}*/
		
		
		backpropagation(&nn, fTarget, fInput);

	}
	
	
	
	/*for (i = 0; i<ITERATIONS; i++)
	{printf("\nCOST %i IS %f\n",i,fCost[i]);}*/
	
	
	//TESTANN(nn);
	/*
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	displayANN(nn,&renderer,&text,fInput,fTarget,fCost[0]);
	pause();
	*/

	SDL_DestroyTexture(text);
	closeWindow(&window,&renderer);
	freeANN(nn);
	printf("\nEND PROGRAM!!!\n");
	return 0;
}

















