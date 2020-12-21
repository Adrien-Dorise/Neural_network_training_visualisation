#include "neuralNetwork.h"




//Network Creation


int initNeuron(struct neuron *n, int iNumberWeights,int iSigmaType,int xPos, int yPos)
{

	int i;
	float fRandom = 0.0;
	if (iNumberWeights<1){printf("WARNING: Impossible to have less than 1 weight for a neuron, initialisation for 1 weight by default\n");iNumberWeights=1;}
	n->fWeights = malloc(iNumberWeights*sizeof(float));
	for(i=0;i<iNumberWeights;i++)
	{
		fRandom = (float)(rand()%50001)+0;	//Limits are rand()%(max-min+1)+min; 	
		n->fWeights[i]=fRandom*0.00001;
	}
	
	n->fLastWeights = malloc(iNumberWeights*sizeof(float));
	for(i=0;i<iNumberWeights;i++)
	{
		n->fLastWeights[i]=0;
	}
	
	n->iWeightNumber = iNumberWeights;
	n->iSigmaType = iSigmaType;
	n->fResultIn=0;
	n->fOutput=0;
	n->xPos=xPos;
	n->yPos=yPos;
	return 0;
}	



void freeNeuron(struct neuron n)
{
	free(n.fLastWeights);
	free(n.fWeights);
}





int initANN(struct ANN * nn, int iInputSize, int iOutputSize, int iHiddenLayerNumber, int iNeuronsPerLayer[], int iIterations, float fGradientSigma, int iSigmaType[])
{
	int lay,neur,i;
	struct neuron n;
	int xPos, yPos;
	
	int iLayerNumber = iHiddenLayerNumber+1;//+1 as we count output layer as a layer
	
	nn->iInputSize = iInputSize;
	nn->iOutputSize = iOutputSize;
	nn->iLayerNumber = iLayerNumber;
	nn->iIterations = iIterations;
	nn->fGradientSigma = fGradientSigma;
	
	
	nn->iNeuronsPerLayer = malloc(iLayerNumber*sizeof(int));
	for (i=0;i<iHiddenLayerNumber;i++){nn->iNeuronsPerLayer[i] = iNeuronsPerLayer[i];}
	nn->iNeuronsPerLayer[iLayerNumber-1] = iOutputSize;
	
	
	nn->neurons = malloc(iLayerNumber*sizeof(struct neuron*));
	for (lay=0; lay<iLayerNumber;lay++) //+1 to add output layer
	{
		

		if(lay<iLayerNumber-1)
		{ 
			nn->neurons[lay] = malloc(iNeuronsPerLayer[lay]*sizeof(struct neuron));
			for (neur=0;neur<nn->iNeuronsPerLayer[lay];neur++)
			{
				xPos = WIDTHBLANK*(lay+1) + OFFSET;
				yPos = HEIGHTBLANK*(neur) + OFFSET;
				if(lay == 0) //Case of input -> first layer
				{
					
					initNeuron(&(nn->neurons[lay][neur]),iInputSize,iSigmaType[lay],xPos,yPos);	
				}
				else //Hidden layers
				{
					initNeuron(&(nn->neurons[lay][neur]),iNeuronsPerLayer[lay-1],iSigmaType[lay],xPos,yPos);
				}
			}
		}
		else if(lay==iLayerNumber-1) //Case for last hidden layer -> output layer
		{
			nn->neurons[lay] = malloc(iOutputSize*sizeof(struct neuron));
			for(neur=0;neur<iOutputSize;neur++)
			{
				xPos = WIDTHBLANK*(lay+1) + OFFSET;
				yPos = HEIGHTBLANK*(neur) + OFFSET; 
				initNeuron(&(nn->neurons[lay][neur]),iNeuronsPerLayer[lay-1],iSigmaType[lay],xPos,yPos);
			}
		}
		else{printf("ERROR IN INITANN, CODE ERROR 1");return 1;} 
		
			
	}
	return 0;
}



