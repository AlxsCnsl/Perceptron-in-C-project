#include<stdio.h>
#include<stdlib.h>
#include"../include/perceptron.h"
#include"../include/malloctools.h"

Perceptron make_perceptron(int w_size, double b, int range){
    double *w = (double*)malloc(w_size * sizeof(double));
    random_weight_init(w, w_size, range);
    Perceptron perceptron;
    MALLOC_CHECK(w);
    perceptron.weights_size = w_size;
    perceptron.bias = b;
    perceptron.weights = w;
    return perceptron;
}

void random_weight_init(double* weights, int w_size, int range) {
    int i;
    for(i=0; i<w_size; i++){
        weights[i] = -range + ((float)rand() / RAND_MAX) * range*2;;
    }
}

void print_perceptron(Perceptron* perceptron){
    int i;
    printf("bias = %f \n [ ", perceptron->bias);
    for(i=0; i< perceptron->weights_size; i++){
        printf("w%d:%f ",i, perceptron->weights[i]);
    }
    printf("]");
}

void free_perceptron(Perceptron* perceptron){
    free(perceptron->weights);
}


double compute_weighted_sum(Perceptron* p, double inputs[], int i_size){
    double S = 0.0;
    int i;
    check_inputs(p, inputs, i_size);
    for(i=0; i<i_size; i++){
        S+= inputs[i] * p->weights[i];
    }
    S+= p->bias;
    return S;
}

void check_inputs(Perceptron* p, double inputs[], int i_size){
    if(inputs == NULL){
        fprintf(stderr, "Erreur d'input NULL \n");
        exit(2);
    }
    if(p->weights_size != i_size){
        fprintf(stderr, "Erreur de taille d'input \n");
        exit(2);
    }
}

int calculate_activation_step_function(double weighted_sum){
    return (weighted_sum > 0) ? 1 : 0;
}
