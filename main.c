#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));

    //DATA
    int row_size = 4, column_size =2;
    double data_inputs[] = {
        0, 0,  //ligne1
        0, 1,  //ligne2
        1, 0,  //...
        1, 1,
    };

    double expected_output[4] = {0, 1, 1, 1};

    Dataset data = new_dataset(data_inputs, row_size, column_size, expected_output);

    //TRAINING
    Perceptron perceptron = make_perceptron(2, 0, 1, ACTIVATION_STEP);
    print_perceptron(&perceptron);
    TrainingConfig conf = new_training_config(1000, 100, 0.01, 0.1);
    multiTrainPerceptron(&perceptron, data, conf);
    print_perceptron(&perceptron);


    //TEST
    printf ("test manuel avec des data : \n");
    double input1[2] = {1, 1};
    double input2[2] = {0, 1};
    double input3[2] = {0, 0};
    get_output_perceptron(&perceptron, input1, 2);
    get_output_perceptron(&perceptron, input2, 2);
    get_output_perceptron(&perceptron, input3, 2);


    //FREE
    free_perceptron(&perceptron);
}