void freeANN(struct ANN nn)
{	
	for (int i=0;i<nn.iLayerNumber;i++)
	{
		for(int j=0;j<nn.iNeuronsPerLayer[i];j++)
		{
			freeNeuron(nn.neurons[i][j]);
		}
		free(nn.neurons[i]);
	}
	free(nn.neurons);

}



int displayANN(struct ANN nn, SDL_Renderer** renderer,SDL_Texture** texture, float fInput[], float fTarget[], float fCost)
{
	int lay,neur,weig;
	int blend =100;
	int color[3] = {0,0,0};
	int colorTarget[3] = {0,0,0};
	int colorArrowGreen[3] = {0,255,0};
	int colorArrowRed[3] = {255,0,0};
	int xNeurIn[nn.iInputSize],yNeurIn[nn.iInputSize];
	int xNeur,yNeur,xLine1,yLine1,xLine2,yLine2,xText,yText;
	char value[50];
	int iWeigthOffset = 8;
	
	
	
	//Input Layer
	for (neur=0;neur<nn.iInputSize;neur++) 
	{	
		xNeurIn[neur] = OFFSET;
		yNeurIn[neur] = HEIGHTBLANK*(neur) + OFFSET;
		gcvt(fInput[neur], 6, value);
		xText = xNeurIn[neur] - 25;
		yText = yNeurIn[neur] -10;
		addTxt(renderer,texture , value, xText,yText, FONTSIZE, color);
	}

	
	//Output Values	
	for (neur=0;neur<nn.iOutputSize;neur++) 
	{	
		xNeur = nn.neurons[nn.iLayerNumber-1][neur].xPos;
		yNeur = nn.neurons[nn.iLayerNumber-1][neur].yPos;
		xLine1 = xNeur+NEURONRADIUS;
		yLine1 = yNeur;
		xLine2 = xNeur+NEURONRADIUS+OFFSET;
		yLine2 = yNeur;
		addBlendLine(renderer, xLine1, yLine1, xLine2, yLine2,color,blend);
		
		xText = xLine2 + 10;
		yText = yLine1 - 10 ;
		gcvt(nn.neurons[nn.iLayerNumber-1][neur].fOutput, 6, value);
		addTxt(renderer,texture , value, xText,yText, FONTSIZE, color);
		
		gcvt(fTarget[neur], 6, value); //PRINT TARGET
		addTxt(renderer,texture , strcat(value," = target"), xText, yText + 25, FONTSIZE, colorTarget);	
	}
	gcvt(fCost, 6, value); //PRINT COST
	addTxt(renderer,texture , strcat(value," = COST"), nn.neurons[nn.iLayerNumber-1][0].xPos, nn.neurons[nn.iLayerNumber-1][0].yPos - NEURONRADIUS*2, FONTSIZE, colorTarget);
	
	

	//Hidden layer
	for (lay=0; lay<nn.iLayerNumber;lay++)
	{
		for (neur=0;neur<nn.iNeuronsPerLayer[lay];neur++) 
		{
			xNeur = nn.neurons[lay][neur].xPos ;
			yNeur = nn.neurons[lay][neur].yPos;
			addCircle(renderer,xNeur,yNeur,NEURONRADIUS,color);
			gcvt(nn.neurons[lay][neur].fOutput, 3, value);
			addTxt(renderer,texture , value, xNeur- NEURONRADIUS/2,yNeur - NEURONRADIUS/4, FONTSIZE, color); // PRINT NEURON OUTPUT
			//printf("Layer %d,Neuron %d: %i//%i//\n",lay,neur,xNeur,yNeur);
			
			for (weig=0;weig<nn.neurons[lay][neur].iWeightNumber;weig++)
			{
				if (nn.neurons[lay][neur].fWeights[weig] != 0) //We do not display when weight = 0
				{
					xLine1 = xNeur - NEURONRADIUS;
					yLine1 = yNeur;
					if (lay==0)
					{
						
						xLine2 = xNeurIn[weig] + NEURONRADIUS;
						yLine2 = yNeurIn[weig];
					}
					else
					{
						xLine2 = nn.neurons[lay-1][weig].xPos + NEURONRADIUS;
						yLine2 = nn.neurons[lay-1][weig].yPos;
					}
					addBlendLine(renderer, xLine1, yLine1, xLine2, yLine2,color,blend);
					
					
					xText = xLine1 - NEURONRADIUS*1.5;
					if (yLine1==yLine2)
					{yText = yLine1 + LINETHICKNESS;}
					else
					{yText = yLine1 - (yLine1-yLine2)/iWeigthOffset;}
					gcvt(nn.neurons[lay][neur].fWeights[weig], 5, value);//print WEIGHTS
					addTxt(renderer,texture , value, xText,yText, FONTSIZE, color);
					}
						
			}

		}	

	}
	return 0;
}


