#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include "interface.h"

#define MAXFUNCTION 50
#define MAXNEURONS 1000
#define MAXLAYERS 20

#define OFFSET 50
#define NEURONRADIUS 30
#define HEIGHTBLANK NEURONRADIUS*2 +300
#define WIDTHBLANK NEURONRADIUS*2 + 300
#define FONTSIZE 11

#define INPUTSIZE 2




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
int displayBackpropagation(struct ANN nn, SDL_Renderer** renderer,SDL_Texture** texture, float fInput[], float fTarget[], float fCost, float fLastCost,int iCurrentIteration, int iTotIterations);
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
