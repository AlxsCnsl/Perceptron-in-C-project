#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));

    //DATA_____________________________________________________________________________
    int row_size = 4, column_size =2;
    double data_inputs[] = {
        0, 1, 
        1, 1, 
        1, 0, 
        0, 0,
    };

    double expected_output[] = {1, 1, 1, 0};

    Dataset data = new_dataset(data_inputs, row_size, column_size, expected_output);




    //TRAINING_______________________________________________________________________________
    Perceptron perceptron = make_perceptron(2, 0, 1, ACTIVATION_SIGMOID);
    print_perceptron(&perceptron);
    TrainingConfig conf = new_training_config(1410065408, 10, 0.1, 0.01);
    multiTrainPerceptron(&perceptron, data, conf);
    print_perceptron(&perceptron);


    //TEST____________________________________________________________________________________

    printf ("test manuel avec des data : \n");
    double input1[] = {1, 1};
    double input2[] = {0, 0};
    double input3[] = {1, 0};
    double input4[] = {0, 1};

    get_output_perceptron(&perceptron, input1, column_size);
    get_output_perceptron(&perceptron, input2, column_size);
    get_output_perceptron(&perceptron, input3, column_size);
    get_output_perceptron(&perceptron, input4, column_size);

    //FREE
    free_perceptron(&perceptron);
}