int displayBackpropagation(struct ANN nn, SDL_Renderer** renderer,SDL_Texture** texture, float fInput[], float fTarget[], float fCost, float fLastCost,int iteration)
{	
	//CLIQUE Q TO QUIT BAKCPROPAGATION DISPLAY; SPACE TO MOVE
	SDL_Event events;
	int lay, neur, weig;
	int error = 0, blend=100;
	int xNeurIn[nn.iInputSize],yNeurIn[nn.iInputSize];
	int xNeur,yNeur,xLine1,yLine1,xLine2,yLine2,xText,yText;
	int *color,colorBlack[3] = {0,0,0},colorGreen[3] = {0,255,0},colorRed[3] = {255,0,0};
	char value[50];
	int iWeigthOffset = 8;


	//We render the first iteration
	SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
	SDL_RenderClear(*renderer);
	displayANN(nn,renderer,texture,fInput,fTarget,fCost);

	gcvt(fLastCost, 6, value); //PRINT LASTCOST
	addTxt(renderer,texture , strcat(value," = LAST COST"), nn.neurons[nn.iLayerNumber-1][0].xPos, nn.neurons[nn.iLayerNumber-1][0].yPos - NEURONRADIUS*2 - FONTSIZE, FONTSIZE, colorBlack);
	if(fCost > fLastCost)
	{color = colorGreen; addArrowUpR(renderer,nn.neurons[nn.iLayerNumber-1][0].xPos - FONTSIZE*2, nn.neurons[nn.iLayerNumber-1][0].yPos - NEURONRADIUS*2,FONTSIZE,color);}
	else if(fCost == fLastCost)
	{color = colorBlack;addArrowRight(renderer,nn.neurons[nn.iLayerNumber-1][0].xPos - FONTSIZE*2, nn.neurons[nn.iLayerNumber-1][0].yPos - NEURONRADIUS*2,FONTSIZE,color);}
	else
	{color = colorRed;addArrowDownR(renderer,nn.neurons[nn.iLayerNumber-1][0].xPos - FONTSIZE*2, nn.neurons[nn.iLayerNumber-1][0].yPos - NEURONRADIUS*2,FONTSIZE,color);}
	
	
	printf("display backpropagation in progress... \nPress a key to continue; Q to quit.\n");
	//INPUT LAYER COORDINATE CALCULATION
	for (neur=0;neur<nn.iInputSize;neur++) 
	{	
		xNeurIn[neur] = OFFSET;
		yNeurIn[neur] = HEIGHTBLANK*(neur) + OFFSET;
	}
	
	
	for(lay=nn.iLayerNumber-1; lay>=0;lay--)
	{
		for(neur=0;neur<nn.iNeuronsPerLayer[lay];neur++) 
		{
			xNeur = nn.neurons[lay][neur].xPos;
			yNeur = nn.neurons[lay][neur].yPos;
			for (weig=0;weig<nn.neurons[lay][neur].iWeightNumber;weig++)
			{
				
				
				
				sprintf(value, "%i", iteration);//print last weights
				addTxt(renderer,texture , "Backpropagation in progress: Press a key to continue, Q to skip this iteration, ESC to quit", 10,10, FONTSIZE*1.5, colorBlack);
				addTxt(renderer,texture , "Old weights displayed below new weights", 10,10+FONTSIZE*1.5, FONTSIZE*1.5, colorBlack);
				addTxt(renderer,texture , strcat(value," iterations"), 10,10+FONTSIZE*3, FONTSIZE*1.5, colorBlack);
				
				
				
				
				
				//Same as display ANN
				if (nn.neurons[lay][neur].fWeights[weig] != 0) //We do not display when weight = 0
				{
					xLine1 = xNeur - NEURONRADIUS;
					yLine1 = yNeur;
					if (lay==0)
					{
						xLine2 = xNeurIn[weig] + NEURONRADIUS;
						yLine2 = yNeurIn[weig];
					}
					else
					{
						xLine2 = nn.neurons[lay-1][weig].xPos + NEURONRADIUS;
						yLine2 = nn.neurons[lay-1][weig].yPos;
					}
					xText = xLine1 - NEURONRADIUS*1.5;
					
					
					
					if (yLine1==yLine2)
					{yText = yLine1 + LINETHICKNESS;}
					else
					{yText = yLine1 - (yLine1-yLine2)/iWeigthOffset;}
					//Choice of color for weight display
					if(nn.neurons[lay][neur].fLastWeights[weig] < nn.neurons[lay][neur].fWeights[weig])
					{color = colorGreen; addArrowUpR(renderer,xText-FONTSIZE*2,yText+FONTSIZE,FONTSIZE,color);}
					else if(nn.neurons[lay][neur].fLastWeights[weig] == nn.neurons[lay][neur].fWeights[weig])
					{color = colorBlack;addArrowRight(renderer,xText-FONTSIZE*2,yText+FONTSIZE,FONTSIZE,color);}
					else
					{color = colorRed;addArrowDownR(renderer,xText-FONTSIZE*2,yText,FONTSIZE,color);}
					
					
					addBlendLine(renderer, xLine1, yLine1, xLine2, yLine2,color,blend);
					gcvt(nn.neurons[lay][neur].fLastWeights[weig], 5, value);//print last weights
					addTxt(renderer,texture , value, xText-10,yText+FONTSIZE, FONTSIZE, colorBlack);
					
				}
				//We wait an input to continue
				do {
    					error = SDL_WaitEvent(&events);
				} while(events.type != SDL_KEYDOWN  && events.window.event != SDL_WINDOWEVENT_CLOSE); 
				switch(events.type)
				{
					case SDL_WINDOWEVENT:
						if (events.window.event == SDL_WINDOWEVENT_CLOSE)
							{printf("Aborting: Window closed\n"); return 1;}
					case SDL_KEYDOWN: 
				    		if (events.key.keysym.sym == SDLK_q) 
							{printf("Aborting: Q key pressed\n"); return 0;}
						if (events.key.keysym.sym == SDLK_ESCAPE) 
							{printf("Aborting: ESC key pressed\n"); return 1;}
				
				
				}
				
				
			}
		}
	}

	if (error==0){printf("ERROR IN displayBackpropagation. Code error %i\n", error);return 1;}
	return 0;
}






