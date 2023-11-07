//---------------------------------------//
//               Libraries
//---------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//---------------------------------------//
//            Global Variables
//---------------------------------------//

FILE *fp;
int I, H, O, li, ui, lo, uo = 0;
double w = 0.0;

//---------------------------------------//
//           Open/Read File
//---------------------------------------//

int readFILE(){

    char name_file[30]; 

    printf("Type the name of the file to read\n");

    scanf("%s", name_file);

    // Open file to read
    fp = fopen(name_file, "r");

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

    char name_file[30]; 

    printf("Type the name of the file to write\n");

    scanf("%s", name_file);

    fp = fopen(name_file, "w");

    // if doesnt open will send message to the user
    if(fp == NULL){
        fprintf(stderr, "Couldn't open the file\n");

        return 1;
    }
}

//---------------------------------------//
//           Calc of the output
//---------------------------------------//

int sumMul(float inputArrayWeight[H][I], float hiddenArrayWeight[O][H], float inputs[I], float bias[H + O]){

    float hiddenArray[H];
    float output[O];

    // Reset outputs values
    for (int i = 0; i < O; i++){
        output[i] = 0;
    }
    
    
    // Sum of the multiplication of the the in layer and hidden layer
    for (int i = 0; i < H; i++){
        for (int k = 0; k < I; k++){
            hiddenArray[i] += inputArrayWeight[i][k] * inputs[k];
        }
        hiddenArray[i] += bias[i];
    }

    printf("\n");
    
    for (int i = 0; i < O; i++){
        for (int j = 0; j < H; j++){
            output[i] += hiddenArrayWeight[i][j] * hiddenArray[j];
        }
        output[i] += bias[i];
    }
    
    for (int i = 0; i < O; i++){
        output[i] = 1/(1 + exp(-output[i]));
    }
    

    for (int i = 0; i < O; i++){
        // Print the result of the sumMult of the output layer
        printf("The value of the output %d is ----> %f !!!\n\n", i, output[i]);
    }
}
        
    

//---------------------------------------//
//              Main Cycle
//---------------------------------------//

int main(){

//---------------------------------------//
//           Initialization
//---------------------------------------//

    //---------------------------------------//
    //       Print information from a file
    //---------------------------------------//

    // Open file to read
    readFILE();

    // Read first line that contain the number of I,H,O
    fscanf(fp, "%d %d %d", &I, &H, &O);

    // Print the values of I,H,O
    printf("I = %d, H = %d, O = %d\n", I, H, O);

    // Read the lines that contain the weight of every link between layers
    while (fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w) == 5){
        // Print the information
        printf("Li -> %d:%d %d:%d %f\n", li, ui, lo, uo, w);
    }

    printf("\n");

    // Close file
    fclose(fp);

    // Neural network parameters
    float inputArrayWeight[H][I];
    float hiddenArrayWeight[O][H];
    float output[O];
    float inputs[I];
    float bias[H + O];

//---------------------------------------//
//              Execution
//---------------------------------------//

    //---------------------------------------------------------------------//
    //        Get information from file to calculate output of network
    //---------------------------------------------------------------------//

    // Open file to read
    readFILE();

    // Gives the information to the user about the initialization of the reading of the neural network
    printf("Reading neural network...\n");

    // Read first line that contain the number of I,H,O
    fscanf(fp, "%d %d %d", &I, &H, &O);

    // Read the lines that contain the weight of every link between in and hidden layer
    for (int k = 0; k < (I * H);k++){
        fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w);
        // Transfer the weights to the array
        inputArrayWeight[k%H][k/H] = w;         
    }

    // Read the lines that contain the weight of every link between hidden and output layer
    for (int i = 0; i < (H * O);i++){
        fscanf(fp, "%d:%d %d:%d %lf", &li, &ui, &lo, &uo, &w);
        // Transfer the weights to the array
        hiddenArrayWeight[0][i] = w;
    }

    printf("\n");

    // Close file
    fclose(fp);

    // Inform the user that the file as been read
    printf("Finished reading the file!\n");

    // Tells the user to type the inputs necessecary to calculate the neural network
    for (int x = 0; x < I; x++){
        printf("Type input number %d\n", x);
        scanf("%f", &inputs[x]);
    }

    // Do the calculation necessary to get output
    sumMul(inputArrayWeight,hiddenArrayWeight,inputs, bias);

    //---------------------------------------------------------------------//
    //        Write information on file about the network parameters
    //---------------------------------------------------------------------//

    // Open file to write
    writeFILE();

    // Tells the user to type the number of input nodes
    printf("Type de number of input nodes\n");
    scanf("%d", &I);

    printf("\n");

    // Tells the user to type the number of hidden nodes
    printf("Type de number of hidden nodes\n");
    scanf("%d", &H);
    
    printf("\n");

    // Tells the user to type the number of output nodes
    printf("Type de number of output nodes\n");
    scanf("%d", &O);

    printf("\n");

    // Write tthe information to a new file
    fprintf(fp, "%d %d %d\n", I, H, O);

    // Structurize the neural network based the numbers typed before
    for (int z = 1; z <= I; z++){
        for (int a = 1; a <= H; a++){
            fprintf(fp, "1:%d 2:%d %lf\n", z, a, w);
        } 
    }
    
    for (int z = 1; z <= H; z++){
        for (int a = 1; a <= O; a++){
            fprintf(fp, "2:%d 3:%d %lf\n", z, a, w);
        } 
    }

    // Close file
    fclose(fp);

    // Tells the user that the file as been created and saved
    printf("Neural net work saved!!!\n");

    return 0;
}