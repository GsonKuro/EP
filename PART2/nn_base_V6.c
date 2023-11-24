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
//          Calculate sigmoid
//---------------------------------------//

double sigmoid(double value){
    return 1/(1 + exp(-value));
}

//---------------------------------------//
//      Calculate sigmoid derivative
//---------------------------------------//

double sigmoid_derivative(double value){
    // returns the derivative value
    return value * (1 - value);
}

//-----------------------------//
//         Propagation
//-----------------------------//

int propagation(double inputArrayWeight[H][I], double hiddenArrayWeight[O][H], double inputArrayBias[1][H], double hiddentArrayBias[1][O], double lr, double median_error_value, int epoch_value){
    
    int epoch = 0;
    int start = 0;
    double median_error;
    double inputArrayWeight3D[4][H][I];
    double hiddenArrayWeight3D[4][O][H];
    double inputArrayBias3D[4][1][H];
    double hiddentArrayBias3D[4][1][O];
    double inputs[4][2] = {{0,0},{0,1},{1,0},{1,1}};
    double target[4][1] = {{0},{1},{1},{0}};
    double hiddenActivation[4][H];
    double hiddenOutput[4][H];
    double outputActivation[4][O];
    double output[4][O];
    double error[4][O];
    double d_hiddenweight[H][O];
    double d_hiddenbias[4][O];
    double d_inputweight[I][H];
    double d_inputbias[4][H];
    double error_prop_hidden[4][O];
    double error_hidden[4][H];
    double weights[4][(I*H)+(H*O)];

    // reallocate weights in 3D arrays
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < H; j++){
            for (int k = 0; k < I; k++){
                inputArrayWeight3D[i][j][k] = inputArrayWeight[j][k];
            }
        inputArrayBias3D[i][0][j] = inputArrayBias[0][j];
        }
        for (int j = 0; j < O; j++){
            for (int k = 0; k < H; k++){
                hiddenArrayWeight3D[i][j][k] = hiddenArrayWeight[j][k];
            }
            hiddentArrayBias3D[i][0][j] = hiddentArrayBias[0][j];
        }
    }

    // start calculation
    start = 1;

    // condition the time of calculation until gets the error objective or a max number of tentaives
    while ((epoch <= epoch_value && median_error > median_error_value) || start == 1){

        start = 0;
        printf("epoch = %d\n", epoch);
        printf("start = %d\n", start);

    //---------------------------------------//
    //         Forward Propagation
    //---------------------------------------//

        // calculate to the 4 solutions
        for(int i = 0; i < 4; i++){

            // calculate hidden output
            for (int j = 0; j < H; j++){
                hiddenActivation[i][j] = 0;
                for (int k = 0; k < I; k++){
                    hiddenActivation[i][j] += inputArrayWeight3D[i][j][k] * inputs[i][k];
                }
                hiddenActivation[i][j] += inputArrayBias3D[i][0][j];
                hiddenOutput[i][j] = sigmoid(hiddenActivation[i][j]);
                printf("%lf ", inputs[i][j]);
                //printf("%lf ", hiddenOutput[i][j]);
            }

            // calculate outputs
            for (int j = 0; j < O; j++){
                outputActivation[i][j] = 0;
                for (int k = 0; k < H; k++){
                    outputActivation[i][j] += hiddenArrayWeight3D[i][j][k] * hiddenOutput[i][k];
                }
                outputActivation[i][j] += hiddentArrayBias3D[i][0][j];
                output[i][j] = sigmoid(outputActivation[i][j]);
                printf("output = %lf\n", output[i][j]);
            }

            // calculate error
            error[i][0] = (target[i][0] - output[i][0]) * sigmoid_derivative(output[i][0]);
            printf("error = %lf\n", error[i][0]);

            // sum the error do divide later
            median_error += fabs(error[i][0]);
        }

        // median error
        median_error = median_error/4;
        printf("median error = %lf", median_error);

        printf("\n");

    //---------------------------------------//
    //            Back Propagation
    //---------------------------------------//

        // calculate to the 4 solutions
        for(int i = 0; i < 4; i++){

            // calculate changes in weights between hidden and output layer
            for (int j = 0; j < H; j++){
                d_hiddenweight[j][0] = lr * error[i][0] * hiddenOutput[i][j];
                //printf("%lf ", d_hiddenweight[j][0]);
            }
            d_hiddenbias[i][0] = lr * error[i][0];
            //printf("%lf\n", d_hiddenbias[i][0]);

            // propagate error to hidden layer
            for(int j = 0; j < H; j++){
                error_prop_hidden[i][j] = error[i][0] * hiddenArrayWeight[0][j];
            }

            // calculate propagated error form output
            for(int j = 0; j < H; j++){
                error_hidden[i][j] = error_prop_hidden[i][j] * hiddenOutput[i][j];
            }
            
            // calculate changes in weights between input and hidden layer
            for(int j = 0; j < H; j++){
                for (int k = 0; k < I; k++){
                    d_inputweight[k][j] = lr * error_hidden[i][j] * inputs[i][k];
                    //printf("%lf ", d_inputweight[k][j]);
                }
                d_inputbias[i][j] = lr * error_hidden[i][j];
                //printf("%lf\n", d_inputbias[i][j]);
            }

            // update weights of input to hidden layer and bias
            for (int j = 0; j < H; j++){
                for (int k = 0; k < I; k++){
                    inputArrayWeight3D[i][j][k] = inputArrayWeight3D[i][j][k] + d_inputweight[k][j];
                    //printf("%lf ", inputArrayWeight[j][k]);
                }
                inputArrayBias3D[i][0][j] = inputArrayBias3D[i][0][j] + d_inputbias[i][j];
                //printf("%lf\n", inputArrayBias[0][j]);
            }
            
            // update weights of hidden to ouput layer and bias
            for (int j = 0; j < O; j++){
                for (int k = 0; k < H; k++){
                    hiddenArrayWeight3D[i][j][k] = hiddenArrayWeight3D[i][j][k] + d_hiddenweight[k][j];
                    //printf("%lf ", hiddenArrayWeight[j][k]);
                }
                hiddentArrayBias3D[i][0][j] = hiddentArrayBias3D[i][0][j] + d_hiddenbias[i][j];
                //printf("%lf\n", hiddentArrayBias[0][j]);
            }
        }

        // one more season
        epoch++;
    }
}

