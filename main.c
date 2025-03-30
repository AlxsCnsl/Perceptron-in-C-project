#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "include/perceptron.h"

int main(void){
    srand(time(NULL));
    Perceptron perceptron = makePerceptron(10, 1.0, 1);
    printPerceptron(&perceptron);
    freePerceptron(&perceptron);
}