#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));

    //DATA_______________________________________________________________________________
    int row_size = 10, column_size =1;
    double data_inputs[] = {
        0, 
        1,
        2, 
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        100,
        1000,
        10000,
        33333,
    };

    double expected_output[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 200, 2000, 20000, 66666};

    Dataset data = new_dataset(data_inputs, row_size, column_size, expected_output);




    //TRAINING_______________________________________________________________________________
    Perceptron perceptron = make_perceptron(1, 0, 0.1, ACTIVATION_LINEAR);
    print_perceptron(&perceptron);
    TrainingConfig conf = new_training_config(10000000, 100, 0.001, 0.0001, GRADIENT_DESCENT);
    multiTrainPerceptron(&perceptron, data, conf);
    print_perceptron(&perceptron);


    //TEST____________________________________________________________________________________

    printf ("test manuel avec des data : \n");
    double input1[] = {1};
    double input2[] = {7.2};
    double input3[] = {122};
    double input4[] = {714};

    get_output_perceptron(&perceptron, input1, column_size);
    get_output_perceptron(&perceptron, input2, column_size);
    get_output_perceptron(&perceptron, input3, column_size);
    get_output_perceptron(&perceptron, input4, column_size);


    //FREE__

    free_perceptron(&perceptron);
}