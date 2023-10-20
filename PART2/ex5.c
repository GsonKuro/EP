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
//       Creation of neural system
//---------------------------------------//

/*int neural(){
    float   inputArrayWeight[3][2];
    float   hiddenArrayWeight[1][3];
    float   output = 0;

    printf("primeira camada \n\n");

    // Percorrer colunas
    for (int i = 0; i < 3; i++){
        // Percorrer linhas
        for (int j = 0; j < 2; j++){      
            printf("%f ", inputArrayWeight[i][j]);    
        }
        printf("\n");
    }

    printf("\ncamda escondida \n\n");
    
    // Percorrer colunas
    for (int q = 0; q < 1; q++){
        // Percorrer linhas
        for (int e = 0; e < 3; e++){      
            printf("%f ", hiddenArrayWeight[q][e]);    
        }
        printf("\n");
    }

    printf("\nultima camada\n\n");

    printf("%f\n\n", output);
}*/

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
    fp = fopen("redeneuralTest", "w");

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

    //neural();

//---------------------------------------//
//              Execution
//---------------------------------------//

    //---------------------------------------------------------------------//
    //        Write information on file about the network parameters
    //---------------------------------------------------------------------//

    // Open file to write
    writeFILE();

    // Write information about the network
    fprintf(fp, "%d %d %d\n", I, H, O);
    for (int i = 0; i < 9; i++)
    {
        fprintf(fp, "%d:%d %d:%d %f\n", li, ui, lo, uo, w);
    }

    // Close file
    fclose(fp);

    //---------------------------------------------------------------------//
    //        Get information in file to calculate output of network
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

    // Open file to read
    openFILE();

    //---------------------------------------//
    //       Print information in file
    //---------------------------------------//

    fscanf(fp, "%d %d %d", &I, &H, &O);

    printf("I = %d, H = %d, O = %d\n", I, H, O);

    while (fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w) == 5){
        printf("Li -> %d:%d %d:%d %f\n", li, ui, lo, uo, w);
    }

    // Close file
    fclose(fp);

    return 0;
}