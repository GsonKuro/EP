//---------------------------------------//
//               Libraries
//---------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//---------------------------------------//
//            Global Variables
//---------------------------------------//

FILE *fp;

//---------------------------------------//
//              Open File
//---------------------------------------//

int openFILE(){
    // Open file to read
    fp = fopen("redeneural", "r");

    // if doesnt open will send message to user
    if(fp == NULL){
        fprintf(stderr, "Couldn't open the file\n");

        return 1;
    }
}

//---------------------------------------//
//           Open/Write File
//---------------------------------------//

int writeFILE(){
    // Open file to read
    fp = fopen("redeneural", "w");

    // if doesnt open will send message to the user
    if(fp == NULL){
        fprintf(stderr, "Couldn't open the file\n");

        return 1;
    }
}

//---------------------------------------//
//           Calc of the output
//---------------------------------------//

int sumMul(float inputArrayWeight[3][2], float hiddenArrayWeight[1][3], float inputs[2]){

    float hiddenArray[3];
    float output;

    printf("Result of the sum of the multipplication\n\n");

    // Sum of the multiplication between in and out of each layer
    hiddenArray[0] = inputArrayWeight[0][0] * inputs[0] + inputArrayWeight[0][1] * inputs[1];
    hiddenArray[1] = inputArrayWeight[1][0] * inputs[0] + inputArrayWeight[1][1] * inputs[1];
    hiddenArray[2] = inputArrayWeight[2][0] * inputs[0] + inputArrayWeight[2][1] * inputs[1];

    // print result of sumMult of hidden layer
    for (int i = 0; i < 3; i++){
        printf("%f ", hiddenArray[i]);
    }

    printf("\n\n");

    printf("OUTPUT !!!\n\n");
    
    output = hiddenArrayWeight[0][0] * hiddenArray[0] + hiddenArrayWeight[0][1] * hiddenArray[1] + hiddenArrayWeight[0][2] * hiddenArray[2];

    // print result of sumMult of output layer
    printf("%f \n\n", output);

}

//---------------------------------------//
//              Main Cycle
//---------------------------------------//

int main(){

//---------------------------------------//
//           Initialization
//---------------------------------------//

    int I, H, O, li, ui, lo, uo = 0;
    double w = 0.0;

    // Neural network
    float inputArrayWeight[3][2];
    float hiddenArrayWeight[1][3];
    float inputs[2];
    float output;

    int inputLayer[1];
    int inputNode[2];
    int hiddenLayer[1];
    int hiddenNode[3];
    int weights[9];

    //neural();

//---------------------------------------//
//              Execution
//---------------------------------------//

    //---------------------------------------------------------------------//
    //        Write information on file about the network parameters
    //---------------------------------------------------------------------//

    // Open file to write
    writeFILE();

    fprintf(fp, "2 3 1\n");
    fprintf(fp, "1:1 2:1 0.234\n");
    fprintf(fp, "1:1 2:2 -0.345\n");
    fprintf(fp, "1:1 2:3 1.124\n");
    fprintf(fp, "1:2 2:1 0.098\n");
    fprintf(fp, "1:2 2:2 -1.9877\n");
    fprintf(fp, "1:2 2:3 0.0\n");
    fprintf(fp, "2:1 3:1 0.0\n");
    fprintf(fp, "2:2 3:1 0.0\n");
    fprintf(fp, "2:3 3:1 0.0\n");

    // Close file
    fclose(fp);

    //---------------------------------------//
    //       Print information from file
    //---------------------------------------//

    // Open file to read
    openFILE();

    fscanf(fp, "%d %d %d", &I, &H, &O);

    printf("I = %d, H = %d, O = %d\n", I, H, O);

    while (fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w) == 5){
        printf("Li -> %d:%d %d:%d %f\n", li, ui, lo, uo, w);
    }

    printf("\n");

    // Close file
    fclose(fp);

    //---------------------------------------------------------------------//
    //        Get information from file to calculate output of network
    //---------------------------------------------------------------------//

    // Open file to read
    openFILE();

    fscanf(fp, "%d %d %d", &I, &H, &O);

    for (int k = 0; k <= 5;k++){
        fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w);
        
        inputArrayWeight[k%3][k/3] = w;
        printf("%f ", inputArrayWeight[k%3][k/3]);

        if (k >= 2 && k < 3)
        {
            printf("\n");
        }            
    }

    printf("\n");

    for (int i = 0; i < 3;i++){
        fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w);
              
        hiddenArrayWeight[0][i] = w;
        printf("%f ", hiddenArrayWeight[0][i]);      
    }

    printf("\n");

    // Close file
    fclose(fp);

    // Insert input values
    inputs[0]  = 1.0;
    inputs[1]  = 2.0;

    // Do the calculation necessary to get output
    sumMul(inputArrayWeight,hiddenArrayWeight,inputs);

    return 0;
}