//---------------------------------------//
//              Main Cycle
//---------------------------------------//

int main(){

//---------------------------------------//
//           Initialization
//---------------------------------------//

    double lr = 0;
    double median_error_value = 0;
    int epoch_value = 0;

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
    double inputArrayWeight[H][I];
    double hiddenArrayWeight[O][H];
    double inputArrayBias[1][H];
    double hiddentArrayBias[1][O];

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

    //---------------------------------------//
    //            Random Weights
    //---------------------------------------//

    // random weights for input to hidden
    for(int i = 0; i < I; i++){
        for(int j = 0; j < H; j++){
            inputArrayWeight[i][j] = ((double)rand()/RAND_MAX);
        }
    }

    // random weights for bias to hidden
    for(int i = 0; i < H; i++){
        inputArrayBias[0][i] = ((double)rand()/RAND_MAX);
    }

    // random weights for hidden to output
    for(int i = 0; i < H; i++){
        for(int j = 0; j < O; j++){
            hiddenArrayWeight[i][j] = ((double)rand()/RAND_MAX);
        }
    }

    // random weights for bias to output
    for(int i = 0; i < O; i++){
        hiddentArrayBias[0][i] = ((double)rand()/RAND_MAX);
    }

    //-----------------------------//
    //            Debug
    //-----------------------------//

    // Print initial weights and biases
    printf("Initial hidden weights: ");
    for (int i = 0; i < I; ++i) {
        for (int j = 0; j < H; ++j) {
            printf("%lf ", inputArrayWeight[i][j]);
        }
    }
    printf("\n");

    printf("Initial hidden biases: ");
    for (int i = 0; i < H; ++i) {
        printf("%lf ", inputArrayBias[0][i]);
    }
    printf("\n");

    printf("Initial output weights: ");
    for (int i = 0; i < H; ++i){
        for (int j = 0; j < O; ++j){
            printf("%lf ", hiddenArrayWeight[i][j]);
        }
    }
    printf("\n");

    printf("Initial output biases: ");
    for (int i = 0; i < O; ++i) {
        printf("%lf ", hiddentArrayBias[0][i]);
    }
    printf("\n");

    //---------------------------------------//
    //        Training Algorithm
    //---------------------------------------//

    printf("Select a learn rate for the neural network\n");
    scanf("%lf", &lr);

    printf("\n");

    printf("Select how much median_error you want for the neural network\n");
    scanf("%lf", &median_error_value);

    printf("\n");

    printf("Select how much epoch you want for the neural network to run\n");
    scanf("%d", &epoch_value);

    propagation(inputArrayWeight, hiddenArrayWeight, inputArrayBias, hiddentArrayBias, lr, median_error_value, epoch_value);

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