float activationFunction(float x,int iSigmaType, int isDerivative) //If isDerivative is 1, we give the derivative value (for backpropagation)
{
	float result = 0;
	float resultDeriv = 0;
	switch(iSigmaType)
	{
		default: printf("WARNING IN activationFunction: iFunctionType invalid. Code error 1\n"); return 0;
		//f(x)=x
		case 1: result = x;
			resultDeriv = 1;
			break;
		
		//Rectifier
		case 2: if(x>0)
			{
				result = x;
				resultDeriv = 1;
				break;
			}
			else
			{
				result = 0;
				resultDeriv = 0;
				break;
			}
		
		//Sigmoid
		case 3: result = 1/(1+exp(-x));
			resultDeriv = result*(1-result);
			break;
	}

	if(isDerivative != 1){return result;}
	else{return resultDeriv;}
}




int propagation(struct ANN *nn,float fInputs[], float fResult[])
{
	int lay, neur,weig,i;
	float fResultTemp=0;
	


	
	for (lay=0; lay<nn->iLayerNumber;lay++)//Propagation
	{	
		
		for (neur=0;neur<nn->iNeuronsPerLayer[lay];neur++)
		{
			fResultTemp = 0;
			for (weig=0;weig<nn->neurons[lay][neur].iWeightNumber;weig++)
			{//printf("layer %i, neur %i, wei %i: %f\n",lay,neur,weig,nn->neurons[lay][neur].fWeights[weig]);
				
				if(lay == 0) //Propagation of inputs
				{
					fResultTemp += nn->neurons[lay][neur].fWeights[weig] * fInputs[weig];
				}
				else
				{
					fResultTemp += nn->neurons[lay][neur].fWeights[weig] * nn->neurons[lay-1][weig].fOutput;
				}
			}
			nn->neurons[lay][neur].fResultIn = fResultTemp;
			nn->neurons[lay][neur].fOutput = activationFunction(fResultTemp,nn->neurons[lay][neur].iSigmaType,0);
		}
	}
	
	for (i=0;i<nn->iOutputSize;i++)
	{
		fResult[i] = nn->neurons[nn->iLayerNumber-1][i].fOutput; 
	}
	return 0;
}




