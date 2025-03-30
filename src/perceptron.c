#include<stdio.h>
#include<stdlib.h>
#include"../include/perceptron.h"
#include"../include/malloctools.h"

Perceptron makePerceptron(int w_size, double b, int range){
    double *w = (double*)malloc(w_size * sizeof(double));
    randomWeightInit(w, w_size, range);
    Perceptron perceptron;
    MALLOC_CHECK(w);
    perceptron.weights_size = w_size;
    perceptron.bias = b;
    perceptron.weights = w;
    return perceptron;
}

void randomWeightInit(double *weights, int w_size, int range) {
    int i;
    for(i=0; i<w_size; i++){
        weights[i] = -range + ((float)rand() / RAND_MAX) * range*2;;
    }
}

void printPerceptron(Perceptron *perceptron){
    int i;
    printf("bias = %f \n [ ", perceptron->bias);
    for(i=0; i< perceptron->weights_size; i++){
        printf("w%d:%f ",i, perceptron->weights[i]);
    }
    printf("]");
}

void freePerceptron(Perceptron *perceptron){
    free(perceptron->weights);
}