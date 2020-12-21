#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include "interface.h"

#define MAXFUNCTION 50
#define MAXNEURONS 1000
#define MAXLAYERS 20

#define OFFSET 100
#define NEURONRADIUS 50
#define HEIGHTBLANK NEURONRADIUS*2 +400
#define WIDTHBLANK NEURONRADIUS*2 +400
#define FONTSIZE 18





struct neuron{
	int iWeightNumber;
	float *fWeights;
	float *fLastWeights;
	int iSigmaType;
	float fResultIn;
	float fOutput;
	int xPos;
	int yPos;
};


	

struct ANN{
	int iInputSize;
	int iOutputSize;
	int iLayerNumber; //hidden layer + output layer
	int iIterations;
	float fGradientSigma;
	int *iNeuronsPerLayer; 
	struct neuron** neurons; //tab of neurons[layer][neuron]
	//char cFunction[MAXFUNCTION];

};


int initANN(struct ANN * nn, int iInputSize, int iOutputSize, int iHiddenLayerNumber, int iNeuronsPerLayer[], int iIterations, float fGradientSigma, int iSigmaType[]);
void freeANN(struct ANN nn);
int initNeuron(struct neuron *n, int iNumberWeights, int iSigmaType,int xPos, int yPos);
void freeNeuron(struct neuron n);
int displayANN(struct ANN nn, SDL_Renderer** renderer,SDL_Texture** texture, float fInput[], float fTarget[], float fCost);
int displayBackpropagation(struct ANN nn, SDL_Renderer** renderer,SDL_Texture** texture, float fInput[], float fTarget[], float fCost, float fLastCost,int iteration);
float activationFunction(float x,int iSigmaType, int isDerivative); //If isDerivative is 1, we
int propagation(struct ANN *nn,float fInputs[], float fResult[]);
float costFunction(int iOutputSize, float fTarget[], float fPredict[]);
//float costDerivative(float fTarget, float fPredict, int fSigma)
float lossDerivative(struct neuron n, float fTarget);
int backpropagation(struct ANN* nn, float fTarget[], float fInput[]);


//TEST
void TESTNEURON(struct neuron n);
void TESTANN (struct ANN nn);


#endif