float costFunction(int iOutputSize, float fTarget[], float fPredict[])
{
	float fCost = 0;
	for(int i=0;i<iOutputSize;i++)
	{
		fCost += pow(fTarget[i] - fPredict[i],2)/2.0;
		//printf("Cost %f, target %f, predict %f\n",fCost,fTarget[i],fPredict[i]);
	}
	return fCost;
}

float lossDerivative(struct neuron n, float fTarget)
{
	return (n.fOutput - fTarget);
}


/*float costDerivative(float fTarget, float fPredict, int fSigma)
{
	float fGradientValue;
	fGradientValue = fTarget - fSigma*((fTarget - fPredict));
	return fGradientValue;
}*/


int backpropagation(struct ANN* nn, float fTarget[], float fInput[])
{
	int lay,neur,weig,i,j;
	float cost = costFunction(nn->iOutputSize,fTarget,fTarget);
	float fLossDeriv = 0;
	float fErrorPropagation = 0;
	float fSigmaDeriv = 0;
	float fInputDeriv = 0;
	float fDeltaWeight = 0;
	float *** fErrorPropagationMemory = malloc(nn->iLayerNumber*sizeof(float**)); //We keep in memory the weights before change for the calculation in next layer

	
	for (lay=nn->iLayerNumber-1; lay>=0;lay--)
	{		
		fErrorPropagationMemory[lay]=malloc(nn->iNeuronsPerLayer[lay]*sizeof(float*));
		for (neur=0;neur<nn->iNeuronsPerLayer[lay];neur++)
		{
			fErrorPropagationMemory[lay][neur]=malloc(nn->iNeuronsPerLayer[lay]*sizeof(float));
			for (weig=0;weig<nn->neurons[lay][neur].iWeightNumber;weig++)
			{
			//printf("layer %i, neur %i, wei %i: %f\n",lay,neur,weig,nn->neurons[lay][neur].fWeights[weig]);
				if(nn->neurons[lay][neur].fWeights[weig] != 0) //No update if weight = 0 
				{
					if(lay == nn->iLayerNumber -1) //Case of Output layer
					{
						fLossDeriv = lossDerivative(nn->neurons[lay][neur],fTarget[neur]);
						fSigmaDeriv = activationFunction(nn->neurons[lay][neur].fResultIn,nn->neurons[lay][neur].iSigmaType,1);
						fInputDeriv = nn->neurons[lay-1][neur].fOutput;
						fDeltaWeight = fLossDeriv * fSigmaDeriv * fInputDeriv;
						fErrorPropagationMemory[lay][neur][weig] = fLossDeriv * fSigmaDeriv * nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fLastWeights[weig] = nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fWeights[weig] = nn->neurons[lay][neur].fWeights[weig] - nn->fGradientSigma * fDeltaWeight;
					}
					else if(lay == 0) //Case of first hidden layer to get the values of inputs
					{
						fErrorPropagation = 0;
						for (i=0;i<nn->iNeuronsPerLayer[lay+1];i++)
						{
							fErrorPropagation += fErrorPropagationMemory[lay+1][i][weig];
						}
						fSigmaDeriv = activationFunction(nn->neurons[lay][neur].fResultIn,nn->neurons[lay][neur].iSigmaType,1);
						fInputDeriv = fInput[weig];
						fDeltaWeight = fErrorPropagation * fSigmaDeriv * fInputDeriv;
						fErrorPropagationMemory[lay][neur][weig] = fLossDeriv * fSigmaDeriv * nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fLastWeights[weig] = nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fWeights[weig] = nn->neurons[lay][neur].fWeights[weig] - nn->fGradientSigma * fDeltaWeight;
					}
					else
					{
						fErrorPropagation = 0;
						for (i=0;i<nn->iNeuronsPerLayer[lay+1];i++)
						{
							fErrorPropagation += fErrorPropagationMemory[lay+1][i][weig];
						}
						fSigmaDeriv = activationFunction(nn->neurons[lay][neur].fResultIn,nn->neurons[lay][neur].iSigmaType,1);
						fInputDeriv = nn->neurons[lay-1][neur].fOutput;
						fDeltaWeight = fErrorPropagation * fSigmaDeriv * fInputDeriv;
						fErrorPropagationMemory[lay][neur][weig] = fLossDeriv * fSigmaDeriv * nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fLastWeights[weig] = nn->neurons[lay][neur].fWeights[weig];
						nn->neurons[lay][neur].fWeights[weig] = nn->neurons[lay][neur].fWeights[weig] - nn->fGradientSigma * fDeltaWeight;

					}
				}
				
			}
		}
	}
	
	//free of fWeightMemory
	for(i=0;i<nn->iLayerNumber-1;i++)
	{
		for(j=0;j<nn->iNeuronsPerLayer[i];j++)
		{
			free(fErrorPropagationMemory[i][j]);
		}
		free(fErrorPropagationMemory[i]);
	}
	free(fErrorPropagationMemory);
	return 0;
}	









