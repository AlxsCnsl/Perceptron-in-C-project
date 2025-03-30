#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));
    Perceptron perceptron = make_perceptron(10, 1.0, 1);
    print_perceptron(&perceptron);
    free_perceptron(&perceptron);
}