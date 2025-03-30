#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));

    //DATA
    int size1 = 10, size2 =2;
    double data_inputs[] = {
        0, 0,  //ligne1
        0, 1,  //ligne2
        1, 0,  //...
        1, 1,
        2, 2,
        3, 4,
        1, 4,
        7, 2,
        10, 4,
        9, 1
    };
    double** new_data = make_data_inputs(data_inputs, size1, size2);
    
    double expected_output[4] = {0, 1, 1, 2, 4, 7, 5, 9, 14, 10};


    Perceptron perceptron = make_perceptron(2, 0, 1);
    print_perceptron(&perceptron);

    int win_counter = 0; 
    int i;
    for(i = 0; i< 100000000; i ++){
        if(trainPerceptron(&perceptron, new_data, expected_output, 4,  0.0000001, 0.00000001, ACTIVATION_LINEAR) == 1){
            win_counter ++;
        }else{
            win_counter = 0;
        }
        if(win_counter == 100){
            break;
        }
    }
    print_perceptron(&perceptron);

    //trainPerceptron(&perceptron, new_data, expected_output, 4,  0.1, 0.01, ACTIVATION_STEP);
    printf ("test manuel avec des data : \n");
    double input1[2] = {1, 1};
    double input2[2] = {4, 6};
    double input3[2] = {12, 5};
    give_resulte_prompt(&perceptron, input1, 2, ACTIVATION_LINEAR);
    give_resulte_prompt(&perceptron, input2, 2, ACTIVATION_LINEAR);
    give_resulte_prompt(&perceptron, input3, 2, ACTIVATION_LINEAR);




    free_perceptron(&perceptron);
}