//TEST
void TESTNEURON(struct neuron n)
{
	printf("\nTEST NEURON BEGIN\n");
	printf("weightNumber = %i\n",n.iWeightNumber);
	printf("Sigma  = %i\n",n.iSigmaType);
	printf("Xpos = %i / Ypos = %i\n",n.xPos,n.yPos);
	printf("Weights: ");
	for (int i=0; i<n.iWeightNumber;i++){printf("%f\t",n.fWeights[i]);}
	printf("\nTEST NEURON END\n");

}


void TESTANN (struct ANN nn)
{
	int lay,neur,weig,iLayerNumber;
	printf("\nTEST ANN BEGIN\n");
	printf("input size = %i\n",nn.iInputSize);
	printf("output size  = %i\n",nn.iOutputSize);
	printf("layer number = %i\n",nn.iLayerNumber);
	printf("iterations  = %i\n",nn.iIterations);
	printf("gradientSigma = %f\n",nn.fGradientSigma);
	
	printf("Neurons per hidden layers : ");
	for (int i=0; i<nn.iLayerNumber-1;i++){printf("%i; ",nn.iNeuronsPerLayer[i]);}

	printf("\nneurons (Output//SigmaType//Weights):");
	for (lay=0; lay<nn.iLayerNumber;lay++)
	{
		if (lay == nn.iLayerNumber-1){iLayerNumber = nn.iOutputSize; printf("\noutput layer %d:\n",lay);}
		else {iLayerNumber = nn.iNeuronsPerLayer[lay]; printf("\nlayer %d:\n",lay);}

		for (neur=0;neur<iLayerNumber;neur++) 
		{
			printf("Neuron %d: %f//%i//",neur,nn.neurons[lay][neur].fOutput,nn.neurons[lay][neur].iSigmaType);
			for (weig=0;weig<nn.neurons[lay][neur].iWeightNumber;weig++)
			{

				printf("%f/",nn.neurons[lay][neur].fWeights[weig]);
				
			}
			printf("\n");
		}	
	
		
	}
	

	/*printf("\nMaxFunction :\n");
	for (int i=0; i<MAXFUNCTION;i++){printf("%c\t",nn.cFunction[i]);}*/
	
	printf("\nTEST ANN END\n");

}























