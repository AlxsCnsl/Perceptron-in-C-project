#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));

    //DATA
    int size1 = 4, size2 =2;
    double data_inputs[] = {
        0, 0,  //ligne1
        0, 1,  //ligne2
        1, 0,  //...
        1, 1,
    };
    double** new_data = make_data_inputs(data_inputs, size1, size2);

    double expected_output[4] = {0, 1, 1, 1};


    Perceptron perceptron = make_perceptron(2, 0, 1);
    print_perceptron(&perceptron);

    TrainingConfig conf = new_training_config(1000, 100, 0.01, 0.1);
    multiTrainPerceptron(&perceptron, new_data, expected_output, 4, conf, ACTIVATION_STEP);

    print_perceptron(&perceptron);

    //trainPerceptron(&perceptron, new_data, expected_output, 4,  0.1, 0.01, ACTIVATION_STEP);
    printf ("test manuel avec des data : \n");
    double input1[2] = {1, 1};
    double input2[2] = {0, 1};
    double input3[2] = {0, 0};
    give_resulte_prompt(&perceptron, input1, 2, ACTIVATION_STEP);
    give_resulte_prompt(&perceptron, input2, 2, ACTIVATION_STEP);
    give_resulte_prompt(&perceptron, input3, 2, ACTIVATION_STEP);




    free_perceptron(&perceptron);
}